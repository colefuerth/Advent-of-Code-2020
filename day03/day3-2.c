// advent of code day 3 part 1
// cole fuerth


#include <stdio.h>
#define MAXCHAR 1000
#define height  323
#define width   31

int main(void)
{
    FILE *fp;
    char str[32];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input3.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    char trees[height][width];
    int down[5] = {1,1,1,1,2};
    int right[5] = {1,3,5,7,1};
    int totals[5] = {0,0,0,0,0};

    // import trees into file
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; i++)
    {
        for (int j=0; j<width; j++) trees[i][j] = str[j];
        //printf("%s\n", trees[i]);
    }

    for (int n=0; n<5; n++)
    {
        int x=0; 
        for (int i=0; i<height; i += down[n])
        {
            if (trees[i][x] == '#')
            {
                totals[n]++;
                //trees[i][x] = 'X';
            }
            //else trees[i][x] = 'O';
            x += right[n];
            if (x>=31) x = x % 31;
            //printf("%s\n", trees[i]);
        }
    }

    long bigboy = 1;
    for (int i=0; i<5; i++) {
        bigboy *= (long) totals[i];
        printf("Number of trees was %d\n", totals[i]);
    }
    printf("bigboy is %ld\n", bigboy);
   
    return 0;

}