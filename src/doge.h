// Joe Jevnik
// 14.10.2013
// Forward declare the functions and some literals.
// Such headers.

#ifndef DOGE_H
#define DOGE_H
#include <pthread.h>

// Thread access
pthread_t *get_time_thread();

// Screens
void init_menu();
void show_menu();
void print_time(void*);

// Game
void start_game();
void play_word();
void show_time(time_t);

char * doge_img();

// Macros to print doge quicker.
#define printdoge() \
    do { \
    attron(COLOR_PAIR(1)); \
    printw("%s",doge_img());\
    attroff(COLOR_PAIR(1)); \
    } while (0);
#define mvprintdoge(r,c) \
    do {		   \
    attron(COLOR_PAIR(1)); \
    mvprintw(r,c,"%s",doge_img());\
    attroff(COLOR_PAIR(1));\
    } while (0);

#endif
