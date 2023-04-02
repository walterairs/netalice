/* File: downloadtest.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file contains the downloadtest function.
*  Created: 18-03-2023
*  Lisence: MIT
*/

#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "downloadtest.h"
#include <ncurses.h>
#include "../../ui/ui.h"
#include "../../main.h"
#include <stdio.h>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"

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
        mvprintw(0, 0, "Downloadtest complete. Check downloaftest.log for results.");
        downloadtestmenu();
        break;
    case 1: {
        downloadLog();
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
 * @brief Downloadtest, downloads a 10MB file from speedtest.tele2.net and saves the results to downloadtest.log
 * 
 * @return null
 */
void downloadtest() {

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
        system("wget -O /dev/null http://speedtest.tele2.net/10MB.zip > downloadtest.txt 2>&1");
        system("tail -n 2 downloadtest.txt | head -n 1 | awk '{print $0\"\\n\"}' >> downloadtest.log");
        system("rm downloadtest.txt");
    }
    else{
        printf("You have no network connection\n");
    }
    
}

/**
 * @brief Downloadlog, reads the downloadtest.log file and prints the speeds
 * 
 * @return null
 */
int downloadLog(){

    // Fetch number of lines in file
    system("wc -l downloadtest.log > downloadtest.txt");
    FILE* lineCount = fopen("downloadtest.txt", "r");
    if (lineCount == NULL) {
        printf("No such file.");
        return 1;
    }
    char sbuf[100];
    fscanf(lineCount, "%s", sbuf);
    int num_lines = atoi(sbuf);
    system("rm downloadtest.txt");

    // Initialize curses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    resize_term(rows, cols);
    clear();

    // Allocate memory for speeds array
    int* speeds = malloc(num_lines * sizeof(int));

    // Open log file and extract speed values
    FILE* log = fopen("downloadtest.log", "r");
    if (log == NULL) {
        endwin();
        printf("No such file.");
        return 1;
    }
    char buf[100];
    int count = 0;
    while (fscanf(log, "%s", buf) != EOF) {
        if (buf[4] == '-') {
            // Assign the date to a variable
            char* date = buf;
            mvprintw(count+1, 20, "Date: ");
            attron(COLOR_PAIR(1));
            printw("%s ", date);
            attroff(COLOR_PAIR(1));
        }
        if (buf[2] == ':') {
            // Assign the time to a variable
            char* time = buf;
            mvprintw(count+1, 40, "Time: ");
            attron(COLOR_PAIR(1));
            printw("%s ", time);
            attroff(COLOR_PAIR(1));
        }
        if (buf[0] == '(') {
            char* num_start = buf + 1;
            int new_num = atoi(num_start);
            mvprintw(count+1, 60, "Speed: ");
            printw("%d MB/s", new_num);
            speeds[count] = new_num;
            count++;
        }
    }

    // Calculate average speed
    int sum = 0;
    for (int i = 0; i < num_lines; i++) {
        sum += speeds[i];
    }
    double average_speed = (double)sum / (num_lines / 2);

    // Display average speed
    mvprintw(count+1, 20, "Average speed according to record: ");
    attron(COLOR_PAIR(1));
    printw("%.2f", average_speed);
    attroff(COLOR_PAIR(1));

    mvprintw(count+2, 20, "press any key to continue...");

    // Clean up
    fclose(log);
    fclose(lineCount);
    free(speeds);

    // End curses
    refresh();
    getch();
    endwin();

    return 0;
}