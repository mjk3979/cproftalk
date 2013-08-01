cproftalk
=========

A proftalk interpreter written in C that is designed for speed and with the goal of eventually using CUDA to evaluate.

What is proftalk?
=================
proftalk is a cool scheme variant designed by @algorithmicist and myself. It was designed for automatic parallelization of code. However, the original proftalk interpreter was quickly hacked together in Java due to class requirements and time constraints. Since this didn't do the awesome idea justice, I have decided to rewrite everything in C, and try to improve on the idea as I go. @algorithmicist has already rewritten a lot of the code in Go, and that project is called golftalk.

To compile
==========
On a GNU/Linux machine, all you should need to do is run make. It's that easy. If you're on a Windows or Mac machine, then I have no idea.

To use
======
Currently code is interpreted by the test_evaluator binary. Just pipe files to that binary on stdin and it will evaluate it. Don't expect much though, no alot of things have been implemented yet.
