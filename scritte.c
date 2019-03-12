#include "scritte.h"
void printGameover(){
	int x=12;
	int k=0;

    /*  XXXXX  XXX  X   X XXXXX 
	X     X   X X X X X
	X XXX XXXXX X   X XXXX
	X   X X   X X   X X
	XXXXX X   X X   X XXXXX

	XXXXX X   X XXXXX XXXX
	X   X X   X X     X   X
	X   X X   X XXXX  XXXX
	X   X  X X  X     X  X
	XXXXX   X   XXXXX X   X
	*/

	while (k<3) {
		mvprintw(13, x, "XXXXX  XXX  X   X XXXXX");
		mvprintw(14, x, "X     X   X X X X X");
		mvprintw(15, x, "X XXX XXXXX X   X XXXX");
		mvprintw(16, x, "X   X X   X X   X X");
		mvprintw(17, x, "XXXXX X   X X   X XXXXX");

		mvprintw(13, x+30, "XXXXX X   X XXXXX XXXX");
		mvprintw(14, x+30, "X   X X   X X     X   X");
		mvprintw(15, x+30, "X   X X   X XXXX  XXXX");
		mvprintw(16, x+30, "X   X  X X  X     X  X");
		mvprintw(17, x+30, "XXXXX   X   XXXXX X   X");
		refresh();

		usleep(1000000);

		mvprintw(13, x, "                       ");
		mvprintw(14, x, "                   ");
		mvprintw(15, x, "                      ");
		mvprintw(16, x, "                   ");
		mvprintw(17, x, "                       ");

		mvprintw(13, x+30, "                      ");
		mvprintw(14, x+30, "                       ");
		mvprintw(15, x+30, "                      ");
		mvprintw(16, x+30, "                      ");
		mvprintw(17, x+30, "                       ");
		refresh();

		usleep(800000);

		++k;
	};
	
}

void printWin(){
	int x=15;
	int k=0;

	/*      X   X XXXXX X   X
		 X X  X   X X   X
		  X   X   X X   X
		  X   X   X X   X
		  X   XXXXX XXXXX

		X   X XXXXX X   X
		X   X X   X XX  X
		X   X X   X X X X
		X X X X   X X  XX
		X   X XXXXX X   X
	*/

	while (k<3) {
		mvprintw(13, x, "X   X XXXXX X   X");
		mvprintw(14, x, " X X  X   X X   X");
		mvprintw(15, x, "  X   X   X X   X");
		mvprintw(16, x, "  X   X   X X   X");
		mvprintw(17, x, "  X   XXXXX XXXXX");

		mvprintw(13, x+23, "X   X XXXXX X   X");
		mvprintw(14, x+23, "X   X X   X XX  X");
		mvprintw(15, x+23, "X   X X   X X X X");
		mvprintw(16, x+23, "X X X X   X X  XX");
		mvprintw(17, x+23, "X   X XXXXX X   X");
		refresh();

		usleep(1000000);

		mvprintw(13, x, "                 ");
		mvprintw(14, x, "                 ");
		mvprintw(15, x, "                 ");
		mvprintw(16, x, "                 ");
		mvprintw(17, x, "                 ");

		mvprintw(13, x+23, "                 ");
		mvprintw(14, x+23, "                 ");
		mvprintw(15, x+23, "                 ");
		mvprintw(16, x+23, "                 ");
		mvprintw(17, x+23, "                 ");
		refresh();

		usleep(800000);

		++k;
	};


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
