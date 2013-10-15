// Joe Jevnik
// 14.10.2013
// The various screens and menus to be displayed throughout the game.
// such menus

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "doge.h"

int mr,mc,opt = 0;

// ASCII art doge.
char *doge_img(){
  return
    "         ***                          ++                     \n"
    "        +=-==+                      +++=-                    \n"
    "       +-:---==+                   *+=----=                  \n"
    "      +-:------==+               ++=------==                 \n"
    "      =-----------=++=========================               \n"
    "     +--:::::---:-----============-=======+++====            \n"
    "     +---:..:----::-===============-======+++++++++          \n"
    "     =---:...---:-===================---===++++++++++        \n"
    "     +----:...:-=======================--==+++++++++++       \n"
    "     +-:------====================++===---==++++===+++++     \n"
    "    +=-----======================+++++==---==+==-::=++**+    \n"
    "   +=-----================---=======++=========::.:-+*****   \n"
    "  +==::-====================--:  --:-====++=+===:..-=+*****  \n"
    "  +=---=====================-...  :=..:-=+++++++++===++***** \n"
    "  +=---=====+=++++++++++++++++=-:::::-====+++++++++++++*****+\n"
    " +=======++++++++++++=+++++++============++++++=======+******\n"
    " +=====+++++++++++++++++++++++++==++++==++++++=:...  . .+****\n"
    "++====++++++++++++++++++++++++++++++++++++++++-.     ..-+****\n"
    "+======++++++++++++++++++++++++++++++++===+====:.    ..:=++++\n"
    "+===--=====+++++++++++++++++++++++++++=========-::....::-=++*\n"
    "====--==========+++++++==+++===++++===========--:::....:=++* \n"
    "====---===++++=====++++++==+++=======-::--===-:.  ....:-+++  \n"
    "==--=--====++++++++==+++++++++++======--::::...::::::-=+++   \n"
    "===----===++++++++++++++++++++============--=-==----==+++    \n"
    "=--------====++++++++++++++++=====================+++++++    \n"
    "=---------=======++++++++====+++=================++++++++    \n"
    "-----------========+++++++++++++++=================+++++++   \n"
    "=----------==========++++++++++=====================++++++++ \n"
    "=====------==============+++++++===================+++==+++++\n"
    "=======------==========================================++++++";
}

// Sets up the screen, and prepares the game.
// Sets ip color pairs and prepares the game for using user input.
// Displays pregame splash.
void init_menu(){
    srand(time(NULL));
    initscr();
    getmaxyx(stdscr,mr,mc);
    start_color();
    use_default_colors();
    init_pair(1,COLOR_YELLOW,-1);
    cbreak();
    keypad(stdscr,TRUE);
    curs_set(0);
    noecho();
    printdoge();
    attron(COLOR_PAIR(1));
    mvprintw(0,mc-28,"Press any key to continue...");
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    mvprintw(20,62,"________________");
    mvprintw(21,61,"/                \\");
    mvprintw(22,60,"<  ");
    attron(A_BOLD);
    printw("%-15s","wow such spell!");
    attroff(A_BOLD);
    printw(" |");
    mvprintw(23,61,"\\_________________/");
    refresh();
    attroff(COLOR_PAIR(1));
    getch();
    show_menu();
}

void show_help(){
    clear();
    mvprintdoge(0,0);
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(3,69,"how 2 play");
    attroff(A_BOLD);
    attron(COLOR_PAIR(1));
    mvprintw(5,60,"u get points for typing fast");
    mvprintw(6,60,"u lose points for typing wrong");
    mvprintw(0,mc-28,"Press any key to continue...");
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    refresh();
    getch();
    show_menu();
}

void show_about(){
    clear();
    mvprintdoge(0,0);
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(3,70,"about");
    attroff(A_BOLD);
    attron(COLOR_PAIR(1));
    mvprintw(5,64,"made by Joe Jevnik");
    mvprintw(6,64,"2013, this program is");
    mvprintw(7,64,"free software, see");
    mvprintw(8,64,"LICENSE for more info");
    mvprintw(0,mc-28,"Press any key to continue...");
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    refresh();
    getch();
    show_menu();
}

void show_menu(){
    clear();
    mvprintdoge(0,0);
    attron(COLOR_PAIR(1) | A_BOLD);
    mvprintw(3,65,"doge teaches typing");
    attroff(A_BOLD);
    mvprintw(mr-1,mc-13,"by Joe Jevnik");
    if (opt == 0){ attron(A_STANDOUT); }
    mvprintw(5,69,"time 2 play");
    if (opt == 0){ attroff(A_STANDOUT); }
    if (opt == 1){ attron(A_STANDOUT); }
    mvprintw(6,69,"how  2 play");
    if (opt == 1){ attroff(A_STANDOUT); }
    if (opt == 2){ attron(A_STANDOUT); }
    mvprintw(7,72,"about");
    if (opt == 2){ attroff(A_STANDOUT); }
    if (opt == 3){ attron(A_STANDOUT); }
    mvprintw(8,72,"exit");
    if (opt == 3){ attroff(A_STANDOUT); }
    refresh();
    switch(getch()){
    case KEY_UP:
	if (opt > 0){
	--opt;
	}
	break;
    case KEY_DOWN:
	if (opt < 3){
	    ++opt;
	}
	break;
    case 10: // ENTER
	switch(opt){
	case 0:
	    start_game();
	    return;
	    break;
	case 1:
	    show_help();
	    break;
	case 2:
	    show_about();
	    break;
	case 3:
	    endwin();
	    exit(0);
	    break;
	}
	break;
    }
    show_menu();
}

/*
void print_time(void *id){
    int r = 0,c = 0;
    long s;
    time_t t;
    struct tm*  t_;
    while (1){
	getyx(stdscr,r,c);
	time(&t);
	t_ = localtime(&t);
	mvprintw(8,69,"time:   %i",t_->tm_sec);
	move(r,c);
	nanosleep(10000);
    }
}
*/
