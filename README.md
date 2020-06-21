Sorting Algorithms
==================

[![Run on Repl.it](https://repl.it/badge/github/rswinkle/sorting)](https://repl.it/github/rswinkle/sorting)

This is just a set of sorting algorithms and a benchmarking program.

I'll add several more algorithms and make some much needed
improvements to some to make tmem more competetive.

I realize that clock() isn't the most accurate/precise timing method
but it's simple to use and will result in the same ranking even if
those numbers aren't actually milliseconds.

"The clock() function returns the processor time since the program started, or - 1 if
that information is unavailable. To convert the return value to seconds, divide it
by CLOCKS_PER_SEC. (Note: if your compiler is POSIX compliant, then CLOCKS_PER_SEC is
always defined as 1000000.) "

Building and Running
====================

You can use the included makefile:

    cd build
    make
    ./benchmark

Or you can regenerate it or another build system using premake5

    premake5 gmake
    cd build
    make
    ./benchmark

There's benchmark is the main C program that I usually update and test with new algorithms
and cppbenchmark which I only occasionally use, mostly just to make sure everything still compiles
and runs the same as C++.

The results are pretty self explanatory but you can redirect them to a file (output.dat) and then
run plotbarchart.py to get a "nice" bar chart of the data.  See heapsort_times.png and quicksort_times.png
for old examples.
