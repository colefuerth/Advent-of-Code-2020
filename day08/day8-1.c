// day 8
// assembly loop finder

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000

int strequ(char a[], char b[])
{
    for (int i=0; i<3; i++) if (a[i] != b[i]) return 0;
    return 1;
}

int searchArray(int executed[], int programPointer)
{
    for (int i=0; i<MAXCHAR; i++) if (programPointer == executed[i]) return 1;
    return 0;
}

int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input8.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }    

    char bois[MAXCHAR][3];
    int nums[MAXCHAR];
    int numcmds = 0;

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        sscanf(str, " %c%c%c%d", &bois[numcmds][0], &bois[numcmds][1], &bois[numcmds][2], &nums[numcmds]);
        numcmds++;
    }

    int programPointer = 0;
    int acc = 0;
    int executed[MAXCHAR];
    for (int i=0; i<MAXCHAR; i++) executed[i] = -1;
    int linesExecuted = 0;
    int currentPointer = 0;  // the location of the jmp/nop that is being swapped for this trial

    while(programPointer<numcmds)
    {
        int nopFlag, jmpFlag;   // flags tell whether jmp or nop is being swapped
        for ( ; strequ(bois[currentPointer], "acc"); currentPointer++);  // find next location of a jmp or nop
        if (strequ(bois[currentPointer], "nop"))
        {
            nopFlag = 0;
            jmpFlag = 1;
        }
        else
        {
            nopFlag = 1;
            jmpFlag = 0;
        }
        
        // reset for next test
        programPointer = 0;
        acc = 0;
        executed[MAXCHAR];
        for (int i=0; i<MAXCHAR; i++) executed[i] = -1;
        linesExecuted = 0;

        printf("trial at jmp/nop at %d...", currentPointer);

        while(1)
        {
            for (int i=0; i<3; i++) printf("%c", bois[programPointer][i]);
            printf(" %d\tacc=%d\tpp=%d\n", nums[programPointer], acc, programPointer);

            if (searchArray(executed, programPointer)) 
            {
                printf("failed.\n");
                break;
            }
            if (programPointer >= numcmds)
            {
                printf("Succeeded!\n");
                break;
            }
            if ((strequ(bois[programPointer], "nop") && currentPointer != programPointer) || (currentPointer == programPointer && nopFlag))
            {
                executed[linesExecuted++] = programPointer++;   // store value of the line just run
            }
            else if (strequ(bois[programPointer], "acc"))
            {
                acc += nums[programPointer];
                executed[linesExecuted++] = programPointer++;   // store value of the line just run
            }
            else if ((strequ(bois[programPointer], "jmp") && currentPointer != programPointer) || (currentPointer == programPointer && jmpFlag))
            {
                executed[linesExecuted++] = programPointer;   // store value of the line just run
                programPointer += nums[programPointer];
            }
            else
            {
                printf("INSTRUCTION NOT FOUND\n");
                return 0;
            }
        }
        currentPointer++;   // need to increment by one before doing the skip acc's again
    }

    printf("The value of the accumulator is %d\n", acc);
    printf("The value of the program pointer is %d\n", programPointer);
    printf("currentPointer was %d", currentPointer);
   
    return 0;
}