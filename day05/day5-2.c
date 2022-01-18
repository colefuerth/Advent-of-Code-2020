// day 5 part 1
// plane tickets

#include <stdio.h>
#include <math.h>

#define INPUT_SIZE 814
#define MAXCHAR 1000

float avg(int a, int b)
{
    return (float)(a+b) / 2.0;
}

int swap(int *a, int *b)    // needs to be verified
{
    int c = *a; 
    *a = *b;
    *b = c;
    return 0;
}

void bubbleSort(int array[], int size)
{
    for (int i=0; i<size; i++)
    {
        for (int j=0; j<size-i-1; j++)
        {
            if (array[j] > array[j+1]) swap(&array[j], &array[j+1]);
        }
    }
    return;
}

int arrayDuplicates(int arr[], int len)
{
    int dupes = 0;
    for (int i=0; i<len-1; i++)
    {
        for (int j=i+1; j<len; j++) {
            if (arr[i] == arr[j] && i != j) {
                dupes++;
                printf("pos [%d] = %d is a dupe with [%d] = %d\n", i, arr[i], j, arr[j]);
            }
        }
    }
    return dupes;
}

int largestInArray(int arr[], int len)
{
    int largest = 0;
    for (int i=0; i<len; i++) if (arr[i] > largest) largest = arr[i];
    return largest;
}

int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input5.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }

    int tickets[INPUT_SIZE][2]; // 0=row 1=column
    int IDnumbers[INPUT_SIZE];
    for (int i=0; i<INPUT_SIZE; i++) IDnumbers[INPUT_SIZE] = 0;
    int numberElements = 0;
    int probleme = 0;

    // find all the ID numbers and store in IDnumbers[]
    for (int x=0; fgets(str, MAXCHAR, fp) != NULL; x++)
    {
        // print current line
        printf("\n");
        //for (int i=0; i<10; i++) {
            printf("%s", str);
        //}
        //printf("\n");

        // start by finding the row
        int upper = 127;
        int lower = 0;
        for (int i=0; i<6; i++) // rows
        {
            if (str[i] == 'B') lower = (int) ceil(avg(lower, upper)); // example went on the high side of a half 
            else upper = (int) floor(avg(lower, upper));
            printf("%c, %d, %d\n", str[i], lower, upper);
        }
        // store result
        if (str[6] == 'B') tickets[x][0] = upper;
        else tickets[x][0] = lower;
        if (upper - lower != 1) probleme++;
        printf("%c, %d\n", str[6], tickets[x][0]);

        // then find the column
        upper = 7;
        lower = 0;
        for (int i=7; i<9; i++) // rows
        {
            if (str[i] == 'R') lower = (int) ceil(avg(lower, upper)); // example went on the high side of a half 
            else upper = (int) floor(avg(lower, upper));
            printf("%c, %d, %d\n", str[i], lower, upper);
        }
        // store result
        if (str[9] == 'R') tickets[x][1] = upper;
        else tickets[x][1] = lower;
        if (upper - lower != 1) probleme++;
        printf("%c, %d\n", str[9], tickets[x][1]);

        IDnumbers[x] = (tickets[x][0] * 8) + tickets[x][1];
        printf("ID = %d\n", IDnumbers[x]);
        numberElements++;

    }

    // part 2 code:
    /*
     * There are blank seats at the front and back; do not count those
     * Your seat is the only ID missing, and the IDs before and after you exist
     */
    bubbleSort(IDnumbers, INPUT_SIZE);

    // find the start of the valid IDs
    int startOfValidIDs;
    for (int i=0; i<INPUT_SIZE; i++) if (IDnumbers[i] != 0) {
        startOfValidIDs = i;
        break;
    }

    // store the existing, valid IDs in an array
    int validIDs[numberElements];
    for (int i=0; i<numberElements; i++) validIDs[i] = IDnumbers[startOfValidIDs + i];

    for (int i=0; i<numberElements-1; i++) if (validIDs[i+1] - validIDs[i] > 1)
    {
        printf("prev: %d \tnext: %d \tyours: %d\n", validIDs[i], validIDs[i+1], validIDs[i]+1);
    }

    //printf("%d duplicates were found.\n", arrayDuplicates(IDnumbers, INPUT_SIZE));
    printf("largest was %d\n", largestInArray(IDnumbers, INPUT_SIZE));
    printf("total # bois was %d\n", numberElements);
    printf("%d problems detected\n", probleme);
}