#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXX 80		//Definizione grandezza schermo
#define MAXY 35 
	
void printGameover();
void printWin();
void printSqr();
