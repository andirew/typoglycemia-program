/**************************************************************\
*                                                              *
* Name: Assign3.2.c                                            *
* Purpose:                                                     *
* This program is a typoglycemia program that will shift word  *
* to the left by a factor of 1, but still keeping the first    *
* and last characters in place. It will take inputs from a file*
* and output them to another file.                             *
****************************************************************
* MODIFICATION HISTORY:                                        *
* 7/3/2017: Andrew Barsoom - created                           *
\**************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_LINE 4098


int Check(FILE *fp, FILE* f);
void shuffle_word(char *arr, int n, int x);
void openFiles();
void display(int d);
/********************************************************************\
*                                                                    *
* Name       : main()                                                *
* Parameters :                                                       *
* Returns    : int                                                   *
* Description:                                                       *
* Function controller and calls retrieve function.                   *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
int main(int argc, const char * argv[])
{
	openFiles(); //call open files, to begin creating all the exterior files.
	return 0;
}
/********************************************************************\
*                                                                    *
* Name       : openFiles()                                           *
* Parameters :                                                       *
* Returns    : void                                                  *
* Description:                                                       *
* Function controller and calls retrieve function.                   *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
void openFiles() {
	FILE *fp; //create a File instance called fp
	FILE *f;// Create a file instance called FP

	//Open a file called dict.txt
	if ((fp = fopen("dict.txt", "r")) == NULL)
	{
		printf("Error! opening file");
		// Program exits if file pointer returns NULL.

	}
	//open a file called scramble.txt
	if ((f = fopen("scramble.txt", "wb+")) == NULL)
	{
		printf("Error! opening file\n");
		// Program exits if file pointer returns NULL.

	}
	Check(fp, f);//Call the main validation function.
}
int Check(FILE *fp, FILE* f) {
	 

	char c[MAX_LINE]; // Introduce a char array to copy to.
	char word[128]; // 128 chars to copy the input to.
	int word_len = 0; //Variable to hold word length
	char buf[MAX_LINE]; //Another input variable.
	int numberofOutputs = 0; //Variable for Number of outputs written to file.
	int i = 0; //Variable for a loop 
	int numCurrPrints = 0;// Variable for number of current Prints
	int stop = 0; //Variable to stop a loop
	int numberread = 0; //Hold number of read words from a file
	int numberread2 = 0; //hold number of read words from a file
	int filelength = 0; // hold the number of total words in a file.
	//Display legend:
	// 1 = Error Opening File
	// 2 = Error: Unexpected End of file;
	// 3 = Error! First line is not an integer! 

	//Open the file to read to determine how many words are in the file.
	while (fgets(buf, sizeof buf, fp) != NULL) {

		if (isdigit(buf[0]) && numberread2 == 0) { 
			numberread2 = buf[0] - '0';
		}
		else {
			filelength++;
		}

	}
	//----------------------------------------------------------------------------------------------
	//REOPEN THE FILE after we read through it once. 

	if ((fp = fopen("dict.txt", "r")) == NULL)
	{
		display(1);
		// Program exits if file pointer returns NULL.
		return 0;
	}
	//----------------------------------------------------
	if (filelength != numberread2) {// If the number declared ontop of the file is not the same as the total length. display error message
		display(2);
		return 0;
	}

	while (fgets(buf, sizeof buf, fp) != NULL  && stop == 0) //Main section that will deal with shuffling the words one by one.
	{
		size_t len = strlen(buf); // get size of the current word
		strncpy(c, buf, MAX_LINE); // Copy it to another char array.
		size_t ln = strlen(c) - 1; // Get the length of c


		if (*c && c[ln] == '\n') //remove trailing \n from fget
			c[ln] = '\0';

		for (i = 0; i < len; i++) {//Loop through every letter in a word to validate it.

			if (isdigit(c[0]) && numberread == 0) { // Check to make sure that the first entry is always a number and that its only read once.
				numberofOutputs = c[0] - '0';
				numberread = 1;
				numCurrPrints = 0;
			}
			else if (numberofOutputs == 0 && stop == 0) { // If the first entry is not a digit, display an error and exit.
				display(3);
				return 0;
			}
			else { //Otherwise, populate another char array with the valid input character.
				word[word_len] = c[i];
				word_len++;
			}
		}

		if (word_len > 3 && numberread != 1) { // Only shuffle a word if its more than 3 letters. 
			numCurrPrints++;
			if (numCurrPrints == numberofOutputs) {	
				shuffle_word(word, word_len, 2);//Call main shuffle function
			}
			else {
				shuffle_word(word, word_len, 3); //call main shuffle function
			}
		}
		if (word_len > 0 && numberread != 1) {
			//printf("%.*s \n", word_len, (char *)word);// Print to console (Debugging)
			fprintf(f, "%.*s\n", word_len, (char *)word); // Print to txt
		}
		numberread = 2;
		if (c == NULL)
			return 0; // Break out here, need to print last word

		word_len = 0;


		if (numCurrPrints == numberofOutputs) { // If we're done printing, exit out.
			stop = 1;
		}

	}


	fclose(fp);//close the files.
	fclose(f);
}
/********************************************************************\
*                                                                    *
* Name       : shuffle_word()                                        *
* Parameters : char * arr, int n, int x                              *
* Returns    : void                                                  *
* Description:                                                       *
* Function that controlles the algorithim for shifting characters    *
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
void shuffle_word(char *arr, int n, int x)
{
	// arr = Char array
	// n = word length
	// x = how far from the end do you shuffle to.
	int i, temp;//variables for loops/temp char holding.

	temp = arr[1];// Hold the 2nd position character in temp

	for (i = 1; i < n - x; i++) {//This will shift everything once to the left
		arr[i] = arr[i + 1];
	}

	arr[i] = temp;//Set the 2nd last position to temp.
}

/********************************************************************\
*                                                                    *
* Name       : display()                                             *
* Parameters : int d                                                 *
* Returns    : void                                                  *
* Description:                                                       *
* Function that will display error mesages depending on the number   *
* it gets.                                                           * 
**********************************************************************
* MODIFICATION HISTORY                                               *
*                                                                    *
* 7/3/2017 - Andrew Barsoom - Created                                *
*                                                                    *
\********************************************************************/
void display(int d) {
	if (d == 1) {
		printf("Error! opening file");
	}
	else if (d == 2) {
		printf("Error: Unexpected end of file \n");
	}
	else if (d == 3) {
		printf("Error! First line is not an integer! \n");
	}

}
