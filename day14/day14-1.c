// ship navigation

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXCHAR 1000
#define FILEPATH "X:\\AdventOfCode\\input14.txt"
//#define FILEPATH "X:\\AdventOfCode\\input14sample.txt"

// 0=maskptr, 1=memptr, 2=value
#define MSKPTR  0
#define MEMPTR  1
#define VAL     2

void zeroLongArray(long long arr[], long len)
{
	for (long i=0; i<len; arr[i++] = 0);
	return;
}

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

void longToArr(long long in, int arr[36])
{
    zeroArray(arr, 36);
    for (int i=0; in > 0; i++)
    {
        arr[i] = in % 2;
        in /= 2;
    }
    return;
}

long long arrToLong(int arr[36])
{
    long long out = 0;
    for (int i=0; i<36; i++) if (arr[i]) out += pow(2, i);
    return out;
}

long long applyMask(long input, char mask[36])
{
    int arr[36];
    longToArr(input, arr);

    // print input array and mask
    //printf("in dec:\t%ld\nin:\t", input);
    //for (int i=0; i<36; i++) printf("%d", arr[35-i]);
    //printf("\nMask:\t%s\n", mask);
    for (int i=0; i<36; i++)
    {
        if (mask[i] == 'X');
        else if (mask[i] == '1') arr[35-i] = 1;
        else if (mask[i] == '0') arr[35-i] = 0;
        else printf("CRITICAL ERROR\n");
    }
    // print output array
    printf("out:\t");
    for (int i=0; i<36; i++) printf("%d", arr[35-i]);
    printf("\n");
    return arrToLong(arr);
}

long max(long a, long b)
{
    if (a > b) return a;
    else return b;
}

long long sumLongArray(long long arr[], long length)
{
    long long sum = 0;
    for (long i=0; i<length; i++) sum += arr[i];
    return sum;
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


    int numberCommands = 0;
    char masks[MAXCHAR][36];
    long programRegistry[MAXCHAR][3];   // 0=maskptr, 1=memptr, 2=value

    // read file to array
	printf("Inputting file information...");
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; i++)	// read input file into integer array
	{
        static int numberMasks = 0;
        if (str[1] == 'a') sscanf(str+7, "%s", &masks[numberMasks++]);  // if mask, store in array
        else {  // grab memory things
            programRegistry[numberCommands][MSKPTR] = numberMasks-1;
            sscanf(str+4, "%ld", &programRegistry[numberCommands][MEMPTR]);
            for (int i=10; !sscanf(str+i, "%ld", &programRegistry[numberCommands][VAL]); i++);
            numberCommands++;
        }
	}
	printf("done.\n");  // END OF INPUT FILE

    // create memory to required length
    // first find the largest memory spot in the whole ass thing
    long memSize = 0;
    for (int i=0; i<numberCommands; i++) memSize = max(programRegistry[i][1], memSize);
    memSize++; // increment from largest index to actual length
    // create and clear the memory
    long long mem[memSize];
    zeroLongArray(mem, memSize);

    for (int i=0; i<numberCommands; i++)
    {
        printf("current cmd is %d\n", i);
        printf("current memptr is %ld\n", programRegistry[i][MEMPTR]);
        printf("current val is %ld\n", programRegistry[i][VAL]);
        long long temp = applyMask(programRegistry[i][VAL], masks[programRegistry[i][MSKPTR]]);
        printf("out is %lld dec\n", temp);
        mem[programRegistry[i][MEMPTR]] = temp;
    }

    printf("Sum of all memory elements is %lld\n", sumLongArray(mem, memSize));
    return 0;
}