cproftalk
=========

A proftalk interpreter written in C that is designed for a good speedup with the goal of eventually using CUDA to evaluate.

What is proftalk?
=================
proftalk is a cool scheme variant designed by algorithmicist and myself. It was designed for automatic parallelization of code. However, the original proftalk interpreter was quickly hacked together in Java due to class requirements and time constraints. Since this didn't do the awesome idea justice, I have decided to rewrite everything in C, and try to improve on the idea as I go. algorithmicist has already rewritten a lot of the code in Go, and that project is called golftalk.

Keywords
========
algorithmicist and I both go to RIT (which is an awesome university btw). When we decided to make this scheme variant, we wanted to give it something unique, so we decided to make the keywords phrases that our professors often say. I'll eventually work on documenting what the mapping is, but until then use the source code to figure it out.

To compile
==========
On a GNU/Linux machine, all you should need to do is run make. It's that easy. If you're on a Windows or Mac machine, then I have no idea.

To use
======
Currently code is interpreted by the test_evaluator binary. Just pipe files to that binary on stdin and it will evaluate it. Don't expect much though, not alot of things have been implemented yet.

Examples
========
Look at fib.proftalk for a simple example. It defines a function that calculates Fibonacci numbers. I actually forgot a lot of Scheme since I learned it, so I don't think what my interpreter does is correct, and therefore this example code is probably not valid scheme.
