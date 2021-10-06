// advent of code day 2 part 1
// cole fuerth

// answer was 634

#include <stdio.h>
#define MAXCHAR 1000

int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input2.txt";

    int valid = 0;
    int a, b, temp;
    char x;
    char gay;


    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        printf("%s", str);
        char m[MAXCHAR];
        for (int i=0; i<MAXCHAR; i++) m[i] = 0;
        sscanf(str, " %d %c %d %c %c %s", &a, &gay, &b, &x, &gay, m);    // gay stores the - and :
        if (m[a-1] == x ^ m[b-1] == x) {    // XOR
            valid++;  // if the number of characters is valid increase the count
            printf("\t\tVALID\n");  // print which ones are valid
        }
        else printf("\n");
    }
    printf("There are %d valid passwords.\n", valid);
    fclose(fp);
    return 0;

}