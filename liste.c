#include "scritte.h"
void printGameover(){
	mvprintw(10,10,"***********************************");
	mvprintw(11,10,"************** GAME ***************");
	mvprintw(12,10,"************** OVER ***************");	
	mvprintw(13,10,"***********************************");
}

void printWin(){
	mvprintw(10,10,"***********************************");
	mvprintw(11,10,"******** CONGRATULATIONS **********");
	mvprintw(12,10,"************ YOU WON **************");
	mvprintw(13,10,"***********************************");

}
void printSqr(){
	int y=0,x;
	for(x=0;x<MAXX; x++){
		mvaddch(y,x,'*');  
		refresh(); 
	}
	for(y=0;y<MAXY;++y){
		mvaddch(y,x,'*');   
		refresh();
	}
	for(x; x>=1; --x){
		mvaddch(y,x,'*');   
		refresh();
	}
	for(y; y>=1;--y){
		mvaddch(y,x,'*');   
		refresh();
	}

}
