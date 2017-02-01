#include <stdio.h>
#include <stdlib.h>


#define NUM_BUFF_SIZE 5
#define BOARD_COLUMNS 4
#define BOARD_ROWS 4
#define BUFFER_SIZE 60
#define WIN_LENGTH 3
#define WILDCARD 'T'
#define MAX(a,b) (a > b) ? a : b
#define MIN(a,b) (a < b) ? a : b


int evaluateBoard(char **string){
	int i, j;
	char unfinished = 0;
	char dot = '.';
	for(i=0; i<BOARD_ROWS; i++){
		for(j = 0; j<BOARD_COLUMNS; j++){
				if ((*(*(string+i)+j)) == dot){
					unfinished = 1;
				}
		}
	}
	if(unfinished){
		printf("Game has not completec");
	}else{
		printf("Draw");
	}
	
}


int rightSearch(char **board, char *token, int row, int column){
	if( (*(*(board+row)+column)) == (*token) || (*(*(board+row)+column)) == WILDCARD){
		if(column == BOARD_COLUMNS - 1)
			return 0;
		else
			return rightSearch(board, token, row, column + 1) + 1;
	}
	else
		return -1;
}

int downSearch(char ** board, char *token, int row, int column){
	if( (*(*(board+row)+column)) == (*token) || (*(*(board+row)+column)) == WILDCARD){
		if(row == BOARD_ROWS - 1){
			return 0;
		}
		else{
			return downSearch(board, token, row + 1, column) + 1;
		}
			
	}
	else
		return -1;
}


int rdiagSearch(char **board, char *token, int row, int column){
	if( (*(*(board + row)+column)) == (*token) || (*(*(board+row)+column)) == WILDCARD){
		if(row == BOARD_ROWS-1 || column == BOARD_COLUMNS-1)
			return 0;
		else
			return rdiagSearch(board, token, row + 1, column + 1) + 1;
	}
	else
		return -1;
}

int ldiagSearch(char **board, char *token, int row, int column){
	if( (*(*(board + row)+column)) == (*token) || (*(*(board+row)+column)) == WILDCARD){
		if(row == BOARD_ROWS-1 || column == 0)
			return 0;
		else
			return ldiagSearch(board, token, row + 1, column - 1) + 1;
	}
	else
		return -1;
}




int checkBoard(char **board, char *token, int row, int column){
	int left = 0,right = 0,up = 0, down = 0,rdiag = 0,ldiag = 0;
	
    right = rightSearch(board, token, row, column) + 1;
	down = downSearch(board, token, row, column) + 1;
	rdiag = rdiagSearch(board, token, row, column) + 1;
	ldiag = ldiagSearch(board, token, row, column) + 1;
	
	
	//printf("l:%d r:%d u:%d d:%d rd: %d ld: %d \n", left, right, up, down, rdiag, ldiag);
	int a = MAX(left, right);
	int b = MAX(up,down);
	int c = MAX(rdiag, ldiag);
	int d = MAX(a,b);
	int e = MAX(d,c);
	return e;
}





int main(){

	FILE *inputFile;
	inputFile = fopen("Input.txt", "r");
	if(!inputFile){
		printf("error opening file\n");
		return -1;
	}
	size_t buff_size = BUFFER_SIZE;
	
	char *sampleSize;
	sampleSize = (char *) malloc(BUFFER_SIZE *sizeof(char));
	getline(&sampleSize, &buff_size, inputFile);
	
	
	int repetitions, cases = 0;
	sscanf(sampleSize, "%d", &repetitions);
	printf("repetitions: %d", repetitions);
	
	for (;repetitions > 0; repetitions--){
		
		char **inputs;																			// Double array for inputs
		inputs = (char **) calloc (BOARD_ROWS, sizeof(char *));									// Allocate memory blocks
			
		int i,j;
		for(i = 0; i < BOARD_ROWS ; i++){
			*(inputs+i) = (char *) calloc(BUFFER_SIZE, sizeof(char));	
			getline((inputs+i), &buff_size, inputFile);
		}
		

		printf("\n");
		for (i = 0; i < BOARD_ROWS; i++){
			printf("%s", *(inputs + i));
		}printf("\n");

		
		printf("Case #%d: ", ++cases);
		char x = 'O';
		int test;
		for( i = 0; i < BOARD_ROWS; i++){
			for(j = 0; j < BOARD_COLUMNS; j++){
				test = checkBoard(inputs, &x, i, j);
				//printf("I is: %d\n", i);
				if(test > 2){
					printf("Winner is %c", x);
					break;
				}
			}
			if(test > 2){
					break;
			}
		}
		if(test < 3){
			x = 'X';
			for( i = 0; i < BOARD_ROWS; i++){
				for(j = 0; j < BOARD_COLUMNS; j++){
						test = checkBoard(inputs, &x, i, j);
						//printf("I is: %d\n", i);
						if(test > 2){
							printf("Winner is %c", x);
							break;
						}
				}
				if(test > 2){
					break;
				}
			}
		}
		
		if(test < 3){
			evaluateBoard(inputs);
		}
		for(i = 0; i < BOARD_COLUMNS; i++){
			free(*(inputs+i));
		}
		free(inputs);
		getline(&sampleSize, &buff_size, inputFile);
	}
	
	return 0;
}
