#include <stdio.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>

#define MAXIX 80
#define MAXIY 35
#define SCRITTE 1

#define ENTER 13	//macro che contengono i valori ASCII dei comandi da tastiera
#define SU 65
#define GIU 66
#define PLAY 1
#define QUIT 5
#define STARTY 1	//Posizione delle scritte sullo schermo

typedef struct {	//Struttura per la scelta iniziale
	int x;
	int y;
	int scelto;
} PosC;

int mainScr();
void printScritta();
void printInvaders();
void printSquare();
void dPrintPlay();
void dPrintQuit();
void deletePlay();
void deleteQuit();
void Controllo(int*);
void* Scelta(void* arg);
