# C++ OOP teaching material

Prepared for Dr. Manaf Gharaibeh, Princess Sumaya University for Technology.

The page contains 18 main topics with 25 core lessons, 40 C++17 examples, and 59 learning activities. Every coding exercise has a starter workspace, a hint, and a complete worked solution. Each supplied example and solution was compiled with GCC using warnings as errors and executed with UndefinedBehaviorSanitizer. The original online checks are retained. New online checks in remote-validation-v2.json cover console I/O, file creation/reading, Point, and both passing and failing versions of the Student checkpoint.

## View the page

Open `teaching/oop/index.html` in a browser. It is self-contained: no web server, build step, or JavaScript/CSS CDN is needed to read the page. Running C++ requires access to Compiler Explorer. If a browser restricts network requests from local files, serve this directory with `python3 -m http.server 8000` and visit `http://localhost:8000/teaching/oop/`.

Examples are highlighted when viewed. Choose **Edit code** to use the editable plain-text source. **Run** executes the current editor contents, even when viewing highlighted code. Enter all standard input before running; this is batch input rather than an interactive terminal. Reset restores code and input, and confirms before discarding changed code. Code, input, and reviewed-topic progress are saved in local browser storage when available. General practice uses self-check explanations. The Classes and Objects model lesson additionally provides a four-line output prediction check, five explained questions, and six code checks for its Student mini-project. These are learning checks, not secure assessment.

The Run action sends only the selected workspace's code and input to `https://godbolt.org/api/compiler/g132/compile`, using its documented execution API. No keys or account are required by this implementation. Service availability, execution limits, compiler availability, and browser cross-origin policy are external dependencies. Errors and timeouts are displayed rather than replaced with canned output. GCC 13.2 was confirmed available and execution-capable during preparation. Configuration is in `app.js`.

## Add to the Hugo website

For a source repository built by Hugo:

1. Copy the provided `teaching/oop/` folder into your Hugo project's **`static/teaching/oop/`** directory. `index.html` is the only file necessary for the page, but copying the whole folder also makes `.cpp` sources available at stable URLs.
2. Find the homepage Teaching section's Markdown source. Academic theme versions differ; commonly it is `content/home/teaching.md` or another file under `content/home/`. Search for `Yarmouk University` or `Object Oriented Programming` to locate it.
3. Insert this subsection before the historical Colorado State University/Yarmouk entries, inside the existing content body, leaving any TOML/YAML front matter intact:

   ```markdown
   ## Princess Sumaya University for Technology

   Teaching materials for my courses:

   - [Object Oriented Programming (11206)](/teaching/oop/)
   ```

4. Run your normal Hugo build and push through your existing GitHub deployment workflow.
5. Check `https://manafhgh.com/teaching/oop/`, the new homepage link, Run, input, and mobile navigation.

For a repository containing only the already-generated website, place `teaching/oop/index.html` directly at that path in the published root. Edit the generated homepage with this equivalent HTML:

```html
<h2>Princess Sumaya University for Technology</h2>
<p>Teaching materials for my courses:</p>
<ul>
  <li><a href="/teaching/oop/">Object Oriented Programming (11206)</a></li>
</ul>
```

Generated homepage edits may be overwritten by the next Hugo build; use the source Markdown when available. Repository-specific edits have not been made because the GitHub repository/source was not provided.

## Source and maintenance

- `teaching/oop/index.html`: self-contained page ready for hosting.
- `teaching/oop/content.json`: examples, notes, sample input, and verified output.
- `teaching/oop/topics.json`: topic sequence, questions, tasks, hints, and solutions.
- `teaching/oop/app.js` and `style.css`: maintainable page behavior and styles.
- `teaching/oop/examples/*.cpp`: 40 examples (including incomplete practice starters) plus 26 coding solutions and the Student checkpoint starter/solution.
- `multifile-point/`: real `point.h`, `point.cpp`, and `main.cpp` project; run `make run`, then `make clean`.
- `verify.py`: compile and execute 69 cases, including the expected failing incomplete checkpoint starter. File-writing programs run in separate temporary working directories. Requires Python 3 and GCC with UBSan support.
- `make_page.py`: regenerate the self-contained page after editing content/styles/script.
- `validation.json`, `remote-validation.json`, `remote-validation-v2.json`: recorded local and external execution results.
- `CHANGES.md`: important corrections and teaching decisions.

After changing examples or solutions, update the JSON and corresponding `.cpp` files, run `python3 verify.py`, then `python3 make_page.py`. The JSON is the source used by the page and the verifier; the `.cpp` files are downloads and should remain consistent.

This package was checked with compiler execution, output checks, HTML generation, and DOM interaction tests (hierarchy, trace, prediction, questions, editing, search, reset, and code-check state). Visual rendering and interaction in an actual browser have not been verified in this environment. The supplied responsive CSS still needs a final browser check on your website.

The original document contains references to TutorialsPoint's inheritance, polymorphism, casting, and overloading tutorials, Programiz's multilevel/multiple inheritance tutorial, and `shorturl.at/oCLP4` for its friend-member example. Those original teaching references are retained here for provenance; no additional tutorial content was copied. This material is for classroom learning, rather than a comprehensive C++ reference.

## Revision and the Classes and Objects model lesson

Revision groups the original first six lessons (functions, recursion, pointers/references, const, scope/static locals, and one-dimensional arrays), followed by console I/O and text-file I/O. The primitive linked-list topic is now an optional exercise within Dynamic Memory. The other remaining course topics are retained. Stable lesson anchors keep existing links usable.

`teaching/oop/classes-lesson.html` contains the guided lesson text. `teaching/oop/model.json` holds the trace steps, five explained questions, coding starter, worked solution, and disclosed coding tests. The object display is a deterministic conceptual trace, not a debugger or a visualization of arbitrary edited code. The examples remain independently runnable.

Progress distinguishes self-reported reviewed lessons from the questions and coding checkpoints. Editing the mini-project after passing invalidates its coding badge. Changing a question answer invalidates its question badge. Previous browser edits and review marks use the same storage namespace as the earlier page.

After editing content, run `python3 verify.py` and `python3 make_page.py`. The verifier refreshes samples but does not infer mathematical correctness solely from a successful exit. To run the DOM checks, install the optional test dependency with `npm install --no-save linkedom`, then run `node verify-page.cjs`. No npm dependency is needed to view or host the self-contained HTML page.

Only `teaching/oop/index.html` needs replacing on your Hugo site, at `static/teaching/oop/index.html`. It contains all code, lesson data, CSS, and JavaScript. No Hugo theme changes are needed for this update. The GitHub-hosted website has not been modified by this package.

## Memory walkthroughs and optional linked-chain exercise

`teaching/oop/memory.json` defines a nine-step pointer/reference trace and an eleven-step allocation/deallocation trace. `memory.js` draws responsive SVG arrows, object/allocation boxes, symbolic targets, and a plain-text state table. Forward/back/restart controls preserve their step in browser storage. Diagrams follow the supplied script and do not inspect edited code. References appear as aliases on the original object, rather than invented separate pointer storage. Released allocations do not retain live displayed values; dangling pointers use dashed amber arrows.

Every diagram state was checked against compiled C++ assertions in `verify-memory-pointers.cpp` and `verify-memory-dynamic.cpp`. No freed pointer is dereferenced or compared in the dynamic assertion trace.

`teaching/oop/optional.json` holds the chain exercise under Dynamic Memory. It asks students to connect local Node objects, print/count a chain (including nullptr), and insert a node without losing the remaining links. Its incomplete starter, staged hints, expected output, complete solution, and original chain reference are available in a collapsed optional exercise. It is excluded from core lesson counts and progress. Existing #linked links still reach the exercise.

Input placeholders read “Enter input before running if required”; supplied sample input is retained. The output formatter omits successful zero exit codes but retains nonzero/unknown exit codes, compilation diagnostics, runtime errors, timeouts, and truncation notices.
