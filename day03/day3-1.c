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

    // import trees into file
    for (int i=0; fgets(str, MAXCHAR, fp) != NULL; i++)
    {
        for (int j=0; j<width; j++) trees[i][j] = str[j];
        //printf("%s\n", trees[i]);
    }
    int num = 0;
    for (int i=0; i<height; i++)
    {
        static int x=0; 
        if (trees[i][x] == '#')
        {
            num++;
            trees[i][x] = 'X';
        }
        else trees[i][x] = 'O';
        x += 3;
        if (x>=31) x = x % 31;
        printf("%s\n", trees[i]);
    }

    printf("Number of trees was %d\n", num);
   
    return 0;

}