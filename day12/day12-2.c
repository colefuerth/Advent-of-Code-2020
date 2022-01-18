// ship navigation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 1000
#define FILEPATH "X:\\AdventOfCode\\input12.txt"
//#define FILEPATH "X:\\AdventOfCode\\input12sample.txt"
#define INPUTLENGTH 774
//#define 	INPUTLENGTH	5

void zeroArray(int arr[], int len)
{
	for (int i=0; i<len; arr[i++] = 0);
	return;
}

void swap(long *a, long *b)
{
    long temp = *a;
    *a = *b;
    *b = temp;
    return;
}

int main(void)
{
	// declare standard file pointer to input path
    FILE *fp;	// file pointer
    char str[MAXCHAR];	// store the current line of input file
    char* filename = FILEPATH;	// intput filepath
    fp = fopen(filename, "r");	// point file pointer to filepath
    if (fp == NULL){ 	// error message if file not found
        printf("Could not open file %s\n",filename);
        return 1;
    }    

    long scalars[INPUTLENGTH];       // contains the magnitudes of each step
    char commands[INPUTLENGTH];     // contains the character commands for each step

    // read file to array
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL && i<INPUTLENGTH; i++)	// read input file into integer array
	{
		// store each line of input in array
		sscanf(str, "%c%d", &commands[i], &scalars[i]);
	}
	printf("done.\n");


	// main code begins here
    long east = 0, north = 0;  // start at 0,0
    long eastWay = 10, northWay = 1;
    long temp;

    for (int i=0; i<INPUTLENGTH; i++)   // loop through all the inputs once
    {
        switch(commands[i])
        {
            case 'N':
                northWay += scalars[i];
                break;
            case 'S':
                northWay -= scalars[i];
                break;
            case 'E':
                eastWay += scalars[i];
                break;
            case 'W':
                eastWay -= scalars[i];
                break;
            case 'F':   
                    east += eastWay * scalars[i];
                    north += northWay * scalars[i];
                break;
            case 'L':
                temp = scalars[i] / 90;
                for (int n=0; n<temp; n++) {
                    swap(&eastWay, &northWay);
                    eastWay *= -1;
                }
                break;
            case 'R':
                temp = scalars[i] / 90;
                for (int n=0; n<temp; n++) {
                    eastWay *= -1;
                    swap(&eastWay, &northWay);
                }
                break;
        }
    }

    printf("The final coords are %ld, %ld\n", east, north);
    printf("The manhattan value is %ld + %ld = %d\n", abs(east), abs(north), abs(east) + abs(north));


    return 0;
}