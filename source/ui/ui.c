/* File: ui.c
*  Author(s): 1) Valtteri Äyräs 2) Niklas Suvitie
*  Description: This file generates the TUI for the program.
*  Created: 11-03-2023
*  Lisence: MIT
*/

#include <ncurses.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include "ui.h"

typedef struct {
    char *options[3];
} menuitems;

/**
 * @brief generates the TUI menu for the program
 * @param struct menuitems
 * @return int 
 */
int menu(menuitems items) {
    initscr();
    cbreak();
    noecho();

    int rows, cols;
    getmaxyx(stdscr, rows, cols);

    int menu_width = 20;
    int menu_height = 5;
    int menu_x = (cols - menu_width) / 2;
    int menu_y = (rows - menu_height) / 2;

    resize_term(rows, cols);
    clear();

    int choice = 0;
    char c;
    char *holdertext = "placeholder";

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    while(1) {
        c = NULL;
        clear();
        mvprintw(menu_y - 3, menu_x, "Alice says ");
        attron(COLOR_PAIR(1));
        printw("Hi!");
        attroff(COLOR_PAIR(1));
        mvprintw(menu_y - 2, menu_x - 4, "Use W, S and Space to navigate");

        while (c == NULL) {
            switch (choice) {
                case 0:
                    mvprintw(menu_y, menu_x, "-> %s", items.options[0]);
                    mvprintw(menu_y + 1, menu_x, "   %s", items.options[1]);
                    mvprintw(menu_y + 2, menu_x, "   %s", items.options[2]);
                    break;
                case 1:
                    mvprintw(menu_y, menu_x, "   %s", items.options[0]);
                    mvprintw(menu_y + 1, menu_x, "-> %s", items.options[1]);
                    mvprintw(menu_y + 2, menu_x, "   %s", items.options[2]);
                    break;
                case 2:
                    mvprintw(menu_y, menu_x, "   %s", items.options[0]);
                    mvprintw(menu_y + 1, menu_x, "   %s", items.options[1]);
                    mvprintw(menu_y + 2, menu_x, "-> %s", items.options[2]);
                    break;
            }
            c = getch();
        }
        switch (c) {
            case 'w':
                if (choice > 0) {
                    choice--;
                }
                break;
            case 's':
                if (choice < 2) {
                    choice++;
                }
                break;
            case ' ':
                endwin();
                return choice;
        }
    }
    endwin();
    return 0;
}
