/* File: main.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file contains the main function, which is the entry point of the program.
*  Created: 11-03-2023
*  Lisence: MIT
*/

#include "ui/ui.h"
#include "tools/speedtest/speedtest.h"
#include "tools/downloadtest/downloadtest.h"
#include <ncurses.h>

typedef struct {
    char *options[3];
} menuitems;

/**
 * @brief Main menu, shows options for the program
 * 
 * @return int 
 */
int main() {
    menuitems items = {
        .options = {
            "Speed test",
            "Download test",
            "Exit"
        }
    };
    int choice = menu(items);
    switch (choice) {
        case 0:
            mvprintw(0, 0, "Running speedtest...");
            speedtestmenu();
            break;
        case 1:
            mvprintw(0, 0, "Running downloadtest...");
            downloadtestmenu();
            break;
        case 2:
            break;
    }
    return 0;
}