// Conceptual, scripted traces. These do not inspect arbitrary edited programs.
function memoryPanel(topic) {
    const m=DATA.memory.find(x=>x.id===topic.id);if(!m)return '';
    return `<div class="memory-lab" data-memory="${m.id}"><span class="eyebrow">Explore memory</span><h3>${safe(m.title)}</h3><p>${safe(m.intro)}</p><div class="memory-controls"><button data-memory-action="reset">Restart</button><button data-memory-action="previous">← Previous</button><span class="memory-position" role="status"></span><button class="primary" data-memory-action="next">Next →</button></div><pre class="lesson-code memory-code"></pre><div class="memory-picture"></div><p class="memory-explanation" aria-live="polite"></p><p class="footnote">Conceptual storage diagram: addresses use names rather than real numeric addresses; box sizes do not represent bytes. It follows this trace only, independently of edits in the runnable programs.</p><details class="answer"><summary>Read the current state as a table</summary><div class="memory-table"></div></details><details class="answer"><summary>Read all steps without the diagram</summary><ol>${m.steps.map(s=>`<li><code>${safe(s.code)}</code><p>${safe(s.note)}</p></li>`).join('')}</ol></details></div>`;
}
function memorySvgStart(id,label) {
    return `<svg viewBox="0 0 800 340" role="img" aria-labelledby="${id}-title"><title id="${id}-title">${safe(label)}</title><defs><marker id="${id}-arrow" markerWidth="9" markerHeight="9" refX="8" refY="4" orient="auto"><path d="M0,0 L8,4 L0,8 Z" fill="#087f8c"/></marker><marker id="${id}-danger" markerWidth="9" markerHeight="9" refX="8" refY="4" orient="auto"><path d="M0,0 L8,4 L0,8 Z" fill="#aa6417"/></marker></defs>`;
}
function memoryArrow(id,fromY,toY,dangling=false) {
    return `<path class="memory-arrow ${dangling?'dangling-arrow':''}" d="M265 ${fromY} C370 ${fromY}, 405 ${toY}, 515 ${toY}" marker-end="url(#${id}-${dangling?'danger':'arrow'})"/>`;
}
function pointerBox(name,value,y,declared=true) {
    return `<g class="pointer-cell ${declared?'':'undeclared-cell'}"><rect x="35" y="${y}" width="230" height="64" rx="7"/><text x="49" y="${y+23}" class="cell-name">${safe(name)}</text><text x="49" y="${y+47}" class="cell-value">${safe(declared?value:'not declared yet')}</text></g>`;
}
function pointerDiagram(state,id) {
    let svg=memorySvgStart(id,'Pointer targets and reference alias: '+state.note);
    svg+='<text x="35" y="23" class="region-title">Pointer objects</text><text x="515" y="23" class="region-title">Integer objects (automatic storage)</text>';
    svg+=pointerBox('ptr',state.ptr==='null'?'nullptr':state.ptr?'&'+state.ptr:'',55,!!state.ptr);
    svg+=pointerBox('p2',state.p2?'&'+state.p2:'',205,!!state.p2);
    for(const [name,y,value] of [['x',55,state.x],['y',205,state.y]]) {
        svg+=`<g class="object-cell"><rect x="515" y="${y}" width="245" height="93" rx="7"/><text x="531" y="${y+25}" class="cell-name">${name} <tspan class="address-label">· address &amp;${name}</tspan></text><text x="531" y="${y+58}" class="int-value">${value}</text>${name==='x'&&state.ref?`<text x="602" y="${y+60}" class="reference-alias">also named num</text>`:''}</g>`;
    }
    if(state.ptr && state.ptr!=='null')svg+=memoryArrow(id,87,state.ptr==='x'?96:246);
    if(state.p2)svg+=memoryArrow(id,237,state.p2==='x'?113:263);
    svg+='<text x="35" y="325" class="legend-text">Solid arrow = pointer stores this object’s address.</text></svg>';
    const rows=[['x','int object',state.x],['y','int object',state.y]];
    if(state.ptr)rows.push(['ptr','pointer value',state.ptr==='null'?'nullptr':'&'+state.ptr]);
    if(state.p2)rows.push(['p2','pointer value','&'+state.p2]);
    if(state.ref)rows.push(['num','reference alias','x (same object; value '+state.x+')']);
    return {svg,rows};
}
function dynamicDiagram(state,id) {
    let svg=memorySvgStart(id,'Local pointers and dynamic allocations: '+state.note);
    svg+='<text x="35" y="23" class="region-title">Local pointer objects</text><text x="515" y="23" class="region-title">Dynamic storage (heap)</text>';
    const rows=[];
    for(const [name,target,y] of [['p',state.p,45],['alias',state.alias,145],['values',state.values,245]]) {
        const value=!target?'':target==='null'?'nullptr':target.startsWith('dangling')?'dangling (old '+target.slice(-1)+')':'address of '+target;
        svg+=pointerBox(name,value,y,!!target);
        if(target && target!=='null')svg+=memoryArrow(id,y+32,target.endsWith('B')?240:name==='alias'?113:82,target.startsWith('dangling'));
        if(target)rows.push([name,'pointer value',value]);
    }
    const a=state.allocation;
    svg+=`<g class="${a?.live?'heap-cell':'released-cell'}"><rect x="515" y="45" width="245" height="90" rx="7"/><text x="531" y="70" class="cell-name">Allocation A · int</text><text x="531" y="105" class="${a?.live?'int-value':'released-label'}">${a?(a.live?a.value:'released — do not access'):'not allocated yet'}</text></g>`;
    const b=state.array;
    svg+=`<g class="${b?.live?'heap-cell':'released-cell'}"><rect x="515" y="190" width="245" height="115" rx="7"/><text x="531" y="214" class="cell-name">Allocation B · int[3]</text>`;
    if(b?.live) {
        b.cells.forEach((value,i)=>{svg+=`<rect class="array-slot" x="${531+i*72}" y="227" width="66" height="45"/><text x="${551+i*72}" y="255" class="array-value">${value}</text><text x="${549+i*72}" y="290" class="address-label">[${i}]</text>`;});
    } else svg+=`<text x="531" y="255" class="released-label">${b?'released — do not access':'not allocated yet'}</text>`;
    svg+='</g><text x="35" y="335" class="legend-text">Dashed amber arrow = dangling pointer; its former target is no longer live.</text></svg>';
    rows.push(['Allocation A','dynamic int',!a?'not allocated':a.live?String(a.value):'released; no live value']);
    rows.push(['Allocation B','dynamic int array',!b?'not allocated':b.live?b.cells.join(', '):'released; no live values']);
    return {svg,rows};
}
function setupMemory() {
    document.querySelectorAll('.memory-lab').forEach(panel=>{
        const model=DATA.memory.find(x=>x.id===panel.dataset.memory);
        let position=Math.max(0,Math.min(model.steps.length-1,Number(saved('memory-'+model.id+'-step','0'))||0));
        function draw() {
            const step=model.steps[position],id='memory-'+model.id;
            const picture=model.kind==='pointers'?pointerDiagram(step,id):dynamicDiagram(step,id);
            panel.querySelector('.memory-position').textContent=`Step ${position+1} of ${model.steps.length}`;
            panel.querySelector('.memory-code').textContent=step.code;
            panel.querySelector('.memory-picture').innerHTML=picture.svg;
            panel.querySelector('.memory-explanation').textContent=step.note;
            panel.querySelector('.memory-table').innerHTML=`<table><thead><tr><th>Name</th><th>Role</th><th>Current state</th></tr></thead><tbody>${picture.rows.map(row=>`<tr>${row.map(c=>`<td>${safe(c)}</td>`).join('')}</tr>`).join('')}</tbody></table>`;
            panel.querySelector('[data-memory-action="previous"]').disabled=position===0;
            panel.querySelector('[data-memory-action="next"]').disabled=position===model.steps.length-1;
            save('memory-'+model.id+'-step',String(position));
        }
        panel.querySelectorAll('[data-memory-action]').forEach(button=>button.addEventListener('click',()=>{
            position=button.dataset.memoryAction==='reset'?0:Math.max(0,Math.min(model.steps.length-1,position+(button.dataset.memoryAction==='next'?1:-1)));
            draw();
        }));
        draw();
    });
}
