/* File: speedtest.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file contains the speedtest function.
*  Created: 11-03-2023
*  Lisence: MIT
*/

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "speedtest.h"
#include <ncurses.h>
#include "../../ui/ui.h"
#include "../../main.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

typedef struct {
    char *options[3];
} menuitems;

/**
 * @brief Speedtest menu, shows options for speedtest
 * 
 * @return int 
 */
int speedtestmenu()
{
    menuitems items = {
        .options = {
            "Run speedtest",
            "View logs",
            "Back"
        }
    };
    int choice = menu(items);
    switch (choice) {
    case 0:
        mvprintw(0, 0, "Running speedtest...");
        speedtest();
        break;
    case 1: {
        char buff[255];
        FILE *logfile;
        logfile=fopen("speedtest.log", "r");
        if (logfile != NULL) {
            fgets(buff, 255, logfile);
            printf("\n%s\n",buff);
            fclose(logfile);
        } else {
            printf("Error opening file.\n");
        }
        break;
    }
    case 2:
        main();
        break;
    }
    return 0;
    
}

/**
 * @brief Speedtest function, runs speedtest and logs it
 * 
 */
void speedtest()
{
    //check connection
    system("ping -c 1 google.com | grep -E '? received' | cut -d, -f2 > connection_test.txt");
    FILE* conTest = fopen("connection_test.txt", "r");
    if (conTest == NULL) {
        printf("no such file.");
    }
 
    char buf[100];
    int flag = 0;
    fscanf(conTest, "%s ", buf);
    if (strcmp(buf, "1") == 0){
        //there is connection
        flag = 1;
    }

    if (flag == 1){
        time_t mytime;
        char *t = NULL;

        mytime = time(NULL);
        t = ctime(&mytime);

        FILE *logfile;
        logfile=fopen("speedtest.log", "a+");
        fprintf(logfile,"Speed test done at %sresult below in milliseconds:\n",t);
        fclose(logfile);
        printf("Ping in milliseconds!\n");
        system("ping -c 1 google.com | grep rtt | cut -d/ -f6 | tee -a speedtest.log");

        printf( GREEN "Speedtest done!\n" RESET);
        }
        else{
            printf("You have no network connection\n");
        }
        showTestAmount();
}

void showTestAmount(){
    int *testAmountArray = NULL;
    FILE *logfile;
    logfile=fopen("speedtest.log", "r");
    char str[10000];
    char *pos;
    static const char word[] = "Speed";
    int index = 0;
    int testAmount = 0;
    while ((fgets(str, 10000, logfile)) != NULL)
    {
        index = 0;

        // Find next occurrence of word in str
        while ((pos = strstr(str + index, word)) != NULL)
        {
            // Index of word in str is
            // Memory address of pos - memory
            // address of str.
            index = (pos - str) + 1;

            testAmount++;
        }
    }

    fclose(logfile);
    printf("Speedtest have been done %d times.\n",testAmount);

    testAmountArray = (int*) malloc(testAmount * sizeof(int));

    if(testAmountArray == NULL){
        printf("Dynamic memory allocation failed\n");
    }else{
        for(index = 0; index < testAmount; index++){
			*(testAmountArray + index) = 0;
		}
    }
    printf("Here is placeholder array\n"); //this array will have 1 if ping over 25ms or 0 if ping under 25ms
	int loop = 0;
	for(loop = 0; loop < testAmount; loop++)
    	printf("%d ", *(testAmountArray + loop));
	
    printf("\n");

    free(testAmountArray);
    
}