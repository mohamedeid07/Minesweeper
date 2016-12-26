#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "funcF.h"


int getGrid(void)
{
    long long number;
    char buffer;  // Holds last character from user input.
    // (i.e '\n' or any other character besides numbers)
    int flag;     // Holds scanf return value
    do
    {
        flag = scanf("%lld%c", &number, &buffer); // Gets input from user
        // While scanf did not read 2 objects (i.e 1 int & 1 char)
        // or the user inputed a number and then a character (eg. 12te)
        // ask user to type a valid value
        while (flag !=2 || buffer!='\n')
        {
            clean_input();
            printf("%s","Type an appropriate integer: ");
            flag = scanf("%lld%c", &number, &buffer);
        }

        if(number<2)
        {
            printf("%s","You have entered a too small size.\n"
                   "Please type a positive integer from 2 to 30: ");

        }
        else if(number>30)
        {
            printf("%s","You have entered a too large size.\n"
                   "Please type a positive integer from 2 to 30: ");
        }
        else       // If user typed an appropriate value, exit do-while.
        {
            break;
        }
    }
    while(1);
    return number;
}




int getCoordinates(void)
{
    long long number;
    char buffer;
    int flag;
    do
    {
        flag = scanf("%lld%c", &number, &buffer);
        while (flag !=2 || buffer!='\n')
        {
            clean_input();
            printf("%s","Type an appropriate integer: ");
            flag = scanf("%lld%c", &number, &buffer);
        }
        if(number<1 || number>30)
        {
            printf("%s","Please type an appropriate Coordinate: ");
        }
        else
        {
            break;
        }
    }
    while(1);
    return number;
}




int getOption(void)
{
    long long number;
    char buffer;
    int flag;
    do
    {
        flag = scanf("%lld%c", &number, &buffer);
        while (flag !=2 || buffer!='\n')
        {
            clean_input();
            printf("%s","Type an appropriate option number: ");
            flag = scanf("%lld%c", &number, &buffer);
        }
        if(number<=0 || number>5)
        {
            printf("%s","Please select an appropriate option number: ");
        }
        else
        {
            break;
        }
    }
    while(1);
    return number;
}

int getG(void)
{
    long long number;
    char buffer;
    int flag;
    do
    {
        flag = scanf("%lld%c", &number, &buffer);
        while (flag !=2 || buffer!='\n')
        {
            clean_input();
            printf("%s","Type an appropriate option number: ");
            flag = scanf("%lld%c", &number, &buffer);
        }
        if(number<1 || number>3)
        {
            printf("%s","Select an appropriate option number: ");
        }
        else
        {
            break;
        }
    }
    while(1);
    return number;
}
int getG1(void)
{
    long long number;
    char buffer;
    int flag;
    do
    {
        flag = scanf("%lld%c", &number, &buffer);
        while (flag !=2 || buffer!='\n')
        {
            clean_input();
            printf("%s","Type an appropriate option number: ");
            flag = scanf("%lld%c", &number, &buffer);
        }
        if(number<1 || number>2)
        {
            printf("%s","Select an appropriate option number: ");

        }
        else
        {
            break;
        }
    }
    while(1);
    return number;
}
void clean_input(void)
{
    while (getchar()!='\n');
    return;
}
void clrscr()
{
    system("@cls||clear");
}
void MineSweeper(void)
{
    printf("   *     *                  *****\n");
    printf("   **   ** * *    * ****** *     * *     * ****** ****** *****  ****** *****\n");
    printf("   * * * * * *    * *      *       *     * *      *      *    * *      *    *\n");
    printf("   *  *  * * * *  * *****   *****  *  *  * *****  *****  *    * *****  *    *\n");
    printf("   *     * * *  * * *            * * * * * *      *      *****  *      *****\n");
    printf("   *     * * *   ** *      *     * **   ** *      *      *      *      *   *\n");
    printf("   *     * * *    * ******  *****  *     * ****** ****** *      ****** *    *\n");
    printf("\n                                                     Ali Rihan & Mohamed Eid\n");
    printf("\n\n\n                    1-New Game   2-Load Game   3-Score Board\n");
    printf("\n\n\n                               Select Option:");
}
