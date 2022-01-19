// day 8
// assembly loop finder

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000

int sumInLast25(long list[], int pos)	// find
{
	for (int i=pos-25; i<pos-1; i++) for (int j=i+1; j<pos; j++) if (list[i] + list[j] == list[pos]) return 1;
	return 0;
}

int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input9.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }    

    long nums[MAXCHAR];

    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; i++)
    {
        sscanf(str, " %ld", &nums[i]);
    }

	int currentPos = 25;
	while(sumInLast25(nums, currentPos) && currentPos < MAXCHAR) currentPos++;
	
	printf("pos %d, value %ld does not have a viable sum in the last 25 elements\n", currentPos, nums[currentPos]);
    
    return 0;
}