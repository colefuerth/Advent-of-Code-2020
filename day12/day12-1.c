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

    double scalars[INPUTLENGTH];       // contains the magnitudes of each step
    char commands[INPUTLENGTH];     // contains the character commands for each step

    // read file to array
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL && i<INPUTLENGTH; i++)	// read input file into integer array
	{
		// store each line of input in array
		sscanf(str, "%c%lf", &commands[i], &scalars[i]);
	}
	printf("done.\n");


	// main code begins here
    double degrees = 0.0;           //start pointing at [EAST]
    double east = 0.0, north = 0.0;  // start at 0,0

    for (int i=0; i<INPUTLENGTH; i++)   // loop through all the inputs once
    {
        switch(commands[i])
        {
            case 'N':
                north += scalars[i];
                break;
            case 'S':
                north -= scalars[i];
                break;
            case 'E':
                east += scalars[i];
                break;
            case 'W':
                east -= scalars[i];
                break;
            case 'F':
                if (degrees == 0.0) east += scalars[i];
                else if (degrees == 90.0) north += scalars[i];
                else if (degrees == 180.0) east -= scalars[i];
                else if (degrees == 270.0) north -= scalars[i];
                else { printf("CRITICAL ERROR IN  DEGREES\n"); return 0; }
                break;
            case 'L':
                degrees += (scalars[i]);
                break;
            case 'R':
                degrees -= (scalars[i]);
                break;
        }
        if (degrees >= 360.0) degrees -= 360.0;
        else if (degrees < 0.0) degrees += 360.0;
        printf("%c%d = [%.2lf] [%.2lf] at %.2lfdeg\n", commands[i], (int) scalars[i], east, north, degrees);
    }

    printf("The final coords are %.2lf, %.2lf\n", east, north);
    printf("The manhattan value is %d + %d = %d\n", abs((int)east), abs((int)north), abs((int)east) + abs((int)north));


    return 0;
}