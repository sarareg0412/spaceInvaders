#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

#define LEFT 68  	//Definizione delle macro per i tasti in input 
#define RIGHT 67 
#define SPACE 32 

#define M 15		//Macro che identifica il numero di nemici
#define N 2			//Identifica il numero di spari
#define R 8

#define NAVE 	1	//Definizione delle macro per gli ID_THREAD dei vari oggetti di gioco e per i colori
#define NEMICI 	2
#define SPARI 	3
#define BOMBA 	4
#define BOMBA2  5
#define NEMICI2 6
#define ALLEATI	7
#define SQUARE  8
#define WINNER  9
#define LOSER   10

#define DIM_BUFFER 1000	//Definizione grandezza buffer

struct pos{	//Struttura per la posizione attuale e precedente dell'oggetto
int  x;
int  y;
};

typedef struct Oggetto {
	struct pos pos;		//Posizioni dell'oggetto
	struct pos pos_vecchia;
	int id_thread;		//Identificativo del thread di provenienza
	int id_nemico;		//Identificativo del nemico i-esimo
	int id_sparo;
	int id_bomba;
	int id_alleato;
	int vivo;		//Intero per determinare se l'oggetto non è stato distrutto
	int morto;
	int d;			//Indica la direzione
	char c;
}Oggetto;

/* Dichiarazioni delle funzioni utilizzate */
void printSqr();
void game();

void* Astronave	(void *arg);
void* Spari	(void* arg);
void* Nemici	(void* arg);
void* Nemici2 	(void* arg);
void* Bombe	(void* arg);
void* Alleati 	(void* arg);
void ControlloAll();

void scritturaBuffer(Oggetto obj);
void letturaBuffer() ;
void printGameover();
void printWin();
