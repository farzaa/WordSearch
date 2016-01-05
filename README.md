# WordSearch

Main concepts explored in this program: Dynamic memory allocation, memory leak prevention, binary search, traversal of 2D arrays, strings in C, file input, user input

This is a program that has 2 inputs: a sample dictionary which is a list of words and a sample "puzzle" which is simply 
a bunch of letters in a 2D Array.  It then goes through the 2D Array horizontally, vertically, and digonally to find
every single combination of letters (including reversed strings) that show up in the dictionary.

The specific of the input can be found below.

The Dictionary:
First input X has the number of words in the file. The next X lines will include one word per line.

Sample Dictionary:
5

ab


be


he


hi


him

The Puzzle
The first line will have 2 number seperated by a space. The first number will be the height of the puzzle, and then second
number will be the width of the puzzle.  The puzzle itself is an assortment of letters. 

Sample Puzzle: 
3 5


abcde


efghi


jklem

Using the two samples above we come to this output:

ab (1)


be (1)


he (2)


hi (1)

This means in the puzzle, we found 4 matches from the dictionary. The number in front of each word is the number of times
that word showed up in the puzzle. 


