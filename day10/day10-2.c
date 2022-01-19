// AOC 2020 day 10 part 2
// power cords and the milk muff

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAXCHAR 1000
//#define INPUTLENGTH 94
#define INPUTLENGTH 31
//#define FILEPATH "X:\\AdventOfCode\\input10.txt"
#define FILEPATH "X:\\AdventOfCode\\input10sample.txt"

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

void bubbleSort(int arr[], int len)	// sort an integer array from largest to smallest
{
	int anyChangesMade = 1;
	while(anyChangesMade)
	{
		anyChangesMade = 0;
		for (int i=0; i<len-1; i++) 
		{
			if (arr[i] > arr[i+1])
			{
				int n = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = n;
				anyChangesMade = 1;
			}
		}
	}
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


    int joltRatings[INPUTLENGTH];	// integer array to store input
	zeroArray(joltRatings, INPUTLENGTH);		// reset array to 0's
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; sscanf(str, " %d", &joltRatings[i++]));	// read input file into integer array
	printf("Done.\n");

	// main code here
	int two=0, three=0, four=0;
    //int five=0, six=0;
    int n = 0;
    bubbleSort(joltRatings, INPUTLENGTH);
    for (int i=0; i<INPUTLENGTH; i++) printf("%d\n", joltRatings[i]);
    for (int i=1; i<INPUTLENGTH; i++)
    {
        if (joltRatings[i] - joltRatings[i-1] == 1) n++;
        else 
        {
            // && joltRatings[i] == n && joltRatings[i-n+1] == n
            if (n == 2) two++;
            if (n == 3) three++;
            if (n == 4) four++;
            //if (n == 5) five++;
            //if (n == 6) six++;
            printf("n=%d\n", n);
            n=0;
        }
    }

    long product = pow(2, two) * pow(4, three) * pow(7, four);// * pow(13, five) * pow(24, six);
    printf("%ld\n", product);
   
    return 0;
}