#include <stdio.h>
#include <stdlib.h>
#include "speedtest.h"

void speedtest()
{
    printf("Speedtest!\n");
    system("ping -c 1 google.com");

    printf("\033[0;31mSpeedtest done!\033[0m\n");
}

void speedtest2()
{
    printf("Speedtest2!\n");
    system("ping -c 1 google.com");

    printf("\033[0;31mSpeedtest2 done!\033[0m\n");
}