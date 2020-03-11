# Software-Opt-Lab2

README
Written by: Ryan Winters
Email: ryanwint@usc.edu
Date: 1-23-19

EE599 Lab 2 ReadMe File



Usage:
Use 'gcc -o run EE599_Lab2_2856568151.c' to compile.
Then './run' to run it.


Summary:
The code reads in two matrices and multiplies them together via different methods. The first method
is the naive method which uses three for loops. The second method is Strassen's method.
I save each output from each method into an output file.
I start a timer before each algorithm and save the time in another output file.


Code used for reference:
I used parts of the recursive function found at the website below:
https://www.geeksforgeeks.org/matrix-multiplication-recursive/
It is implemented in lines 22-51 of my code

Used for reading in a file line by line.
https://www.daniweb.com/programming/software-development/code/216411/reading-a-file-line-by-line
Implemented at lines 99-147 of my code.

Used for converting input string to numbers
https://www.geeksforgeeks.org/converting-strings-numbers-cc/
Implemented at lines 132-136

Used for multiplying Matrices
 https://www.programmingsimplified.com/c-program-multiply-matrices
 Implemented at lines 209-217 and sporadically throughout.
