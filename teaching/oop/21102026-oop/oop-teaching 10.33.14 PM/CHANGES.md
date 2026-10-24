# Important corrections and teaching decisions

- Expanded the reference swap into an explicit value/reference comparison.
- Added missing headers and main functions to incomplete snippets. Kept deliberately invalid calls commented so the supplied programs compile.
- Initialized pointers to `nullptr` and explained reference assignment without printing platform-specific addresses.
- Corrected the recursive array sum to call `sumArray_recursive`, rather than an unrelated `sum`. Corrected initializer comments and removed random data so output is reproducible. Explained that `sizeof` is an operator and array parameters do not preserve array size.
- Used const queries and const-reference parameters for Point; kept the original axis result of -1. The lifetime example uses separate value/reference calls to make copy construction easy to trace without relying on optional return-value copies.
- Supplied missing complete examples for interface/implementation separation, Line composition, and multiple/multilevel inheritance. Added the real three-file Point project.
- Unified Student GPA validation at 0–100, including constructor use. The source previously allowed default GPA 0 but setters required at least 35. This range is a teaching choice, not a statement of university grading policy.
- Initialized the temperature accumulator, rejected empty averages, validated scale labels, and corrected **temperature-difference** conversion: Fahrenheit-to-Celsius changes multiply by 5/9 without subtracting 32; Celsius-to-Fahrenheit changes multiply by 9/5 without adding 32. The original floating-point reading expressions did not themselves suffer integer division, because multiplication by a float occurred first.
- Made the Box count track live objects with a destructor. Its retained `modifyCount` method is explicitly labeled as a demonstration of access rules that breaks the counter's intended meaning; normal examples/exercises do not call it.
- Kept the primitive linked list as non-owning links to local objects. It does not pretend to be a general owning list or handle cycles.
- Removed executed memory leaks from the dynamic-memory example, initialized array elements, and paired every allocation with its matching deallocation. Explained why deleting a pointer to a local variable is invalid.
- Reworked the owning grade array to implement the Rule of Three: destructor, deep-copy constructor, and deep-copy assignment. Added input/index/range validation and a positive-size requirement. Introduced copy assignment here because safe ownership requires it, and noted the Rule of Zero alternative using `std::vector`.
- Fixed friend-function initialization comments and narrowed the friend-member example's parameter to a const reference.
- Showed both returned values and returned references in the `this` example.
- Corrected inheritance explanations: private base data remains in the base subobject. Removed an unused, undefined member declaration.
- Added virtual base destructors, explicit overrides, a proper Penguin constructor, and cleanup of the dynamically allocated Cat. Removed the blanket claim that direct virtual calls are necessarily statically bound: their concrete type can allow compiler devirtualization, but the language semantics remain virtual.
- Corrected the Circle downcast failure message and explained failed pointer casts versus failed reference casts. Distinguished pointer/reference upcasting from by-value object slicing.
- Removed the duplicate Student operator example. Made comparison queries const, equality return bool, and `+=` return the updated Student by reference. Explained exact floating-point equality limits.
- Implemented prefix/postfix increment conventions and made stream extraction leave the object unchanged if input fails.
- Added 24 understanding questions and 24 programming tasks, with complete compiled solutions. Exercise workspaces begin with a relevant working example, not an intentionally broken program. Solutions are hidden initially but publicly present in the static page source, which suits practice rather than graded assessment.


# Version 2: Revision and Classes and Objects

- Grouped the six introductory lessons under Revision while retaining their anchors; added console I/O and real text-file I/O with complete checked examples and exercises.
- Removed source-origin subtitles from every example title.
- Expanded Classes and Objects with prerequisites, learning objectives, class/object/state/interface explanations, constructor/default argument/const discussion, an accessible object-state stepper, output prediction feedback, guided experiments, a validated Student mini-project, staged hints, and a five-question checkpoint.
- Added six compiled code checks that accept the worked solution and reject the incomplete starter. Reviewed status and passed checkpoints are tracked separately. Editing a passed solution invalidates its code-check badge.
- Retained later course topics and their examples/exercises. Added standalone downloads for the new material.
- File examples use their own temporary working directory during local validation; online files are temporary and cannot access student computer files.


# Version 3: input/output display and memory

- Updated every standard-input placeholder to “Enter input before running if required”.
- Suppressed successful Exit code: 0 messages while keeping errors and runtime/service diagnostics.
- Added accessible, stepped SVG memory diagrams to Pointers and References and Dynamic Memory. Paired them with runnable trace programs and compiled state assertions.
- Moved the primitive linked-list topic into a collapsed optional exercise in Dynamic Memory, retaining its anchor and original runnable reference. Added a chain-building/traversal/insertion starter, hints, and full solution.
- Kept core progress separate from the optional exercise; core lessons now total 25 under 18 main topics.
