/* File: downloadtest.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file contains the downloadtest function.
*  Created: 18-03-2023
*  Lisence: MIT
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "downloadtest.h"
#include <ncurses.h>
#include "../../ui/ui.h"
#include "../../main.h"

typedef struct {
    char *options[3];
} menuitems;

/**
 * @brief Downloadtest menu, shows options for downloadtest
 * 
 * @return int 
 */
int downloadtestmenu()
{
    menuitems items = {
        .options = {
            "Run downloadtest",
            "View logs",
            "Back"
        }
    };
    int choice = menu(items);
    switch (choice) {
    case 0:
        mvprintw(0, 0, "Running downloadtest...");
        downloadtest();
        break;
    case 1: {
        char buff[255];
        FILE *logfile;
        logfile=fopen("downloadtest.log", "r");
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
 * @brief Downloadtest, downloads a 10MB file from speedtest.tele2.net and saves the results to downloadtest.log
 * 
 * @return null
 */
void downloadtest() {
    system("wget -O /dev/null http://speedtest.tele2.net/1GB.zip | grep -E '? received' | cut -d, -f2 >> downloaftest.log");
    printf("Downloadtest complete. Check downloadtest.log for results.");
}