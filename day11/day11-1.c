// seating arrangement
/*
 * L means empty
 * . means floor space
 * # means full
 * changes are not made immediately, they are made in rounds
 */

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000
#define INPUTLENGTH 91
#define WIDTH 92

void zeroArray(int arr[], int len)
{
	for (int i=0; i<len; arr[i++] = 0);
	return;
}

int numberAdjacentSeatsOccupied(char arr[INPUTLENGTH][WIDTH], int column, int row)
{
	// determine max and min ranges for check area
	int ymax, ymin, xmax, xmin;
	if (column == 0) xmin = 0;
	else xmin = column - 1;
	if (column == WIDTH-1) xmax = WIDTH-1;
	else xmax = column + 1;
	if (row == 0) ymin = 0;
	else ymin = row - 1;
	if (row == INPUTLENGTH-1) ymax = INPUTLENGTH-1;
	else ymax = row + 1;

	int count = 0;
	for (int y=ymin; y<=ymax; y++) for (int x=xmin; x<=xmax; x++)
	{
		if (x == column && y == row) continue; // skip checking the target spot
		if (arr[y][x] == '#') count++;
	}
	return count;
}

int main(void)
{
	// declare standard file pointer to input path
    FILE *fp;	// file pointer
    char str[MAXCHAR];	// store the current line of input file
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input11.txt";	// intput filepath
    fp = fopen(filename, "r");	// point file pointer to filepath
    if (fp == NULL){ 	// error message if file not found
        printf("Could not open file %s\n",filename);
        return 1;
    }    

	char seats[INPUTLENGTH][WIDTH];	// contains current status of seats

	// declare flag arrays and zero them
	int seatsToBeFilled[INPUTLENGTH][WIDTH];
	int seatsToBeEmptied[INPUTLENGTH][WIDTH];
	for (int i=0; i<INPUTLENGTH; i++){
		zeroArray(seatsToBeFilled[i], WIDTH);
		zeroArray(seatsToBeEmptied[i], WIDTH);
	}

    // read file to array
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL && i<INPUTLENGTH; i++)	// read input file into integer array
	{
		// store each line of input in array
		sscanf(str, "%s", seats[i]);
	}
	printf("done.\n");

	// main code begins here

	int changesMadeFlag = 1;	// 
	while (changesMadeFlag)
	{
		// loop through all seats
		for (int y=0; y<INPUTLENGTH; y++) for (int x=0; x<WIDTH; x++)
		{
			char currentSeat = seats[y][x];
			if (currentSeat == '.') continue;	// skip checking floor space
			else if (currentSeat == '#')		// logic if seat is full
			{
				if (numberAdjacentSeatsOccupied(seats, x, y) >= 4) seatsToBeEmptied[y][x] = 1;
			}
			else if (currentSeat == 'L')
			{
				if (numberAdjacentSeatsOccupied(seats, x, y) == 0) seatsToBeFilled[y][x] = 1;
			}
		}

		// apply any changes found
		changesMadeFlag = 0;
		for (int i=0; i<INPUTLENGTH; i++){
			for (int j=0; j<WIDTH; j++)
			{
				if (seatsToBeEmptied[i][j]) {
					seats[i][j] = 'L';
					seatsToBeEmptied[i][j] = 0;
					changesMadeFlag = 1;
				}
				if (seatsToBeFilled[i][j]) {
					seats[i][j] = '#';
					seatsToBeFilled[i][j] = 0;
					changesMadeFlag = 1;
				}
			}
		}

		/*// for debug purposes, output the matrix every time:
		printf("\n");
		for (int i=0; i<INPUTLENGTH; i++) {
			for (int j=0; j<WIDTH; j++){
				printf("%c", seats[i][j]);
			}
			printf("\n");
		}*/

	}

	// count the number of occupied seats and print to console
	int count = 0;
	for (int i=0; i<INPUTLENGTH; i++) for (int j=0; j<WIDTH; j++) if (seats[i][j] == '#') count++;
	printf("At the end of the duffle kerfuffle, there are %d seats occupied.\n", count);

    return 0;
}