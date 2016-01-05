# WordSearch

**Main concepts explored in this program:** 

Dynamic memory allocation, memory leak prevention, binary search, traversal of 2D arrays, strings in C, file input, user input

**Description:**


This is a program that has 2 inputs: a sample dictionary (read from a file) which is a list of words and a sample "puzzle" (read from the keyboard) which is simply a bunch of letters in a 2D Array.  It then goes through the 2D Array horizontally, vertically, and digonally to find every single combination of letters (including reversed strings) that show up in the dictionary.

The specifics of the input can be found below.

**The Dictionary:**


First input X has the number of words in the file. The next X lines will include one word per line. The max word length (currently set to 20) can be changed in the "WordSearch.h" file. 

**Sample Dictionary:**


5

ab


be


he


hi


him

**The Puzzle:**


The first line will have 2 number seperated by a space. The first number will be the height of the puzzle, and then second
number will be the width of the puzzle.  The puzzle itself is an assortment of letters. 

**Sample Puzzle:** 


3 5


abcde


efghi


jklem

**Using the two samples above we come to this output:**

ab (1)


be (1)


he (2)


hi (1)

This means in the puzzle, we found 4 matches from the dictionary. "ab" was found going horizontally in Row 1, "be" was found going diagonally from Row 1 to Row 2, "he" was found once going vertically from Row 2 to Row 3, and once going diagonally in reverse from Row 2 to Row 1, "hi" was found go horiozntally in Row 2. The number in front of each word is the number of times
that word showed up in the puzzle. 


