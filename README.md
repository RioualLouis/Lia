# C-Neural-Network

A neural network built in C from scratch.



--- 



#### Identified errors

* A compiled file is tracked by git that probably shouldn’t be. Compare your `.gitignore` patterns with the name of your executable.

* `error.h` and `error.c` disagree on the name of one function. Nothing breaks yet; think about what the linker will say on the first call.

* In `mat_mult`, compare the type of the accumulator with the type of the data it sums.

* `create_random_vect` produces integers from 0 to range - 1. Ask yourself what range and sign of values a network’s initial weights should have, and why.

* `-ansi` in the `Makefile` means C89. Fine if intentional, but it forbids some things you may want later (// comments, declarations mixed with code, inline).

