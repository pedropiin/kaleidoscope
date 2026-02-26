# kaleidoscope

Simple toy programming language built based off of the [LLVM tutorial](https://llvm.org/docs/tutorial/index.html). 

This code only differs from the original in the sense that is reformatted
to follow an OOP approach. So code generation is done with a Visitor Pattern, each frontend "pass" has its own class (and file, given 
that the og is single-file). 