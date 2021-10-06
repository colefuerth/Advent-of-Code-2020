// AOC 2020 day 10 
// power cords and the milk muff

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000
#define INPUTLENGTH 94

void zeroArray(int arr[], int len)
{
	for (int i=0; i<len; arr[i++] = 0);
	return;
}

int searchArray(int arr[], int len, int num)
{
	for (int i=0; i<len; i++) if (arr[i] == num) return 1;
	return 0;
}

int largestInArray(int arr[], int len)
{
	int largest = 0;
	for (int i=0; i<len; i++) if (arr[i] > largest) largest = arr[i];
	return largest;
}

int main(void)
{
	// declare standard file pointer to input path
    FILE *fp;	// file pointer
    char str[MAXCHAR];	// store the current line of input file
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input10.txt";	// intput filepath
    fp = fopen(filename, "r");	// point file pointer to filepath
    if (fp == NULL){ 	// error message if file not found
        printf("Could not open file %s\n",filename);
        return 1;
    }    


    int joltRatings[INPUTLENGTH];	// integer array to store input
	zeroArray(joltRatings, INPUTLENGTH);		// reset array to 0's
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; sscanf(str, " %d", &joltRatings[i++]));	// read input file into integer array
	printf("Done.\n");

	int usedAdapters[INPUTLENGTH];	// store the jolt ratings of the used adapters
	zeroArray(usedAdapters, INPUTLENGTH);

	// jumpByThree = 1 because the final jump to the laptop charger is a jump of 3 that is not accounted for in the input
	int jumpByOne = 0, jumpByThree = 1, numAdaptersUsed = 0, currentJolts = 0;
	int moveToNextAdapterFlag = 0;
	int largestJoltRating = largestInArray(joltRatings, INPUTLENGTH);
	int numberOfTries = 0;

	// main code here
	printf("Starting main process..\n");
	while (currentJolts < largestJoltRating && numberOfTries++ < INPUTLENGTH)
	{
		printf("Current joltage rating: %d\n", currentJolts);
		for (int jd=1; jd<=3; jd++)	// look for increases of 1, 2, then 3 jolts available
		{
			printf("\tchecking for jd of +%d\n", jd);
			for (int i=0; i<INPUTLENGTH; i++) {
				//if (searchArray(usedAdapters, numAdaptersUsed, joltRatings[i])) continue;
				if (joltRatings[i] == currentJolts + jd)	// find the smallest available jump
				{
					if (jd == 1) jumpByOne++;
					if (jd == 3) jumpByThree++;
					printf("%d: %d\n", numAdaptersUsed+1, joltRatings[i]);
					usedAdapters[numAdaptersUsed++] = joltRatings[i];
					currentJolts = joltRatings[i];
					moveToNextAdapterFlag = 1;
					break;
				}
			}
			if (moveToNextAdapterFlag)
			{
				moveToNextAdapterFlag = 0;
				break;
			}
		}
	}

	printf("Largest joltage rating is %d\n", largestJoltRating);
	printf("number of adapters used was %d\n", numAdaptersUsed);
	printf("number of jumps by 1 is %d\n", jumpByOne);
	printf("number of jumps by 3 is %d\n", jumpByThree);
	printf("Part 1 answer is %d\n", jumpByOne * jumpByThree);
   
    return 0;
}