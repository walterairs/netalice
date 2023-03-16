#include "ui/ui.h"
#include "tools/speedtest/speedtest.h"
#include <ncurses.h>

typedef struct {
    char *options[3];
} menuitems;

int main() {
    menuitems items = {
        .options = {
            "Speedtest",
            "Run pingtest",
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
            break;
        case 2:
            break;
    }
    return 0;
}