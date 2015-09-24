Sorting Algorithms
==================

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
