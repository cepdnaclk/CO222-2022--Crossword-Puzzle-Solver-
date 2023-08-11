/* 
    CO222 - 2022
    Crosswords Puzzle Solver
    Group 24
    E/19/060 - DANUJAN S.
    E/19/205 - KUMARA I.P.S.N.U
*/

//Required Header Files
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

//Character Arrays
char mystr2Darray[20][20];      // To store the words
char my2Darray[100][100];       // To store the grid pattern

//Global Variables
int row_str;                    // Counter for the number of words in the str_array
int count;                      // Length of the grid

// Try to place the word at the specified position in the puzzle.
// Return true if the word was successfully placed, false otherwise.
bool place_word(char word[],int row, int col, int dir){  
    /* 
     * word[] here is a row in the 2d array 
     * dir indicates whether it is horizontal or vertical
     * row means horizontal position of the #
     * col means vertical position of the #
     */

    int r,c;     // Replacements for row and column in later parts

    //  Check if the word fits within the puzzle grid
    //Horizontal
    if(dir == 0){ 
        if(col + (strlen(word)-1) > count){     // -1 is used to remove the count for the '\0' character in the end of every word
            return false;
        }
    // Vertical
    }else{ 
        if(row + (strlen(word)-1)> count){
            return false;
        }
    }

    //check if the word overlaps with any existing letters in the puzzle
    for(int i = 0; i < strlen(word)-1; i++){
        //Horizontal
        if(dir == 0){ 
            r = row;
            c = col + i;
        // Vertical
        }else{  
            r = row + i;
            c = col;
        }
        if(my2Darray[r][c] != '#' && my2Darray[r][c] != word[i]){
            return false;
        }
    }

    // Place the word in the puzzle
    for(int i = 0; i < strlen(word)-1; i++){
        if(dir == 0){           //Horizontal placement
            r = row;
            c = col + i;
        }else{                  //Vertical placement
            r = row + i;
            c = col;
        }
        my2Darray[r][c] = word[i];
    }

    return true;
}

// Recursive function to solve the puzzle.
// words: remaining words to be placed in the puzzle
// num_words: number of words
// Returns true if the puzzle was successfully filled, false otherwise.
bool solve_puzzle(char words[][row_str],int num_words){

    //Base case: no more words to place
    //If there are no words to fill then the function will return true and grid will be printed
    if(num_words == 0){
        return true;
    }

    //Try to place the current word at all positions in the puzzle
    for( int i = 0; i < count; i++){
        for( int j = 0; j < count; j++){
            if(my2Darray[i][j] == '#'){

                //Try to place the word horizontally
                if(place_word(words[0],i,j,0)){
                    if(solve_puzzle(words + 1,num_words - 1)){
                        return true;
                    }
                    //Undo the placement of the word
                    for(int k = 0; k < strlen(words[0]); k++){
                        i = i;
                        j = j + k;
                        my2Darray[i][j] = '#';
                    }
                }
                

                //Try to place the word Horizontally
                if(place_word(words[0],i,j,1)){
                    if(solve_puzzle(words+1,num_words-1)){
                        return true;
                    }
                    // Undo the placement of the word
                    for(int l = 0; l < strlen(words[0]); l++){
                        i = i +l;
                        j = j;
                        my2Darray[i][j] = '#';
                    }
                }

            }
        }
    }

    // Unable to place the current word
    return false;
}


int main(){
    // ! 1. To get the grid inputs
	char myarray[100];  //To get the first line only and used to determine the length of the array
	char array[100];
	
	//Getting first line of the grid pattern
	fgets(myarray,sizeof(myarray),stdin);
	
	//Calculating the number of elements in the first line of grid pattern
	for(int j = 0; myarray[j] != '\0'; j++){
		count++;
    }
    count = count - 1; //Removing the last empty element '\0'
    
    //assigning the First row to 2d  grid character array
	for(int i = 0; i < count; i++){
		my2Darray[0][i] = myarray[i];
	}
	
	//Getting the inputs to the other rows in the 2D array
	//Starting from second row because we have assigned the initial inputs to row 1
	for(int row = 1; row < count; row++){
		fgets(array,sizeof(array),stdin);
		int count_col = 0;
		for(int p = 0; array[p] != '\0'; p++){
			count_col++;
		}
		count_col = count_col - 1;
		if(count_col == count){
			for(int col = 0; col < count; col++){
				if(array[col] == 35 || array[col] == 42 ||(array[col]>64 && array[col]<91)||(array[col]>96 &&array[col]<123)){
					my2Darray[row][col] = array[col];
				}else{
					printf("invalid input");
					return 0;
				} 	
			}
		}else{
			printf("invalid input");    //If you enter more characters than the previous line it will return 'Invalid input'
			return 0;
		}	
	}
	char c = getchar();                //To save the newline character which are inserted after the entry of the grid inputs

	if( c == '\n'){

	}else{
		printf("invalid input");
	}


    // ! 2. To get the string inputs

    char mystr2Darray[100][100]; // To save the character inputs
    int flag = 0;                // used to indicate when two newline characters are inputed - Indicate the termination of string inputs


    while(fgets(mystr2Darray[row_str],sizeof(mystr2Darray),stdin)){
        if(strcmp(mystr2Darray[row_str], "\n") == 0){  //checks whether this line is new line or not
            flag++;                                    //increase the flag value by one
        }else{
            flag = 0;                                  //Reset the flag if the line is not a newline character
        }
        if(flag == 1){
            break;
        }
        row_str++;                                     // Move to the next row
    }


    if(solve_puzzle(mystr2Darray,row_str)){ // Puzzle with solutions will be printed if solve_puzzle returns true
        // To Print the solution
        for(int i = 0; i < count; i++){
            for(int j = 0; j < count; j++){
                printf("%c",my2Darray[i][j]);
            }
            putchar('\n');
        }
    }else{
        printf("IMPOSSIBLE\n");
    }
	return 0;
}


