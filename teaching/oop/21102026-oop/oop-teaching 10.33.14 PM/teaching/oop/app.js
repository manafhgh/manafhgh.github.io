'use strict';
const DATA = window.OOP_DATA;
const allLessons=[...DATA.topics,...DATA.optional];
const byId = new Map(DATA.examples.map(e => [e.id, e]));
byId.set('model-starter',{id:'model-starter',code:DATA.model.starter,stdin:''});
byId.set('model-solution',{id:'model-solution',code:DATA.model.solution,stdin:'',output:DATA.model.solutionOutput});
const safe = s => String(s).replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
function highlight(code) {
    const re = /(\/\*[\s\S]*?\*\/|\/\/[^\n]*|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|\b(?:class|public|private|protected|const|constexpr|static|virtual|override|return|if|else|for|while|int|float|double|bool|char|void|new|delete|nullptr|using|namespace|friend|explicit|default|try|catch|throw|true|false|long)\b|\b\d+(?:\.\d+)?\b)/g;
    let result='', last=0;
    for (const m of code.matchAll(re)) {
        result += safe(code.slice(last,m.index));
        const v=m[0], kind=v.startsWith('//')||v.startsWith('/*')?'comment':v[0]==='"'||v[0]==="'"?'string':/^\d/.test(v)?'number':'keyword';
        result += `<span class="${kind}">${safe(v)}</span>`;
        last=m.index+v.length;
    }
    return result+safe(code.slice(last));
}
function saved(key,fallback) { try{return localStorage.getItem('oop-v1-'+key) ?? fallback;}catch{return fallback;} }
function save(key,value) { try{localStorage.setItem('oop-v1-'+key,value);}catch{} }
function runner(e, id=e.id, isSolution=false) {
    const original=e.code, current=saved(id+'-code',original);
    return `<div class="runner" data-id="${safe(id)}" data-source="${safe(e.id)}" data-solution="${isSolution}">
        <div class="toolbar"><button class="primary" data-action="run">Run ▶</button>${id==='model-workspace'?'<button class="check-code" data-action="check">Check solution</button>':''}<button data-action="edit" aria-pressed="false">Edit code</button><button data-action="copy">Copy</button><button data-action="download">Download .cpp</button><button data-action="reset">Reset</button><span class="language">C++17 · GCC 13.2</span></div>
        <pre class="code-view" tabindex="0" aria-label="C++ source code"><code>${highlight(current)}</code></pre>
        <textarea class="editor" aria-label="Edit C++ source code" spellcheck="false" autocapitalize="off" hidden>${safe(current)}</textarea>
        <div class="io"><div><label for="input-${safe(id)}">Standard input (cin)</label><textarea id="input-${safe(id)}" class="stdin" aria-label="Standard input" placeholder="Enter input before running if required">${safe(saved(id+'-stdin',e.stdin||''))}</textarea></div><div><span class="output-label">Output / compiler messages</span><pre class="output" aria-live="polite">Run the program to see its output.</pre></div></div>
        <div class="status" role="status"></div>
        ${e.output!==undefined?`<details class="sample"><summary>Verified sample output${e.stdin?' (using the supplied input)':''}</summary><pre>${safe(e.output)}</pre></details>`:''}
    </div>`;
}
function examplesFor(t) {
    return DATA.examples.filter(e=>e.topic===t.id).map((e,i)=>`<details class="example" ${i===0?'open':''}><summary>${safe(e.title)}</summary><div class="example-body"><p class="note">${safe(e.note)}</p>${runner(e)}</div></details>`).join('');
}
function practiceFor(t) {
    const ex=t.exercise, base=byId.get(ex.example);
    const sol={id:ex.id,code:ex.solution,stdin:ex.stdin,output:ex.output};
    return `<div class="practice"><h3>${t.model?'Extension practice':'Check your understanding'}</h3><span class="exercise-label">01 · Think first</span><p>${safe(t.question)}</p><details class="answer"><summary>Reveal explanation</summary><p>${safe(t.answer)}</p></details><hr style="border:0;border-top:1px solid #e4e5d6;margin:1.3rem 0"><span class="exercise-label">02 · Build and test</span><p>${safe(ex.task)}</p><details class="answer"><summary>Hint</summary><p>${safe(ex.hint)}</p></details>
    <details class="example"><summary>Practice workspace<small>Starts with ${safe(base.title)}. Edit the code to complete the task.</small></summary><div class="example-body">${runner(base,'workspace-'+t.id)}</div></details>
    <details class="solution"><summary>Reveal a worked solution</summary><p>${safe(ex.explanation)}</p>${runner(sol,ex.id,true)}</details><p class="footnote">Compare your reasoning and output with the solution. This workspace has no automatic checks; the Classes mini-project has a separate Check solution button.</p></div>`;
}
function modelLesson() {
    const t=DATA.topics.find(t=>t.model);
    const quiz=DATA.model.quiz.map((q,n)=>`<fieldset class="quiz-question" data-question="${q.id}"><legend>${n+1}. ${safe(q.prompt)}</legend>${q.options.map((o,i)=>`<label><input type="radio" name="${q.id}" value="${i}" ${saved('quiz-'+q.id,'')===String(i)?'checked':''}> ${safe(o)}</label>`).join('')}<p class="quiz-feedback" hidden></p></fieldset>`).join('');
    return DATA.model.html.replace('<!-- EXAMPLES -->',examplesFor(t)).replace('<!-- CHECKED_WORKSPACE -->',runner(byId.get('model-starter'),'model-workspace')).replace('<!-- CHECKED_SOLUTION -->',runner(byId.get('model-solution'))).replace('<!-- QUIZ -->',quiz);
}
function optionalChain() {
    const t=DATA.optional[0],ex=t.exercise,base=byId.get(ex.example);
    const solution={id:ex.id,code:ex.solution,stdin:ex.stdin,output:ex.output};
    return `<details id="linked" class="optional-exercise"><summary>Optional exercise · Link objects into a chain</summary><div class="optional-body"><p>${safe(t.intro)} This is a first look at a linked list.</p><h4>Think first</h4><p>${safe(t.question)}</p><details class="answer"><summary>Explain</summary><p>${safe(t.answer)}</p></details><h4>Your task</h4><p>${safe(ex.task)}</p><p>Expected chains: <code>10 20 30</code>, then <code>10 15 20 30</code>. Counts: 3, 0 for an empty chain, then 4. Assume the chain has no cycles.</p><details class="answer"><summary>Hint 1 · Traverse</summary><p>Use a const Node* cursor. Read the value with cursor->value, then advance to cursor->next until nullptr.</p></details><details class="answer"><summary>Hint 2 · Insert without losing links</summary><p>${safe(ex.hint)}</p></details>${runner(base,'workspace-linked')}<details class="solution"><summary>Reveal a worked solution</summary><p>${safe(ex.explanation)}</p>${runner(solution,ex.id,true)}</details><details class="solution"><summary>Reference: another completed chain</summary>${runner(byId.get('e19'))}</details><p class="footnote">All nodes in this exercise are local objects. Their links do not own storage; do not delete these nodes. Use Run and the expected results to assess your solution; this optional exercise has no automatic code checker.</p></div></details>`;
}
function renderTopic(t) {
    const revision=t.group==='revision';
    const major=DATA.topics.filter(x=>x.group!=='revision').findIndex(x=>x.id===t.id)+2;
    const tag=revision?'h3':'h2';
    return `<section class="topic ${revision?'sublesson':''}" id="${t.id}"><div class="topic-head"><div><span class="eyebrow">${revision?'Revision · Lesson '+t.number:'Topic '+major}</span><${tag}>${safe(t.title)}</${tag}></div><label><input class="complete" type="checkbox" data-topic="${t.id}" ${saved(t.id+'-done','')==='yes'?'checked':''}> Mark reviewed</label></div><p class="topic-intro">${safe(t.intro)}</p>
    ${t.model?modelLesson():(t.lesson||'')+memoryPanel(t)+examplesFor(t)}${practiceFor(t)}${t.id==='dynamic'?optionalChain():''}</section>`;
}
function render() {
    const revision=DATA.topics.filter(t=>t.group==='revision');
    document.querySelector('#topics').innerHTML=`<section id="revision" class="revision-group"><div class="revision-heading"><span class="eyebrow">Topic 1 · Foundations</span><h2>Revision</h2><p>Eight short sublessons refresh the C++ tools you will use throughout OOP. Work through them in order, or revisit a specific skill when you need it.</p></div>${revision.map(renderTopic).join('')}</section>`+DATA.topics.filter(t=>t.group!=='revision').map(renderTopic).join('');
    document.querySelector('#topic-nav').innerHTML=`<div class="revision-nav"><a href="#revision" class="nav-group">01 · Revision</a><div class="nav-children">${revision.map((t,i)=>`<a href="#${t.id}" data-topic="${t.id}">${i+1}. ${safe(t.title)}</a>`).join('')}</div></div>`+DATA.topics.filter(t=>t.group!=='revision').map((t,i)=>`<a href="#${t.id}" data-topic="${t.id}">${String(i+2).padStart(2,'0')} · ${safe(t.title)}${t.model?' <span class="model-tag">Guided</span>':''}</a>`).join('');
    updateProgress();
}
function updateProgress() {
    const count=document.querySelectorAll('.complete:checked').length;
    document.querySelector('#progress').max=DATA.topics.length;
    document.querySelector('#progress').value=count;
    document.querySelector('#progress-text').textContent=`${count} of ${DATA.topics.length} lessons reviewed`;
    const mastery=document.querySelector('#classes-mastery');
    if(mastery)mastery.textContent=`Classes checkpoint: questions ${saved('classes-quiz-passed','')==='yes'?'passed':'not yet passed'} · coding checks ${saved('classes-code-passed','')==='yes'?'passed':'not yet passed'}. Reviewed status is a separate self-check.`;
}
let activeRequest=null;
function resultText(data) {
    const lines=arr=>(arr||[]).map(x=>x.text||'').join('\n');
    const build=data.buildResult||data;
    const sections=[];
    const diagnostics=lines(build.stderr);
    if (diagnostics) sections.push('Compiler messages:\n'+diagnostics.replace(/\x1b\[[0-9;]*m/g,''));
    if (build.code!==0) { sections.push('Compilation failed.'); return sections.join('\n\n'); }
    if (!data.didExecute && !data.execResult) { sections.push('Compiled, but execution was not returned by the service.');return sections.join('\n\n'); }
    const execution=data.execResult||data;
    sections.push(lines(execution.stdout)||'(No standard output)');
    const error=lines(execution.stderr);if(error)sections.push('Standard error:\n'+error);
    const outcome=[];
    if(execution.code!==0)outcome.push(`Exit code: ${execution.code ?? 'unknown'}`);
    if(execution.timedOut)outcome.push('Execution timed out');
    if(execution.truncated)outcome.push('Output truncated');
    if(outcome.length)sections.push(outcome.join(' · '));
    return sections.join('\n\n');
}
async function runProgram(container, checked=false) {
    if(activeRequest){container.querySelector('.status').textContent='Another program is running. Please wait.';return;}
    const submittedCode=container.querySelector('.editor').value;
    const code=checked?'#define main learner_main\n'+submittedCode+'\n'+DATA.model.tests:submittedCode;
    const input=container.querySelector('.stdin').value;
    const out=container.querySelector('.output'),status=container.querySelector('.status');
    const controller=new AbortController();activeRequest=controller;
    const timer=setTimeout(()=>controller.abort(),45000);
    document.querySelectorAll('[data-action="run"],[data-action="check"]').forEach(b=>b.disabled=true);
    out.textContent='Compiling and running…';status.textContent='Sending code and input to Compiler Explorer.';
    try {
        const response=await fetch('https://godbolt.org/api/compiler/g132/compile',{
            method:'POST',headers:{'Content-Type':'application/json','Accept':'application/json'},signal:controller.signal,
            body:JSON.stringify({source:code,options:{userArguments:'-std=c++17 -Wall -Wextra -pedantic',compilerOptions:{executorRequest:true},filters:{execute:true},executeParameters:{args:[],stdin:input},tools:[],libraries:[]},lang:'c++',allowStoreCodeDebug:false})
        });
        if(!response.ok)throw new Error('Compiler service returned HTTP '+response.status);
        const result=await response.json();
        const formatted=resultText(result);
        out.textContent=checked?formatted.replace(/^OOP_CHECKPOINT_PASS(?:\r?\n|$)/gm,'').trimEnd():formatted;
        status.textContent=checked?'Checks finished for the code submitted. Read the individual PASS/FAIL results.':'Finished. Output corresponds to the code and input submitted when Run was clicked.';
        if(checked) {
            const passed=result.didExecute && result.code===0 && (result.stdout||[]).some(x=>x.text==='OOP_CHECKPOINT_PASS');
            const unchanged=container.querySelector('.editor').value===submittedCode;
            save('classes-code-passed',passed && unchanged?'yes':'');updateProgress();
            if(passed && unchanged)status.textContent='All six coding checks passed. Well done—now explain why invalid input preserves the old grade.';
            if(!unchanged)status.textContent='Code changed during the check. Run Check solution again to assess the current version.';
        }
    } catch(error) {
        out.textContent=error.name==='AbortError'?'The request timed out. Try a smaller program or try again later.':`${error.message}\nThe compiler service may be unavailable. Download the code and run it locally, or copy it into https://godbolt.org/.`;
        status.textContent='Run could not be completed.';
    } finally {
        clearTimeout(timer);activeRequest=null;
        document.querySelectorAll('[data-action="run"],[data-action="check"]').forEach(b=>b.disabled=false);
    }
}
function originalFor(container) {
    if(container.dataset.solution==='true')return allLessons.find(t=>t.exercise.id===container.dataset.id).exercise.solution;
    return byId.get(container.dataset.source).code;
}
function traceMarkup(step, previous) {
    if(!step.objects.length)return '<p class="no-objects">Point defines the type. No objects exist yet.</p>';
    return step.objects.map(object=>{
        const old=previous?.objects.find(x=>x.name===object.name);
        return `<div class="object-card"><h4>${safe(object.name)} <span>: Point</span></h4><dl><div class="${!old||old.x!==object.x?'changed':''}"><dt>x</dt><dd>${object.x}</dd></div><div class="${!old||old.y!==object.y?'changed':''}"><dt>y</dt><dd>${object.y}</dd></div></dl><small>Own instance data</small></div>`;
    }).join('');
}
function setupModel() {
    let position=Math.max(0,Math.min(DATA.model.steps.length-1,Number(saved('trace-position','0'))||0));
    function drawTrace() {
        const step=DATA.model.steps[position];
        document.querySelector('#trace-position').textContent=`Step ${position} of ${DATA.model.steps.length-1}`;
        document.querySelector('#trace-code').textContent=step.code;
        document.querySelector('#object-cards').innerHTML=traceMarkup(step,DATA.model.steps[position-1]);
        document.querySelector('#trace-note').textContent=step.note;
        document.querySelector('[data-trace="previous"]').disabled=position===0;
        document.querySelector('[data-trace="next"]').disabled=position===DATA.model.steps.length-1;
        save('trace-position',String(position));
    }
    document.querySelectorAll('[data-trace]').forEach(button=>button.addEventListener('click',()=>{
        position=button.dataset.trace==='reset'?0:Math.max(0,Math.min(DATA.model.steps.length-1,position+(button.dataset.trace==='next'?1:-1)));
        drawTrace();
    }));
    drawTrace();
    const prediction=document.querySelector('#point-prediction');
    prediction.value=saved('point-prediction','');
    prediction.addEventListener('input',()=>save('point-prediction',prediction.value));
    document.querySelector('#check-prediction').addEventListener('click',()=>{
        const expected='(2,3)(0,0)(3,2)(8,0)';
        const correct=prediction.value.replace(/\s/g,'')===expected;
        document.querySelector('#prediction-feedback').textContent=correct?'Correct. Each update changes only its selected object.':'Not quite. Trace the constructor defaults first, then update p2.x and both coordinates of p1. Spaces and line breaks do not affect this check.';
    });
    const form=document.querySelector('#classes-quiz');
    form.addEventListener('submit',event=>{
        event.preventDefault();let score=0,answered=0;
        DATA.model.quiz.forEach(q=>{
            const chosen=form.querySelector(`input[name="${q.id}"]:checked`);
            const feedback=form.querySelector(`[data-question="${q.id}"] .quiz-feedback`);
            const correct=chosen && Number(chosen.value)===q.correct;
            if(chosen)answered++;
            if(correct)score++;
            feedback.hidden=false;
            feedback.textContent=(correct?'Correct. ':chosen?'Revisit this idea. ':'Choose an answer. ')+q.explanation;
            feedback.classList.toggle('correct',!!correct);
        });
        const passed=score===DATA.model.quiz.length;
        save('classes-quiz-passed',passed?'yes':'');
        document.querySelector('#quiz-result').textContent=`${score}/${DATA.model.quiz.length} correct${answered<DATA.model.quiz.length?` · ${DATA.model.quiz.length-answered} unanswered`:''}. ${passed?'Question checkpoint passed.':'Read the explanations, revise your answers, and try again.'}`;
        updateProgress();
    });
    form.addEventListener('change',()=>{
        document.querySelector('#quiz-result').textContent='Selections changed. Check your answers again.';
        form.querySelectorAll('.quiz-feedback').forEach(el=>el.hidden=true);
    });
    document.querySelector('#reset-quiz').addEventListener('click',()=>{
        form.querySelectorAll('input[type="radio"]').forEach(input=>{input.checked=false;input.defaultChecked=false;save('quiz-'+input.name,'');});
        form.querySelectorAll('.quiz-feedback').forEach(el=>el.hidden=true);
        save('classes-quiz-passed','');document.querySelector('#quiz-result').textContent='Questions reset.';updateProgress();
    });
}
let toastTimer;
function toast(message) { const el=document.querySelector('#toast');el.textContent=message;el.hidden=false;clearTimeout(toastTimer);toastTimer=setTimeout(()=>el.hidden=true,2500); }
document.addEventListener('click',async event=>{
    const button=event.target.closest('button[data-action]');if(!button)return;
    const container=button.closest('.runner');if(!container)return;
    const editor=container.querySelector('.editor'),view=container.querySelector('.code-view');
    switch(button.dataset.action) {
        case 'run': await runProgram(container);break;
        case 'check': await runProgram(container,true);break;
        case 'edit': {
            const show=editor.hidden;editor.hidden=!show;view.hidden=show;
            if(!show)view.querySelector('code').innerHTML=highlight(editor.value);
            button.textContent=show?'View code':'Edit code';button.setAttribute('aria-pressed',String(show));
            if(show)editor.focus();break;
        }
        case 'copy':try{await navigator.clipboard.writeText(editor.value);toast('Code copied.');}catch{editor.hidden=false;view.hidden=true;editor.focus();editor.select();toast('Select and copy the code manually.');}break;
        case 'download': {
            const url=URL.createObjectURL(new Blob([editor.value],{type:'text/plain'}));
            const a=document.createElement('a');a.href=url;a.download=container.dataset.id+'.cpp';a.click();setTimeout(()=>URL.revokeObjectURL(url),1000);break;
        }
        case 'reset': {
            if(editor.value!==originalFor(container) && !confirm('Restore the original code and input? Your edits in this workspace will be replaced.'))break;
            editor.value=originalFor(container);view.querySelector('code').innerHTML=highlight(editor.value);
            const stdin=container.dataset.solution==='true'?allLessons.find(t=>t.exercise.id===container.dataset.id).exercise.stdin:byId.get(container.dataset.source).stdin;
            container.querySelector('.stdin').value=stdin||'';
            if(container.dataset.id==='model-workspace'){save('classes-code-passed','');updateProgress();}
            save(container.dataset.id+'-code',editor.value);save(container.dataset.id+'-stdin',stdin||'');
            container.querySelector('.output').textContent='Run the program to see its output.';container.querySelector('.status').textContent='Original code restored.';break;
        }
    }
});
document.addEventListener('input',event=>{
    const runner=event.target.closest('.runner');if(!runner)return;
    if(event.target.matches('.editor')){save(runner.dataset.id+'-code',event.target.value);if(runner.dataset.id==='model-workspace'){save('classes-code-passed','');updateProgress();}}
    if(event.target.matches('.stdin'))save(runner.dataset.id+'-stdin',event.target.value);
});
document.addEventListener('keydown',event=>{
    if(event.target.matches('.editor')&&event.key==='Tab') {
        event.preventDefault();const el=event.target,start=el.selectionStart,end=el.selectionEnd;
        el.setRangeText('    ',start,end,'end');el.dispatchEvent(new Event('input',{bubbles:true}));
    }
});
document.addEventListener('change',event=>{
    if(event.target.closest('#classes-quiz') && event.target.matches('input[type=radio]')) {save('quiz-'+event.target.name,event.target.value);save('classes-quiz-passed','');updateProgress();}
    if(event.target.matches('.complete')){save(event.target.dataset.topic+'-done',event.target.checked?'yes':'');updateProgress();}
});
document.querySelector('#search').addEventListener('input',event=>{
    const q=event.target.value.trim().toLowerCase();let visible=0;
    DATA.topics.forEach(t=>{
        const searchable=[t.title,t.intro,t.question,t.exercise.task,t.lesson||'',t.model?DATA.model.html:'',DATA.memory.find(m=>m.id===t.id)?.title||'',t.id==='dynamic'?JSON.stringify(DATA.optional):'',...DATA.examples.filter(e=>e.topic===t.id).flatMap(e=>[e.title,e.note,e.code])].join(' ').toLowerCase();
        const matches=!q||searchable.includes(q);
        document.getElementById(t.id).hidden=!matches;
        document.querySelector(`#topic-nav a[data-topic="${t.id}"]`).hidden=!matches;
        if(matches)visible++;
    });
    document.querySelector('#revision').hidden=!DATA.topics.some(t=>t.group==='revision'&&!document.getElementById(t.id).hidden);
    document.querySelector('.revision-nav').hidden=document.querySelector('#revision').hidden;
    document.querySelector('#no-results').hidden=visible!==0;
    document.querySelector('#search-status').textContent=q?`${visible} matching topics`:'';
});
document.querySelector('#print').addEventListener('click',()=>window.print());
render();
setupModel();
setupMemory();
if('IntersectionObserver' in window) {
    const observer=new IntersectionObserver(entries=>{
        entries.forEach(entry=>{if(entry.isIntersecting){document.querySelectorAll('#topic-nav a').forEach(a=>a.classList.toggle('active',a.dataset.topic===entry.target.id));}});
    },{rootMargin:'-10% 0px -65% 0px'});
    document.querySelectorAll('.topic').forEach(t=>observer.observe(t));
}
