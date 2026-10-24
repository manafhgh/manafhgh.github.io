"""Generate a self-contained HTML page after verify.py succeeds."""
import json, re
from pathlib import Path
root=Path(__file__).resolve().parent/'teaching/oop'
data={'examples':json.loads((root/'content.json').read_text()),'topics':json.loads((root/'topics.json').read_text())}
data['memory']=json.loads((root/'memory.json').read_text())
data['optional']=json.loads((root/'optional.json').read_text())
data['model']=json.loads((root/'model.json').read_text())
data['model']['html']=(root/'classes-lesson.html').read_text()
payload=json.dumps(data,ensure_ascii=False).replace('</',r'<\/')
html='''<!doctype html>
<html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1">
<title>Object Oriented Programming | Manaf Gharaibeh</title>
<meta name="description" content="C++ OOP examples, runnable programs, and practice exercises for PSUT students, by Dr. Manaf Gharaibeh.">
<style>STYLE</style></head><body>
<a class="skip" href="#main">Skip to learning material</a>
<header><a href="https://manafhgh.com/"><strong>MANAF GHARAIBEH</strong></a><span>Princess Sumaya University for Technology</span><a href="https://manafhgh.com/#teaching">← Teaching</a></header>
<div class="shell"><aside class="sidebar"><span class="sidebar-title">Course companion · 11206</span><details open><summary>Explore the topics</summary><label for="search" class="footnote">Search topics and code</label><input id="search" type="search" placeholder="e.g. constructor, pointer…"><div id="search-status" class="footnote" role="status"></div><nav id="topic-nav" aria-label="Course topics"></nav></details><div class="progress"><span id="progress-text"></span><progress id="progress" max="24" value="0" aria-label="Topics reviewed"></progress><div>Edits and progress are saved in this browser when storage is available.</div></div><button id="print" class="print-button">Print current view</button></aside>
<main id="main"><span class="eyebrow">PSUT · C++ learning material</span><h1>Object Oriented<br>Programming</h1><p class="lead">Read it. Predict it. Run it. Build on it.<br>A guided collection of classroom examples and exercises by Dr. Manaf Gharaibeh.</p><div class="stats"><span><strong>24</strong>topics</span><span><strong>32</strong>examples</span><span><strong>48</strong>exercises</span></div>
<div class="intro-note"><p><strong>Start with a prediction.</strong> Read each example, work out what it should do, then run it. Use <strong>Edit code</strong> to experiment and <strong>Reset</strong> to restore the original.</p><p>For programs using <code>cin</code>, enter all input before pressing Run. Code and input are sent to <a href="https://godbolt.org/" target="_blank" rel="noopener">Compiler Explorer</a>; execution requires internet access and service availability. The examples use C++17.</p><p>Intentional errors stay commented out so the supplied programs compile. Sample output is from verified local runs. Exercises have hints, editable workspaces, and worked solutions.</p></div>
<noscript>This page requires JavaScript for its examples and controls. Downloaded .cpp files can be compiled locally.</noscript><div id="no-results" class="empty" hidden>No matching topics. Try a different search.</div><div id="topics"></div><footer>Adapted and corrected from OOP Examples, Fall 2022. Additional examples fill gaps in the source document. <a href="https://manafhgh.com/#teaching">Return to Teaching</a></footer></main></div><div id="toast" class="global-status" role="status" hidden></div>
<script>window.OOP_DATA=PAYLOAD;</script><script>APP</script></body></html>'''
html=html.replace('max="24"','max="26"').replace('<strong>24</strong>topics','<strong>19</strong>topics').replace('<strong>32</strong>examples','<strong>37</strong>examples').replace('<strong>48</strong>exercises','<strong>59</strong>activities')
html=html.replace('Adapted and corrected from OOP Examples, Fall 2022. Additional examples fill gaps in the source document.','C++ learning material · Dr. Manaf Gharaibeh · Princess Sumaya University for Technology.')
html=html.replace('A guided collection of classroom examples and exercises by Dr. Manaf Gharaibeh.','Revision, runnable examples, and a guided Classes and Objects lesson by Dr. Manaf Gharaibeh.')
html=html.replace('Exercises have hints, editable workspaces, and worked solutions.','Revision groups eight foundation lessons. Classes and Objects adds a visual trace, prediction feedback, and a mini-project with six coding checks. Other exercises have hints and worked solutions.')
main_count=1+sum(t.get('group')!='revision' for t in data['topics'])
activity_count=2*(len(data['topics'])+len(data['optional']))+7
html=re.sub(r'<div class="stats">.*?</div>',f'<div class="stats"><span><strong>{main_count}</strong>topics</span><span><strong>{len(data["examples"])}</strong>examples</span><span><strong>{activity_count}</strong>activities</span></div>',html)
html=re.sub(r'(<progress id="progress" max=")\d+',lambda m:m[1]+str(len(data['topics'])),html)
html=html.replace('STYLE',(root/'style.css').read_text()).replace('PAYLOAD',payload).replace('APP',(root/'memory.js').read_text()+'\n'+(root/'app.js').read_text())
(root/'index.html').write_text(html)
print(root/'index.html')
