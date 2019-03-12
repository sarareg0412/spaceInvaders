#include "screen.h"
#include "scritte.h"
pthread_mutex_t mtx;	//mutex per la gestione dei thread
int x, y;
int t=25000; 		//Variabile per il tempo delle scritte iniziali
PosC cursore;

int mainScr(){
	int scelta=0;
	pthread_t tscelta;	//Thread scelta

	//curs_set(0);		//nasconde il cursore
	//noecho();		//evita che i caratteri inseriti da tastiera siano visualizzati nel terminale 
	/* Inizializzo mutex */
	pthread_mutex_init(&mtx, NULL);
	
	printSqr();	//Stampa del quadrato di gioco
	
	init_pair(SCRITTE,COLOR_YELLOW,COLOR_RED);
	attron(COLOR_PAIR(SCRITTE));
	printScritta();	//Stampa SPACE INVADERS
	dPrintPlay();	//Funzione che stampa la scritta play o quit
	dPrintQuit();
    	attroff(COLOR_PAIR(SCRITTE));
	//Creo il thread Scelta
	if(pthread_create(&tscelta, NULL, Scelta, NULL)) {
		endwin();
		exit; 
	}
	/* Attendo la terminazione del thread */
	pthread_join (tscelta, NULL);
	//Chiamo la funzione controllo
	Controllo(&scelta);
	/* Elimino mutex */
	pthread_mutex_destroy (&mtx);

	clear();		//Pulisco lo schermo
	return scelta;
}
void *Scelta(void *arg){
	int deltay;	/* Spostamento verticale */
	char d;
	cursore.x=60;		//Posizione iniziale del cursore
	cursore.y=STARTY+16;
	cursore.scelto=0;
	/* Blocco mutex, disegno carattere, aggiorno schermo e sblocco mutex */
	pthread_mutex_lock(&mtx);
	mvaddch(cursore.y,cursore.x,'o');
	refresh();
	pthread_mutex_unlock(&mtx);
	
	//Il ciclo termina quando viene scelta un'opzione 
	while (cursore.scelto!=1){

		/* Blocco mutex, cancello carattere e sblocco mutex */
		pthread_mutex_lock(&mtx);
		mvaddch(cursore.y,cursore.x,' ');
		pthread_mutex_unlock(&mtx);

		d=getchar();	//Acquisizione carattere da tastiera
		switch (d){	//switch sul carattere
			case SU:
				if (cursore.y>=STARTY+21)
					cursore.y-=6;
				break;
			case GIU:
				if (cursore.y<=STARTY+16)
					cursore.y+=6;
				break;
			case ENTER:
				cursore.scelto=1;
				break;
		}
		/* Blocco mutex, disegno carattere, aggiorno schermo e sblocco mutex */
		pthread_mutex_lock(&mtx);
		mvaddch(cursore.y,cursore.x,'o');
		refresh();
		pthread_mutex_unlock(&mtx);
	}


}
void Controllo(int* scelta){
	if(cursore.scelto==1){
		if(cursore.y==STARTY+16)
			 *scelta=1;
		else
			 *scelta=5;
	}
}
void printScritta(){
int x,y=STARTY+4;
int s=3;
	//     		xxx  xxx  xx   xxx xxx
	//     		x    x x x  x x    x
	//     		xxx  xxx xxxx x    xx
	//       	  x x   x  x x    x
	//     		xxx  x   x  x  xxx xxx 
	//
	//	x x  x x  x  xx  xxx  xxx xxx  xxx
	//	x xx x x  x x  x x  x x   x  x x
	//	x x xx x  x xxxx x  x xx  xxx  xxx
	//	x x  x x  x x  x x  x x   x x     x
	//	x x  x  xx  x  x xxx  xxx x  x xxx
	
	//prima riga
	for(x=6-s;x<11-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=12-s;
	for(x;x<17-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=19-s;
	for(x;x<22-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=25-s;
	for(x;x<28-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=30-s;
	for(x;x<35-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	//Seconda riga
	y++;
	x=30-s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=28-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=24-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=22-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=18-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=16-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=12-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=6-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	//Terza riga
	y++;
	for(x=6-s;x<11-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=12-s;
	for(x;x<17-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=18-s;
	for(x;x<23-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=24-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=30-s;
	for(x;x<34-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	//Quarta riga
	y++;
	x=30-s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=28-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=24-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=22-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=18-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=12-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=10-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	//Quinta riga
	y++;
	for(x=6-s;x<11-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=12-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=18-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=22-s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=25-s;
	for(x;x<28-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=30-s;
	for(x;x<35-s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	printInvaders();
}
void printInvaders(){
int x;y=STARTY+4;
int s=5;
	//Prima riga
	x=30+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=32+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=36+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=38+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=42+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=45+s;
	for(x;x<48+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	x=50+s;
	for(x;x<54+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=56+s;
	for(x;x<61+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=62+s;
	for(x;x<67+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=68+s;
	for(x;x<73+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	//Seconda riga
	++y;
	x=68+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=66+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=62+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=56+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=54+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=50+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=48+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=44+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=42+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=38+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=36+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=33+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=32+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=30+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	//Terza riga
	++y;
	x=30+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=32+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=34+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=36+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=38+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=42+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=44+s;
	for(x;x<49+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	x=50+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=54+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=56+s;
	for(x;x<60+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=62+s;
	for(x;x<67+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	x=68+s;
	for(x;x<73+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	//Quarta riga
	++y;
	x=72+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=65+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=62+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=56+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=54+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=50+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=48+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=44+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=41+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=39+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=36+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=35+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=32+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=30+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	//Quinta riga
	++y;
	x=30+s;
	mvaddch(y,x,'x');   
	refresh();		
	usleep(t);
	x=32+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=36+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=40+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	
	x=44+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);

	x=48+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);	
	
	x=50+s;
	for(x;x<54+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	x=56+s;
	for(x;x<61+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	x=62+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=66+s;
	mvaddch(y,x,'x');   
	refresh();
	usleep(t);
	x=68+s;
	for(x;x<73+s;x++){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}
	
}
void dPrintPlay(){
	int y=STARTY+14;
	int s=1;
	//***** *     ***** *   *
	//***** *     *****   *
	//*     ***** *   *   *
	
	/*Nel movimento della visualizzazione la scritta si muove prima da sinistra a destra,
	  poi nella seconda riga da destra verso sinistra, e nella terza di nuovo da sinistra a 
	  destra*/
	/*FIRST LINE*/
	for (x=26+s; x<31+s; ++x){
		mvaddch(y,x,'x');   
		refresh();
		usleep(t);
	}

	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	x=39+s;

	for (; x<42+s; ++x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

	x=44+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(300000);
	x=48+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	/*SECOND LINE*/
	++y;
	x=47+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=45+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=42+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=38+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=30+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=26+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	/*THIRD LINE*/
	y++;
	x=26+s;
	for (; x<31+s; ++x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=38+s;
	for (; x<43+s; ++x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}
	x=46+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	/*FOURTH LINE*/
	++y;
	x=46+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=42+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=38+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=26+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	/*FIFTH LINE*/
	++y;
	x=26+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=32+s;
	for (; x<37+s; ++x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

	x=38+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=42+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=46+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);


}

void dPrintQuit(){
	int y=STARTY+20;
	int s=1;
	//*****   *   * * *****
	//* * *   *   * *   *
	//******* ***** *   *

	/*FIRST LINE*/
	for (x=48+s; x>43+s; --x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}
	x=40+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=36+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=29+s;
	for (; x>26+s; --x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

	/*SECOND LINE*/
	x=26+s;
	++y;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=30+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	x+=2;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x+=4;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x+=4;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x+=6;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	/*THIRD LINE*/
	x=46+s;
	++y;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x-=6;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x-=4;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=32+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=30+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=26+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	/*FOURTH LINE*/
	x=26+s;
	++y;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=29+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x=30+s;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	x+=2;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x+=4;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x+=4;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x+=6;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	/*FIFTH LINE*/
	x=46+s;
	++y;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);

	x-=6;
	mvaddch(y,x,'x');
	refresh();
	usleep(t);
	
	x=35+s;
	for (; x>32+s; --x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

	x=30+s;
	for (; x>26+s; --x){
		mvaddch(y,x,'x');
		refresh();
		usleep(t);
	}

}
