//Farzain Majeed 
//UCF 2015
//Past Assignment

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This file holds our struct/fucntion definitions and some important values. 
#include "WordSearch.h"


//This reads in the dictionary file which holds the words we will be looking for.
//We will store the words in a 2D array.
int readDictionary(Dictionary *dict) {

	int i;
	char *test = malloc(sizeof(char) * (MAX_WORD_LENGTH + 1));
	FILE *ifp = fopen("dictionary.txt", "r");
	fscanf(ifp, "%d", &(dict->size));
	//Allocate memory for each individual array in the 2D Array
	dict->words = malloc(sizeof(char *) * dict->size);
	dict->counts = malloc(sizeof(int) * dict->size);
	for (i=0; i<dict->size; i++) {
		dict->counts[i] = 0;
	}

	if(dict->words == NULL){
			destroyDictionary(dict);
			return 0;
      }  
    //Just in case, I clear up any garbage data initially in test.
    memset(&test[0], 0, sizeof(test));    
	for(i=0; i<dict->size; i++) {
		//"test" is placeholder for the word and changes at every line
		fscanf(ifp, "%s", test);
		//Allocate exact amount of memory for each word to be put in array
		dict->words[i] = malloc(sizeof(char) * (strlen(test)));

		//This is in case memory isn't properly allocated. 
		if(dict->words[i] == NULL) {
			destroyDictionary(dict);
			return 0;
		}

		//Copy string into array.
		//We don't use string literal b/c that would cause a memory leak.
		strcpy(dict->words[i], test);
	}

	free(test);
	//close the file! 
	fclose(ifp);
	return 1;
}

//This fucntion will free any memory associated with the dictionary
//when the program exits.
void destroyDictionary(Dictionary *dict) {
	int i;

	for (i=0; i<dict->size; i++) {
		free (dict->words[i]);
		dict->words[i] = NULL;
	}
	//Free everything piece by piece!
	free (dict->words);
	dict->words = NULL;   
	dict->size = 0;
	free (dict->counts);
	dict->counts = NULL;
	free (dict);
	dict = NULL;
}

//Our puzzle is actually read from the keyboard but it is built
//very similarly to the dictionary with a 2D Array.
int readPuzzle(WordSearchPuzzle *puzzle) {

	int j;
	char *holder;

	//Here I grab the dimensions of the 2D Array we want to build. 
	scanf("%d", &(puzzle->height));
	scanf("%d", &(puzzle->width));

	//First lets allocate for the Array of arrays (hence a 2D Array)
	puzzle->grid = malloc(sizeof(char *) * (puzzle->height));

	//Once again, I include this as a saftey measure. 
	if (puzzle->grid == NULL) {
			destroyPuzzle(puzzle);
			return 0;
	}
	//Lets also allocate memory for out holder;
	holder = malloc(sizeof(char)*((puzzle->width)+1));
	//Just in case, I clear up any garbage data initially in holder.
	memset(&holder[0], 0, sizeof(holder));

	if (holder == NULL) {
		free(holder);
		return 0;
	}
	for (j=0; j<puzzle->height; j++) {
		//printf("in\n");
		scanf("%s", holder);
		//Now lets allocate each indivdual array 
		puzzle->grid[j] = malloc(sizeof(char) * (puzzle->width)+1);

		if (puzzle->grid[j] == NULL) {
			destroyPuzzle(puzzle);
			return 0;
		}
		//Lets copy whats in our holder in our brand new array we just malloc'd
		strcpy(puzzle->grid[j], holder);		
	}
	free(holder);
	//Puzzle reading was sucecssful!
	return 1;
}

//This fucntion will free any memory associated with the puzzle
//when the program exits.
void destroyPuzzle(WordSearchPuzzle *puzzle) {

	int i;

	for (i=0; i<puzzle->height; i++) {
		free (puzzle->grid[i]);
		puzzle->grid[i] = NULL;
	}

	//Just like destroy dictionary, lets destory this piece by piece
	free (puzzle->grid);
	puzzle->grid = NULL;   
	puzzle->height = 0;
	puzzle->width = 0;
	free(puzzle);
	puzzle = NULL;
}

//This is the heart of the program, it goes through our puzzle horizontally,
//vertically, and diagonally and picks up every single combination of letters
//even backwards. 
int puzzlePossibilties(WordSearchPuzzle *puzzle, Dictionary *dict) {
	int i, j, k, x, o, n, r, z, c, p = 0;

	//All these declarations shall make sense later
	char temp;
    char *singleStrings;
    char **test;
    char test2[301];
    char **testerArray;
    char testerArraySingle[301];
    char srcH[301];
    char destH[301];
    char srcV[301];
    char destV[301];
    char srcD[301];
	char destD[301];

    //Lets take care of single chars first, becuse single chars count
    //as a word.
    singleStrings = malloc(sizeof(char) * (2));

    if (singleStrings == NULL) {
    	free(singleStrings);
    	singleStrings = NULL;
    }
    strcpy(singleStrings, "");
    singleStrings[1] = '\0';
    //Above I malloc a string for one char and set the ending code.
    for (i=0; i<puzzle->height; i++) {
    	for (j=0; j< puzzle->width; j++) {
    		  singleStrings[0] = puzzle->grid[i][j];
    		  //Finally, we check if theres a match.
    		  checkString(dict, singleStrings);
    	}
    }

   //Now lets look for the horizontal possibilites.
   for (i=0; i<puzzle->height; i++) {
       for (k=0; k<puzzle->width; k++) {
       		//I still need to make sure I'm not printing single chars!
       		//This conditional takes care of that
       		for (x=2; x<=puzzle->width; x++) {
       			//This is basically to avoid duplicates
       			if(strlen(puzzle->grid[i]+k) < x)
       				continue;
       			//I want to clear the array of any garbage.
	       		memset(&destH[0], 0, sizeof(destH));
	       		memset(&srcH[0], 0, sizeof(srcH));
	       		//Copy the string I want to work with into srcH
		   		strcpy(srcH, puzzle->grid[i]+k);
		   		//Slice that string up using strncpy
		   		strncpy(destH, srcH, x);
		   		checkString(dict, destH);
		   		//Here is the code to check the backwards string.
		   		z = 0;
   				p = strlen(destH) - 1;
  				while (z < p) {
	     			temp = destH[z];
	      			destH[z] = destH[p];
	      			destH[p] = temp;
	      			z++;
	      			p--;
   				}
   				checkString(dict, destH);
	   		}
	   	}
	   		
	}

   //Now lets create vertical possibilties.
   //First I'm going to create a 2D Array to easily work with
   //Pretty much just how I did it in the horizontal function
   //Except now its a little harder since I have to make my strings manually.
   test2[puzzle->height+1] = '\0';

   test = malloc(sizeof(char*) * puzzle->width);
   if (test == NULL) {
      free(test);
      test = NULL;
      return 0;	
   }

    //Lets make some strings here. I just go in every col, grabs the chars
   //And put it in my 2D array.
   for (i=0; i<puzzle->width; i++) {
   		//I malloc my array here which is going to have my vertical strings
   		test[i] = malloc(sizeof(char) * ((puzzle->height)+1));
		for (k=0; k<puzzle->height; k++) {
			test2[k] = puzzle->grid[k][i];
		}
		//Copy my test array into my 2D Array
		strcpy(test[i], test2);
	}
	//Here is where I actually go through each vertical possibility using
	//the strings i just made above. 
	for (i=0; i<puzzle->width; i++) {
       for (k=0; k<puzzle->height; k++) {
       		for (x=2; x<=puzzle->height; x++) {

       			if(strlen(test[i]+k) < x)
       				continue;
       			//I once again clear my array of any garbage it may have
       			memset(&destV[0], 0, sizeof(destV));
       			memset(&srcV[0], 0, sizeof(srcV));
		   		strcpy(srcV, test[i]+k);
		   		strncpy(destV, srcV, x);
		   		checkString(dict, destV);

		   		//Reverse code once again, this can be put in its own function.
		   		z = 0;
   				p = strlen(destV) - 1;
  				while (z < p) {
	     			temp = destV[z];
	      			destV[z] = destV[p];
	      			destV[p] = temp;
	      			z++;
	      			p--;
   				}
   				checkString(dict, destV);
       		}
    	}
    }

    //Now lets get to making those pesky diagonal possibilties 
    //Here I am once again creating a 2D array to work with so
    //I can later slice it all up.
    testerArray = malloc(sizeof(char *) * (100000));
    if (testerArray == NULL) {
      free(testerArray);
      testerArray = NULL;
      return 0;	
    }
    testerArraySingle[puzzle->width-1] = '\0';

    //My for loops get a little complicated. My r var is what I use
    //to keep track of my 2D Array I am building. 
    r = 0;
    //Here I go from the top left to the bottom right of my puzzle
	for (n=0; n<puzzle->width-1; n++) {
		memset(&testerArraySingle[0], 0, sizeof(testerArraySingle));
		//int c is what I use to keep track of my string making array.
		c = 0;
	    for (i=0,j=n; i<puzzle->height; i++,j++) {
			testerArraySingle[c] = puzzle->grid[i][j];
			c++;
	    }

	   r++; 
	   testerArray[r] = malloc(sizeof(char) * (puzzle->width+1));	
    
	   strcpy(testerArray[r], testerArraySingle);
	}



	//The above loop leaves some holes in the bottom left of the puzzle.
	//This fixes that. 
	for (n=1; n<puzzle->height-1; n++) {
		memset(&testerArraySingle[0], 0, sizeof(testerArraySingle));
		c = 0;
	    for (i=n,j=0; i<puzzle->height; i++,j++) {	
	    	testerArraySingle[c] = puzzle->grid[i][j];
			c++;
	    }

	    r++;
   		testerArray[r] = malloc(sizeof(char) * (puzzle->width+1));
   		strcpy(testerArray[r], testerArraySingle);
   		//printf("Going out.....%s at %d \n", testerArray[r], r);
		//PRINT OUT INNER TOP LEFT TO BOTTOM RIGHT
	}

	//This loop goes from the top right to the bottom left
	//So this is the opposite diagonal
	for (n=1; n<puzzle->width+1; n++) {
		memset(&testerArraySingle[0], 0, sizeof(testerArraySingle));
		c =0;
	    for (i=0,j=n; i<puzzle->height; i++,j--) {
	    	if (j== puzzle->width)
	    		break;
			testerArraySingle[c] = puzzle->grid[i][j];
			c++;
	    }
	 //Some parts of my array were just blank spaces, this fixes that
	 if (strcmp(testerArraySingle, "") != 0) {
	    	r++;
   			testerArray[r] = malloc(sizeof(char) * (puzzle->width+1));
   			strcpy(testerArray[r], testerArraySingle);	
   		}

	}

	//The above loop still leaves holes is the puzzle!
	//So just like before I made this loop to fix that patch. 
	for (n=1; n<puzzle->height+1; n++) {
		memset(&testerArraySingle[0], 0, sizeof(testerArraySingle));
		c = 0;
	    for (i=n,j=puzzle->width-1; i<puzzle->height; i++,j--) {
	    	if (i== puzzle->height-1 && j== puzzle->width-1)
	    		break;
			testerArraySingle[c] = puzzle->grid[i][j];
			c++;
	    }

	    if (strcmp(testerArraySingle, "") != 0) {
	    	r++;
   			testerArray[r] = malloc(sizeof(char) * (puzzle->width+1));
   			strcpy(testerArray[r], testerArraySingle);
   		}
	
	}

	//This is where I slice up my 2D array full of my diagonal combos.

	for (i=1; i<=r; i++) {
       for (k=0; k<puzzle->width; k++) {
       		for (x=2; x<=puzzle->width; x++) {
       			//I still need to make sure I'm not printing single chars!
       			//This conditional takes care of that
       			if(strlen(testerArray[i]+k) < x)
       				continue;
       			if (strcmp(testerArray[i]+k, "") != 0) {

	       			memset(&destD[0], 0, sizeof(destD));
	       			memset(&srcD[0], 0, sizeof(srcD));
			   		strcpy(srcD, testerArray[i]+k);

			   		strncpy(destD, srcD, x);
			   		checkString(dict, destD);
		   		}
		   		z = 0;
   				p = strlen(destD) - 1;
  				while (z < p) {
	     			temp = destD[z];
	      			destD[z] = destD[p];
	      			destD[p] = temp;
	      			z++;
	      			p--;
   				}
   				checkString(dict, destD);

       		}
    	}
    }
    //Avoid memory leaks like the plague.
    free(singleStrings);

    for (i=0; i<puzzle->height; i++) {
		free (testerArray[i]);
		testerArray[i] = NULL;
	}
    for (i=0; i<puzzle->width; i++) {
		free (test[i]);
		test[i] = NULL;
	}
	free(test);
	free(testerArray);
	return 1;	
}

//Binary search to check for likeness. O(logn) baby!
int checkString(Dictionary *dict, char *str) {
		int lo = 0, hi = dict->size - 1, mid;
		while (hi >= lo)
		{
			mid = lo + (hi  - lo) / 2;
			//if the string is "less than" move to the left
			if (strcmp(str, dict->words[mid]) < 0)
				hi = mid - 1;
			
			//if the string is "less than" move to the right 
			else if (strcmp(str, dict->words[mid]) > 0)
				lo = mid + 1;
			// otherwise, we found the key!
			else {	
				dict->counts[mid]++;
				//printf("found it homie %s\n", str); 
				//printf("%s (%d)\n", str, dict->counts[mid]);
				return 1; 
			}
		}
		
		return 0;
}

int main(void) {

	int dictionaryReturn;
	int puzzleReturn;
	int i;
	//Create the structs and send them to the methods!
	Dictionary *dict = malloc(sizeof(Dictionary));
	dictionaryReturn = readDictionary(dict);
	WordSearchPuzzle *puzzle = malloc(sizeof(WordSearchPuzzle));
	puzzleReturn = readPuzzle(puzzle);
	//This methods creates all the word combos
	puzzlePossibilties(puzzle, dict);
	for (i=0; i<dict->size;i++) {
		if (dict->counts[i] == 0)
			continue;
		printf("%s (%d)\n", dict->words[i], dict->counts[i]);
		
	}
	//We dont want any memory leaks!
	destroyDictionary(dict);
	destroyPuzzle(puzzle);

	return 0;
}
