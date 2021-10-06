// day 8
// assembly loop finder

// not 65118771, lower

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000

int sumInLast25(long list[MAXCHAR], int pos)	// find
{
	for (int i=pos-25; i<pos-1; i++) for (int j=i+1; j<pos; j++) if (list[i] + list[j] == list[pos]) return 1;
	return 0;
}

long contiguousSum(long list[MAXCHAR], int pos)
{
	long sum = 0;
	for (int i=0; i<pos-2; i++) {
		sum = 0;
		for (int j=i+1; j<pos && sum < list[pos]; j++)	// i is lower bound, j is upper bound of sum
		{	
			sum = 0;
			for (int k=i; k<=j; k++) sum += list[k];
			if (sum == list[pos]) {
				long largest=list[i], smallest=list[i];
				for (int m=i+1; m<=j; m++)
				{
					if (list[m] > largest) largest = list[m];
					if (list[m] < smallest) smallest = list[m];
				}
				return largest + smallest;
			}
		}
	}
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

	long sum = contiguousSum(nums, currentPos);
	
	printf("pos %d, value %ld does not have a viable sum in the last 25 elements\n", currentPos, nums[currentPos]);
    printf("sum of lower and upper bound of sum range is %ld\n", sum);
   
    return 0;
}