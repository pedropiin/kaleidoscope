# Kaleidoscope 

Repo to store the implementation of the Kaleidoscope programming languages. 

Implementation based on its respective LLVM tutorial ([Kaleidoscope Tutorial](https://llvm.org/docs/tutorial/index.html)). 

It only differs from the original in the sense that is reformatted to follow an OOP approach. So code generation is done with a Visitor Pattern, each frontend "pass" has its own class (and file, given the 'single-file strategy' used in the og).
