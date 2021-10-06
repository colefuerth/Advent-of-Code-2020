// day 6 part 1
// questionnaire

// answer 1 was 6799

#include <stdio.h>
#include <string.h>

#define MAXCHAR 1000

int sumArray(int arr[], int len)
{
    int sum = 0;
    for (int i=0; i<len; i++) sum += arr[i];
    return sum;
}

int searchCharInStr(char str[], int len, char c)
{
    int total = 0;
    for (int i=0; i<len; i++) if (str[i] == c) total++;
    return total;
}

int presentInArray(int arr[], int len)
{
    int present = 0;
    for (int i=0; i<len; i++) if (arr[i] > 0) present++;
    return present;
}

int presentInAllSurveys(int arr[26][10], int man)
{
    int total = 0;
    for (int i=0; i<26; i++) 
    {
        int test = 1;
        for (int j=0; j<man; j++){
            if (arr[i][j] == 0) test = 0;
        }
        if (test) total++;
    }
    return total;
}

int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input6.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s\n",filename);
        return 1;
    }

    int answered[1000];
    for (int i=0; i<1000; i++) answered[i]=0;

    int currentSurvey = 0;
    int currentMan = 0;
    int alphabetExists[26][10];
    for (int i=0; i<26; i++) for (int j=0; j<10; j++) alphabetExists[i][j] = 0;
    

    while (fgets(str, MAXCHAR, fp) != NULL)
    {

        printf("\n-> %s", str);
        //printf("length = %ld\n", strlen(str));

        int newLineDetected = 1;

        for (int i=0; i<26; i++) 
        {
            int temp = searchCharInStr(str, strlen(str), 'a' + i); // search for each letter of the alphabet
            alphabetExists[i][currentMan] += temp;
            if (temp) newLineDetected = 0;
        }

        if (newLineDetected)
        {
            int temp = presentInAllSurveys(alphabetExists, currentMan);
            printf("newboi detected, sum is %d\n", temp);
            answered[currentSurvey++] = temp;
            for (int i=0; i<26; i++) for (int j=0; j<10; j++) alphabetExists[i][j] = 0;
            currentMan = 0;
        }
        else currentMan++;
        
    }

    answered[currentSurvey++] = presentInAllSurveys(alphabetExists, currentMan);// new line not at the end of program, so gotta do the last one manually

    int answer = sumArray(answered, currentSurvey);

    /*int test[] = {2,2,5,2,0,0};
    printf("test result is %d\n", presentInArray(test, 6));
    printf("test sum is %d\n", sumArray(test, 6));*/

    /*char string[100] = "your mom smells like an egg";
    char searched = 'm';
    printf("There are %d occurences of %c in '%s'\n", searchCharInStr(string, strlen(string), searched), searched, string);
    printf("there are %ld characters in this string.\n", strlen(string));*/

    printf("Answer is %d\nNumber of surveys was %d\n", answer, currentSurvey);
    return 0;
}