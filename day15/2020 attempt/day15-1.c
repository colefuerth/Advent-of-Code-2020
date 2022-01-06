// day 15: memory game

#include <stdio.h>

// returns the index of the number it found, -1 means not found
long searchArray(long arr[], long length, long search)   
{
    for (long i=length-2; i>=0; i--) if (arr[i] == search) return i;
    return -1;
}

int currentPlace(long currentPos)
{
    return currentPos % 1000;
}

int main(void)
{
    long target = 30000000;
    long input[] = {16,1,0,18,12,14,19}; // declare input
    long inputLength = sizeof(input) / sizeof(input[0]); // number of integers in input set
    printf("inputLength is %d\n", inputLength);
    printf("Declaring arr...");
    long arr[target]; // memory set for question
    printf("done.\n");
    int currentTurn;  // current turn, ah yes very descriptive
    printf("assigning the first %ld values...", inputLength);
    for (long i=0; i<inputLength; i++) arr[i] = input[i];  // empty the initial input into the mem array
    printf("done.\n");
    // start of main code
    for (currentTurn = inputLength ; currentTurn < target; currentTurn++)
    {
        long temp = searchArray(arr, currentTurn, arr[currentTurn-1]);
        if (temp == -1) arr[currentTurn] = 0;
        else if (arr[currentTurn-1] == arr[currentTurn-2]) arr[currentTurn] = 1;
        else arr[currentTurn] = currentTurn-1 - temp;
        if (currentTurn % 100 == 0) printf("reached %ld\n", currentTurn);
    }

    printf("the %ldth spoken number is %ld\n", target, arr[target-1]);

}