// Joe Jevnik
// 14.10.2013
// lets make program

#include <ncurses.h>
#include <pthread.h>
#include "doge.h"
#define EXIT_SUCCESS 0

pthread_t pt;

// Spawns the time thread and the main thread.
int main(){
    pthread_create(&pt,NULL,print_time,NULL);
    init_menu();
    return EXIT_SUCCESS;
}

pthread_t *get_time_thread(){
    return &pt;
}
