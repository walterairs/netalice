/* File: speedtest.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file contains the speedtest function.
*  Created: 11-03-2023
*  Lisence: MIT
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "speedtest.h"
#include <ncurses.h>
#include "../../ui/ui.h"
#include "../../main.h"

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
    system("ping -c 1 google.com | grep -E '? received' | cut -d, -f2 >> testi.txt");

    time_t mytime;
    char *t = NULL;

    mytime = time(NULL);
    t = ctime(&mytime);

    FILE *logfile;
    logfile=fopen("speedtest.log", "a+");
    fprintf(logfile,"Speed test done! at %s \n",t);
    fclose(logfile);
    printf("Ping in milliseconds!\n");
    system("ping -c 1 google.com | grep rtt | cut -d/ -f6");

    printf("\033[0;31mSpeedtest done!\033[0m\n");
    
}