// Joe Jevnik
// 14.10.2013
// Functions that handle user input and keeping score.
// many data

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "doge.h"

int mr,mc,c,mis = 0,sc = 0;
long st;

int wordc;
char **wordv;
//time_t t;
//struct tm*  t_;

// Phrases indicating a correct word.
#define NUM_CORR_PHRASES 11
char *CORR_PHRASES[] = { "wow",
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
char *INCORR_PHRASES[] = { "o no",
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
    int n = rand() % NUM_CORR_PHRASES;
    return CORR_PHRASES[n];
}

// Returns a pseudorandom phrase to denote a wrong character.
char *get_incorr_phrase(){
    int n = rand() % NUM_INCORR_PHRASES;
    return INCORR_PHRASES[n];
}

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
    wordv = (char**) malloc(wordc * sizeof(char*));
    for (int n = 0;fgets(lb,128,f);n++){
        wordv[n] = strdup(lb);
    }
    //time(&t);
    // t_ = localtime(&t);
    // st = t_->tm_sec;
    play_word();
}

void play_word(){
    clear();
    int in,col = 0;
    c = 0;
    char *word = wordv[rand() % wordc];
    mvprintdoge(0,0);
    attron(COLOR_PAIR(1));
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    mvprintw(7,69,"words:  %i",sc);
    //time(t);
    //t_ = localtime(t);
    //mvprintw(8,69,"WPM:    %i",(double) sc / (t_->tm_sec - st));
    mvprintw(8,69,"errors: %i",mis);
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
	  endwin();
	  exit(0);
	  break;
	case 19:
	  play_word();
	  break;
	case KEY_UP:
	case KEY_DOWN:
	case 10:
	    continue;
	    break;
	//case 263:
	case KEY_BACKSPACE:
	case 330:
	case 127:
	    if (col == 0){
		continue;
	    }
	    --col;
	    --c;
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
