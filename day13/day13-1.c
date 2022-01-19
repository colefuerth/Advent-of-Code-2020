// ship navigation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 1000
#define FILEPATH "X:\\AdventOfCode\\input13.txt"
#define INPUTLENGTH 100
//#define FILEPATH "X:\\AdventOfCode\\input13sample.txt"

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
    /*for (int i=0; fgets(str, MAXCHAR, fp) != NULL && i<INPUTLENGTH; i++)	// read input file into integer array
	{
		// store each line of input in array
		sscanf(str, "%c%d", &commands[i], &scalars[i]);
	}*/
    int minTime;
    fgets(str, MAXCHAR, fp);
    sscanf(str, " %d", &minTime);
    int busTimes[INPUTLENGTH];
    zeroArray(busTimes, INPUTLENGTH);
    fgets(str, MAXCHAR, fp);
    char ehe[5];
    int numberBusses = 0;
    for (int i=0; str[i] != '\0'; i++)
    {
        static int n=0;
        if (str[i] == ',') { 
            n = 0; 
            sscanf(ehe, " %d", &busTimes[numberBusses++]); 
            for (int j=0; j<5; j++) ehe[j] = '\0';
        }
        else if (str[i] == 'x') i++; // skip to character after next ','
        else ehe[n++] = str[i];
    }
    sscanf(ehe, " %d", &busTimes[numberBusses++]);
	printf("done.\n");

    
    // START OF MAIN PROGRAM
    int departureTime = minTime;
    int theChosenBus = 0;
    while (!theChosenBus)
    {
        printf("trying departure time %d...\n", departureTime);
        for (int i=0; i<numberBusses; i++) {
            if (departureTime % busTimes[i] == 0) theChosenBus = busTimes[i];
        }
        if (!theChosenBus) departureTime++;
    }
    int waitTime = departureTime - minTime;
    printf("min time is %d\nbus times are:\n", minTime);
    for (int i=0; i<numberBusses; i++) printf("%d\n", busTimes[i]);
    printf("Departure time is %d on bus %d\nWait time is %d\nanswer is %d\n", departureTime, theChosenBus, waitTime, theChosenBus * waitTime);
//  208 is too high
    return 0;
}