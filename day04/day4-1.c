// advent of code day 4-1

// not 198


#include <stdio.h>
#include <string.h>
#define MAXCHAR 1000

int searchString(char str[MAXCHAR], char src[3])
{
    char *pch = strstr(str, src);
    //printf("searching %s...", src);
    if (pch) {
        //printf(" found.\n");
        return 1;
    }
    else 
    {
        //printf(" not found.\n");
        return 0;
    }
}

int stringEqu(char src[3], char equ[3], int len)
{
    for (int i=0; i<len; i++) if (src[i] != equ[i]) return 0;
    return 1;
}

int searchStringCheckParam(char str[MAXCHAR], char src[3])
{
    // first check if the string even exists
    char *pch = strstr(str, src);
    //printf("searching %s...", src);
    if (pch) {
        //printf(" found. Information: ");
    }
    else 
    {
        //printf(" not found.\n");
        return 0;
    }

    // then check for valid information
    char *loc = pch + 4; // the location of the data being checked
    if (stringEqu(src, "byr", 3))
    {
        //char in[4] = {loc[0],loc[1],loc[2],loc[3]};
        int read;
        sscanf(loc, " %d", &read);
        if (read >= 1920 && read <= 2002) return 1;
        else return 0;
    }
    if (stringEqu(src, "iyr", 3))
    {
        //char in[4] = {loc[0],loc[1],loc[2],loc[3]};
        int read;
        sscanf(loc, " %d", &read);
        if (read >= 2010 && read <= 2020) return 1;
        else return 0;
    }
    if (stringEqu(src, "eyr", 3))
    {
        //char in[4] = {loc[0],loc[1],loc[2],loc[3]};
        int read;
        sscanf(loc, " %d", &read);
        if (read >= 2020 && read <= 2030) return 1;
        else return 0;
    }
    if (stringEqu(src, "hgt", 3))
    {
        int read;
        char unit[2];
        sscanf(loc, "%d %c %c", &read, &unit[0], &unit[1]);
        if (stringEqu(unit, "cm", 2))
        {
            if (read >= 150 && read <= 193) return 1;
            else return 0;
        }
        else if (stringEqu(unit, "in", 2))
        {
            if (read >= 59 && read <= 76) return 1;
            else return 0;
        }
        else return 0;
    }
    if (stringEqu(src, "hcl", 3))
    {
        // get the 7 characters after loc
        char in[7];
        for (int i=0; i<7; i++) in[i] = loc[i];
        if (in[0] != '#') return 0; // check for '#'
        for (int i=1; i<7; i++) if ((in[i] < '0' || in[i] > '9') && (in[i] < 'a' || in[i] > 'f')) return 0;
        return 1;
    }
    if (stringEqu(src, "ecl", 3))
    {
        if (stringEqu(loc, "amb", 3)) return 1;
        if (stringEqu(loc, "blu", 3)) return 1;
        if (stringEqu(loc, "brn", 3)) return 1;
        if (stringEqu(loc, "gry", 3)) return 1;
        if (stringEqu(loc, "grn", 3)) return 1;
        if (stringEqu(loc, "hzl", 3)) return 1;
        if (stringEqu(loc, "oth", 3)) return 1;
        return 0;
    }
    if (stringEqu(src, "pid", 3))
    {   
        // check that there are integers for 9 places and no more or less after start
        for (int i=0; i<9; i++) if (!(loc[i] >= '0' && loc[i] <= '9')) return 0;
        if (loc[9] >= '0' && loc[9] <= '9') return 0;
        return 1;   
    }
    if (stringEqu(src, "cid", 3)) return 1;
    return 0;
}


int sumarray(int in[], int len)
{
    int sum = 0;
    for (int i=0; i<len; i++) sum += in[i];
    return sum;
}

int allArrayElementsPresent(int in[], int len)
{
    for (int i=0; i<len; i++) if (in[i] == 0) return 0;
    return 1;
}

int main(void)
{

    FILE *fp;
    char str[MAXCHAR];
    char* filename = "/home/cole/shared-drives/X:/AdventOfCode/input4.txt";
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    //char params[7][3] = { "byr" , "iyr" , "eyr" , "hgt" , "hcl" , "ecl" , "pid"};
    int total = 0; // total
    int numberPassports = 0;
    int numberDuplicates = 0;

    // import trees into file
    while(fgets(str, MAXCHAR, fp) != NULL)
    {
        
        static int yourmom[7] = {0,0,0,0,0,0,0}; // this must be 7 if the passort is valid
        static int mymom = 0;   // records the last count to check if a new line is present

        printf("\n-> %s", str);
        
        if (searchStringCheckParam(str, "byr")) yourmom[0]++;
        if (searchStringCheckParam(str, "iyr")) yourmom[1]++;
        if (searchStringCheckParam(str, "hgt")) yourmom[2]++;
        if (searchStringCheckParam(str, "eyr")) yourmom[3]++;
        if (searchStringCheckParam(str, "hcl")) yourmom[4]++;
        if (searchStringCheckParam(str, "ecl")) yourmom[5]++;
        if (searchStringCheckParam(str, "pid")) yourmom[6]++;

        // check for duplicates:
        for (int i=0; i<7; i++) if (yourmom[i] > 1) numberDuplicates++;

        // cid still counts as information even in a single line
        // if no new elements were detected in the line then it must be a blank line
        if (sumarray(yourmom,7) == mymom && !searchString(str, "cid:")) {
            for (int i=0; i<7; i++) yourmom[i] = 0;
            printf("newboi\n");
            numberPassports++;
        }
        
        printf("yourmom = %d\n", sumarray(yourmom,7));
        if (allArrayElementsPresent(yourmom,7)) {
            total++;
            printf("VALID. total = %d\n", total);
        }
        
        mymom = sumarray(yourmom,7);
    }

    printf("total was %d\n", total);
    printf("number of passports was %d\n", numberPassports);
    printf("number of duplicates was %d\n", numberDuplicates);

}

