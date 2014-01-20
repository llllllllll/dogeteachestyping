// Joe Jevnik
// 14.10.2013
// Functions that handle user input and keeping score.
// many data

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "doge.h"

// Max row, max column, current char, word count, mistake count, score
int mr,mc,c,wordc,mis = 0,sc = 0,not_playing = 1; // is the game not running.
time_t time_ctr = 0,s = 0; // The time counter and the the game itself starts.
char **wordv; // The word list loaded from /usr/share/dict/words

// Phrases indicating a correct word.
#define NUM_CORR_PHRASES 11
static char *CORR_PHRASES[] = { "wow",
				"wow",
				"such smart",
				"such letters",
				"such spell",
				"many letters",
				"how smart",
				"good",
				"very typing",
				"how keyboard",
				"top doge" };

// Phrases indicating a mistyped letter.
#define NUM_INCORR_PHRASES 9
static char *INCORR_PHRASES[] = { "o no",
				  "wat",
				  "pls",
				  "pls no",
				  "why",
				  "mabe next time",
				  "such learning",
				  "top kek",
				  "you can do it" };

// Returns a pseudorandom phrase to denote a correctly spelled word.
char *get_corr_phrase(){
    return CORR_PHRASES[rand() % NUM_CORR_PHRASES];
}

// Returns a pseudorandom phrase to denote a wrong character.
char *get_incorr_phrase(){
    return INCORR_PHRASES[rand() % NUM_INCORR_PHRASES];
}

// Loads the word file and counts the words. mallocs a char** to hold every word
// and mallocs each word in it.
// ERROR: Errors if the words file cannot be read and exits with exit(1).
void start_game(){
    getmaxyx(stdscr,mr,mc);
    FILE *f = fopen("/usr/share/dict/words","r");
    char lb[128];
    if (f == NULL){
	clear();
	mvprintw(0,0,"ERROR:file:'/usr/share/dict/words' not found");
	mvprintw(1,0,"Press any key to continue...");
	refresh();
	getch();
	exit(1);
    }
    for (wordc = 0;fgets(lb,128,f);wordc++);
    fseek(f,0,SEEK_SET);
    wordv = malloc(wordc * sizeof(char*));
    for (int n = 0;fgets(lb,128,f);n++){
        wordv[n] = strdup(lb);
    }
    time(&s);
    not_playing = 0;
    play_word();
}

// Plays one word.
// Increments sc for every word you get correct.
// Increments c for every letter you get correct.
// Increments mis for every letter you get incorrect.
void play_word(){
    move(3,60);
    clrtoeol();
    move(5,60);
    clrtoeol();
    move(6,60);
    clrtoeol();
    move(7,60);
    clrtoeol();
    move(8,60);
    clrtoeol();
    move(9,60);
    clrtoeol();
    int in,col = 0;
    char *word = wordv[rand() % wordc];
    c = 0;
    //mvprintdoge(0,0);
    attron(COLOR_PAIR(1));
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    mvprintw(7,69,"words:  %i",sc);
    mvprintw(8,69,"errors: %i",mis);
    mvprintw(9,69,"wps:    %f", (double) sc / (time_ctr - s));
    mvprintw(10,69,"time:   %i",time_ctr - s);
    attron(A_BOLD);
    mvprintw(3,69,"%s",word);
    mvprintw(5,67,"> ");
    attroff(A_BOLD);
    curs_set(1);
    while(1){
	if (word[c] == '\n'){
	    ++sc;
	    play_word();
	    break;
	}
	in = getch();
	switch(in){
	case 3:
	  for (int n = 0;n < wordc;n++){
	      free(wordv[n]);
	  }
	  free(wordv);
	  pthread_cancel(time_thread);
	  endwin();
	  exit(0);
	  break;
	case 19:
	  play_word();
	  break;
	case KEY_RESIZE:
	    move(mr-1,mc-13);
	    clrtoeol();
	    endwin();
	    getmaxyx(stdscr,mr,mc);
	    mvprintw(mr-1,mc-13,"by Joe Jevnik");
	    move(5,69);
	    refresh();
	    continue;
	    break;
	case KEY_UP:
	case KEY_DOWN:
	case 10:
	    continue;
	    break;
	case KEY_BACKSPACE:
	case 330:
	case 127:
	    if (col == 0){
		continue;
	    }
	    --col;
	    printw("\b \b");
	    continue;
	    break;
	case 6:
	case KEY_RIGHT:
	    move(5,getcurx(stdscr)+1);
	    ++col;
	    continue;
	    break;
	case 2:
	case KEY_LEFT:
	    if (col == 0){
		continue;
	    }
	    move(5,getcurx(stdscr)-1);
	    --col;
	    continue;
	    break;
	}
	printw("%c",in);
	if (in == word[c] && col == c){
	    ++c;
	    if (rand() % 2){
		mvprintw(20,62,"________________");
		mvprintw(21,61,"/                \\");
		mvprintw(22,60,"<  ");
		attron(A_BOLD);
		printw("%-15s",get_corr_phrase());
		attroff(A_BOLD);
		printw(" |");
		mvprintw(23,61,"\\_________________/");
		move(5,col+70);
		refresh();
	    }
	} else {
	    mvprintw(8,69,"errors: %i",++mis);
	    move(5,col+70);
	    if (rand() % 2){
		mvprintw(20,62,"________________");
		mvprintw(21,61,"/                \\");
		mvprintw(22,60,"<  ");
		attron(A_BOLD);
		printw("%-15s",get_incorr_phrase());
		attroff(A_BOLD);
		printw(" |");
		mvprintw(23,61,"\\_________________/");
		move(5,col+70);
		refresh();
	    }
	}
	++col;
    }
}

// Hides the time if needed.
void show_time(){
    if (not_playing){
	attron(A_INVIS);
    }
    move(9,69);
    clrtoeol();
    move(10,69);
    clrtoeol();
    mvprintw(9,69,"wps:    %f", (double) sc / (time_ctr - s));
    mvprintw(10,69,"time:   %i",time_ctr - s);
    if (not_playing){
	attroff(A_INVIS);
    }
}
