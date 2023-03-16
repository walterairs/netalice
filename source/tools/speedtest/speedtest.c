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
        case 1:
        char buff[255];
        FILE *logfile;
        logfile=fopen("speedtest.log", "r");
        fgets(buff, 255,(FILE*)logfile);
        printf("\n%s\n",buff);
        fclose(logfile);
            break;
        case 2:
            main();
            break;
    }
    return 0;
    
}

void speedtest()
{
    time_t mytime;
    char *t = NULL;

    mytime = time(NULL);
    t = ctime(&mytime);

    //write log file
    FILE *logfile;
    logfile=fopen("speedtest.log", "a+");
    fprintf(logfile,"Speed test done! at %s \n",t);
    fclose(logfile);
    printf("Ping in milliseconds!\n");
    system("ping -c 1 google.com | grep rtt | cut -d/ -f6");

    printf("\033[0;31mSpeedtest done!\033[0m\n");
    
}