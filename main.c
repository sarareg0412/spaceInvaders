#include "screen.h"
#include "gameArea.h"
#include <time.h>
#include <curses.h>

int main(){
	int nexti, ret;
	int x=100,y=100;
	int t=2000000;

	srand(time(NULL));
	initscr();
	curs_set(0);		//nasconde il cursore
	noecho();		//evita che i caratteri inseriti da tastiera siano visualizzati nel terminale 
	if (has_colors()){
		start_color();
	} 
	assume_default_colors(COLOR_YELLOW,COLOR_BLACK);
	nexti=mainScr();			
	switch (nexti){
		case PLAY:
			game();
			break;
		case QUIT:
			break;
	}
	
	endwin();
	return 0;
}
