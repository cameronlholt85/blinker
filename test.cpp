#include <stdio.h>
#include <iostream>

void dec2bin(int num)
{

    bool binArray[8] = {};

    int tmp = num;

    for (int i = 4; i > 0; i--)
    {
        binArray[i - 1] = tmp % 2;
        tmp = tmp / 2;
    }

    for (int i = 0; i < 4; i++)
    {
        // printf("%d", binArray[i]);
        if (binArray[i])
        {
            printf("green \n");
        }
        else
        {
            printf("red \n");
        }
    }

    printf("\n\n");
}

int main()
{
    int hh = 9;

    printf(" %d \n", 20 / 5);
    printf(" %d \n", 30 / 5);
    printf(" %d \n", 40 / 5);
    printf(" %d \n", 43 / 5);
    printf(" %d \n", 46 / 5);

    dec2bin(hh);
}