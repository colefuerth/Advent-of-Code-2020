// plane bullshit 
// answer was 756261495958122

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 1000
#define INPUTLENGTH 100
#define FILEPATH "X:\\AdventOfCode\\input13.txt"
//#define FILEPATH "X:\\AdventOfCode\\input13sample.txt"
#define MIN_START 500000000000000
//#define MIN_START 1000

void zeroArray(long arr[], long len)
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

    long scalars[INPUTLENGTH];       // contains the magnitudes of each step
    char commands[INPUTLENGTH];     // contains the character commands for each step

    // read file to array
	printf("Inputting file information...");
    /*for (int i=0; fgets(str, MAXCHAR, fp) != NULL && i<INPUTLENGTH; i++)	// read input file into integer array
	{
		// store each line of input in array
		sscanf(str, "%c%d", &commands[i], &scalars[i]);
	}*/
    long minTime;
    fgets(str, MAXCHAR, fp);
    sscanf(str, " %ld", &minTime);
    long busTimes[INPUTLENGTH];
    long busIndex[INPUTLENGTH];
    zeroArray(busTimes, INPUTLENGTH);
    zeroArray(busIndex, INPUTLENGTH);
    fgets(str, MAXCHAR, fp);
    char ehe[5];
    int numberBusses = 0;
    int index = 0;
    for (int i=0; str[i] != '\0'; i++)
    {
        static int n=0;
        if (str[i] == ',') { 
            n = 0; 
            busIndex[numberBusses] = index++;
            sscanf(ehe, " %d", &busTimes[numberBusses++]); 
            for (int j=0; j<5; j++) ehe[j] = '\0';
        }
        else if (str[i] == 'x') { i++; index++; }// skip to character after next ','
        else ehe[n++] = str[i];
    }
    busIndex[numberBusses] = index++;
    sscanf(ehe, " %ld", &busTimes[numberBusses++]);
	printf("done.\n");

    
    // START OF MAIN PROGRAM P1
    /*int departureTime = minTime;
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
    printf("Departure time is %d on bus %d\nWait time is %d\nanswer p1 is %d\n", departureTime, theChosenBus, waitTime, theChosenBus * waitTime);*/

    // MAIN CODE PART 2

    long long departureTime;
    int timeFound = 0;

    // find the largest bus time and then its index to find the starting point, and the incrementation for brute force
    int largestBusNumber;   // the index in the busTimes array holding the largest bus time
    for (int i=0; i<numberBusses; i++)
    {
        static int largest = 0;
        if (busTimes[i] > largest) { largest = busTimes[i]; largestBusNumber = i; }
    }
    printf("Largest bus is %d\n", busTimes[largestBusNumber]);
    for (departureTime = MIN_START; departureTime % busTimes[largestBusNumber]; departureTime++); // find a starting point that divides evenly by largest number
    printf("First spot divisible by largest bus time is %lld\n", departureTime);
    printf("Initial starting time is %lld - %ld = %lld\n", departureTime, busIndex[largestBusNumber], departureTime - busIndex[largestBusNumber]);
    departureTime -= busIndex[largestBusNumber];    // starting point needs to be compatible with the largest boi
    
    
    printf("bus times/indexes are:\n");
    for (int i=0; i<numberBusses; i++) printf("%ld\t%ld\n", busTimes[i], busIndex[i]);
    printf("Starting main process...");

    for (long i=0; !timeFound; i++)
    {
        timeFound = 1;
        for (int i=0; i<numberBusses && timeFound; i++)
        {
            timeFound = timeFound && ((departureTime + (long long) busIndex[i]) % (long long) busTimes[i] == 0);
        }
        if (!timeFound) departureTime += busTimes[largestBusNumber];
        if (i>100000000)
        {
            printf("reached %lld\n", departureTime);
            i=0;
        }
    }
    

    printf("Done.\nTarget dept time is %lld\n", departureTime);


    return 0;
}