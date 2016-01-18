# misc-cpp-projs

The misc-cpp-proj is a public GIT repository where 
[Rubens](http://www.rubens-gomes.com) keeps some personal C++
programming projects.  The source code that is provided are 
mainly used for demonostrations and learning purposes only.


## Environment

The development environment consists of Linux (or Linux-Like)
environment with C++ GNU compiler and standard C++11 libraries.
Also, the Boost C++ source libraries are also installed.

## Build and Run 

A simple Makefile is provided in each folder to build the 
application.  The user should review the Makefile to ensure
that its settings (like INCLUDE and LIB paths) are appropriately
set for the environment.

To run a build at the Linux shell type:

    make clean; make

To clean your .depend file listing:

    make distclean
