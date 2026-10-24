"""Compile and execute all examples and exercise solutions with GCC."""
import concurrent.futures, json, subprocess, tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent / 'teaching/oop'
examples = json.loads((ROOT/'content.json').read_text())
topics = json.loads((ROOT/'topics.json').read_text())
optional = json.loads((ROOT/'optional.json').read_text())
lessons = topics + optional
model = json.loads((ROOT/'model.json').read_text())
jobs = [(e['id'],e['code'],e['stdin']) for e in examples]
jobs += [(t['exercise']['id'],t['exercise']['solution'],t['exercise']['stdin']) for t in lessons]
jobs += [('model-solution', model['solution'], ''),
         ('model-checks-solution', '#define main learner_main\n'+model['solution']+'\n'+model['tests'], ''),
         ('model-checks-starter', '#define main learner_main\n'+model['starter']+'\n'+model['tests'], '')]
def verify(job):
    name, code, stdin = job
    with tempfile.TemporaryDirectory() as folder:
        source = Path(folder)/'main.cpp'; binary=Path(folder)/'program'
        source.write_text(code)
        compiled=subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Wpedantic','-Werror',
            '-fsanitize=undefined','-fno-sanitize-recover=all',str(source),'-o',str(binary)],capture_output=True,text=True)
        if compiled.returncode:
            return dict(id=name,passed=False,diagnostics=compiled.stderr)
        run=subprocess.run([str(binary)],input=stdin,capture_output=True,text=True,timeout=10,cwd=folder)
        expected=1 if name=='model-checks-starter' else 0
        passed=run.returncode==expected and not run.stderr
        if name=='model-checks-solution': passed=passed and 'OOP_CHECKPOINT_PASS' in run.stdout
        if name=='model-checks-starter': passed=passed and 'FAIL:' in run.stdout and 'OOP_CHECKPOINT_PASS' not in run.stdout
        return dict(id=name,passed=passed,exit_code=run.returncode,output=run.stdout,diagnostics=run.stderr)
results=list(concurrent.futures.ThreadPoolExecutor(max_workers=4).map(verify,jobs))
for r in results:
    print(r['id'], 'PASS' if r['passed'] else 'FAIL',r.get('diagnostics',''))
for e in examples:
    r=next(r for r in results if r['id']==e['id'])
    if r['passed']: e['output']=r['output']
for t in lessons:
    r=next(r for r in results if r['id']==t['exercise']['id'])
    if r['passed']:t['exercise']['output']=r['output']
(ROOT/'content.json').write_text(json.dumps(examples,indent=2))
(ROOT/'topics.json').write_text(json.dumps(topics,indent=2))
(ROOT/'optional.json').write_text(json.dumps(optional,indent=2))
model['solutionOutput']=next(r['output'] for r in results if r['id']=='model-solution')
(ROOT/'model.json').write_text(json.dumps(model,indent=2))
(ROOT.parent.parent/'validation.json').write_text(json.dumps(results,indent=2))
if not all(r['passed'] for r in results): raise SystemExit(1)
print(f'All {len(results)} programs passed warnings-as-errors and UndefinedBehaviorSanitizer checks.')
