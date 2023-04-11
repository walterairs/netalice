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
    int returnValue = 0;
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
        returnValue = speedtest();
        if(returnValue == 1){
            break;
        }else{
            speedtestmenu();
        }
        break;
    case 1: {
        showTestAmount();
        main();
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
int speedtest()
{
    system("ping -c 1 google.com | grep -E '? received' | cut -d, -f2 > connection_test.txt");
    FILE* conTest = fopen("connection_test.txt", "r");
    if (conTest == NULL) {
        printf("no such file.");
    }
 
    char buf[100];
    int flag = 0;
    fscanf(conTest, "%s ", buf);
    if (strcmp(buf, "1") == 0){
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
        system("ping -c 1 google.com | grep rtt | cut -d/ -f6 >> speedtest.log");

        return 0;
        }
        else{
            printf("You have no network connection\n");
            return 1;
        }
}

void showTestAmount(){
    int count = 0;
    // Initialize curses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    resize_term(rows, cols);
    clear();

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
        while ((pos = strstr(str + index, word)) != NULL)
        {
            index = (pos - str) + 1;

            testAmount++;
        }
    }

    fclose(logfile);
    mvprintw(count+1, 20, "Speedtest have been done %d times.\n",testAmount);
    system("awk '!/Speed/ && !/result/ {print}' speedtest.log | tail -n 1 > speedstemp.log");
    FILE *tempSpeed;
    tempSpeed=fopen("speedstemp.log","r");
    char tempvalue[10];
    fscanf(tempSpeed, "%s", tempvalue);
    
    mvprintw(count+2, 20, "Most recent result:");
    attron(COLOR_PAIR(1));
    mvprintw(count+3, 20, "%s",tempvalue);
    attroff(COLOR_PAIR(1));
    mvprintw(count+6, 20, "press any key to continue...");

    fclose(tempSpeed);
    
    // End curses
    refresh();
    getch();
    endwin();
}