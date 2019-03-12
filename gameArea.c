#include "gameArea.h"
#include "scritte.h"
/* Dichiarazione globale degli oggetti di gioco*/
Oggetto astronave;	
Oggetto spari[N];	
Oggetto nemici[M];
Oggetto bombe[M];
Oggetto nemici2[M];
Oggetto alleati[R];

Oggetto buffer[DIM_BUFFER];	//Dichiarazione del buffer di gioco
Oggetto letto;			//Variabile per prelevare un oggetto dal buffer
int gameover = 0; 
int inserito=0;			//Tengono il conto degli oggetti inseriti o prelevati
int prelevato=0;
int vivi=1;			//Indica se i nemici di primo o secondo livello sono vivi
int vivi2=0;
char key; 			//Variabile per l'input da tastiera

sem_t PRESENTI;			//Indica quante posizioni del buffer sono state scritte
sem_t DISPONIBILI;		//Indica quante posizioni del buffer sono ancora disponibili
pthread_mutex_t mutex;

/* Dichiarazione delle stringhe di caratteri dei vari oggetti di gioco */
char carAstronave[6][6] = {{' ',' ',' ',' ',' ',' '},{' ',' ','/','\\',' ',' '},{'/',']','[',']','[','\\'},{'[',']','=','=','[',']'},{'[',']','\\','/','[',']'},{':',':',' ',' ',':',':'}};
char carNemici[3][3]={{' ','=',' '},{'[','0',']'},{' ','V',' '}};
char carNemici2[3][3]={{'=',' ','='},{' ',' ',' '},{'v',' ','v'}};
char carEnem[3][3]={{' ','A',' '},{'=',' ','='},{' ','V',' '}};
char carAlleati[3][5]={{' ','/','^','\\',' '},{'<','=','=','=','>'},{' ','v',' ','v',' '}};
char carAlleato[3][5]={{' ','/','^','\\',' '},{'<',' ',' ',' ','>'},{' ','v',' ','v',' '}};
void game(){
	/* Inizializzamo le coppie dei colori che verranno utilizzati 
	   Il primo numero indica il numero della coppia; il secondo il colore
	   in foreground; il secondo in background */
	init_pair(SQUARE,COLOR_YELLOW,COLOR_BLACK);
	init_pair(NAVE, COLOR_GREEN, COLOR_BLACK);
	init_pair(NEMICI, COLOR_RED, COLOR_BLACK);
	init_pair(ALLEATI, COLOR_BLUE, COLOR_BLACK);
	init_pair(NEMICI2, COLOR_RED, COLOR_BLACK);
	init_pair(SPARI, COLOR_GREEN, COLOR_BLACK);
	init_pair(BOMBA, COLOR_YELLOW, COLOR_BLACK);
	init_pair(BOMBA2, COLOR_RED, COLOR_BLACK);
	init_pair(WINNER, COLOR_GREEN, COLOR_BLACK);
	init_pair(LOSER, COLOR_RED, COLOR_BLACK);
	
	//Accendiamo il colore
    attron(COLOR_PAIR(SQUARE));
	printSqr();	//Stampa del quadrato di gioco
	//Spegnamo il colore	
	attroff(COLOR_PAIR(SQUARE));

/* Inizializzazione dei thread degli oggetti del gioco */		
	pthread_t t_astronave, t_nemici, t_nemici2;
	pthread_t t_spari, t_bombe;
	pthread_t t_alleati;

/* Inizializzazione del mutex e dei semafori*/	
	pthread_mutex_init( &mutex, NULL);
	sem_init(&PRESENTI, 0, 0);
	sem_init(&DISPONIBILI, 0, DIM_BUFFER);
/* Creazione dei thread per i vari oggetti di gioco */

	if(pthread_create(&t_astronave, NULL, Astronave, NULL))  { //Creazione del thread Astronave 
		endwin();
		exit; 
	}
	if(pthread_create(&t_nemici, NULL, Nemici, NULL)){ //Creazione del thread Nemici
		endwin();
		exit;
    	}
	
	if(pthread_create(&t_spari, NULL, Spari, NULL)){ //Creazione del thread Spari
		endwin();
		exit;
    	}
	if(pthread_create(&t_bombe, NULL, Bombe, NULL))  { //Creazione del thread Bombe 
		endwin();
		exit; 
	}
	if(pthread_create(&t_nemici2, NULL, Nemici2, NULL))  { //Creazione del thread Nemici2
		endwin();
		exit; 
	}
	if(pthread_create(&t_alleati, NULL, Alleati, NULL))  { //Creazione del thread Alleati 
		endwin();
		exit; 
	}
	ControlloAll();		//Chiamata della funzione di controllo

	pthread_cancel(t_astronave); //Invio il segnale di cancellazione ai thread
	pthread_cancel(t_nemici);
	pthread_cancel(t_spari);
	pthread_cancel(t_bombe);	
	pthread_cancel(t_nemici2);
	pthread_cancel(t_alleati);

	pthread_join(t_astronave,0); //Attesa della terminazione dei thread 
	pthread_join(t_nemici,0);
	pthread_join(t_spari,0);
	pthread_join(t_bombe,0);	
	pthread_join(t_nemici2,0);
	pthread_join(t_alleati,0);

/* Distruzione del mutex e dei semafori */
	pthread_mutex_destroy (&mutex);
	sem_destroy(&PRESENTI);
	sem_destroy(&DISPONIBILI); 

	
}
void *Astronave (void *arg){

	int i,j;
	astronave.vivo=3;
/* Definizione della posizione iniziale dell'astronave */
	astronave.pos.x =(MAXX-6)/2;
	astronave.pos.y = MAXY-6;
/* Stampa della posizione attuale dell'astronave */	

	for(i=0;i<6;i++){
		for(j=0;j<6;j++){
			mvaddch(astronave.pos.y+i,astronave.pos.x+j,carAstronave[i][j]); 
		}
	}

	while(gameover==0 && astronave.vivo>0){
		key = getch();

	/* Viene salvata la posizione precedente dell'astronave */
		astronave.pos_vecchia.x=astronave.pos.x;
		astronave.pos_vecchia.y=astronave.pos.y;
	/* In base al tasto premuto viene modificata la posizione dell'astronave */	
		switch(key){
			case LEFT:	
		/* Se l'astronave non ha superato il quadrato di controllo e viene premuto
			   il tasto sinistro, si decrementa la sua posizione x */
				if(astronave.pos.x > 1)
					astronave.pos.x-=1;
				break;
			case RIGHT:
		/* Se l'astronave non ha superato il quadrato di controllo e viene premuto
			   il tasto destro, si incrementa la sua posizione x */
				if(astronave.pos.x < MAXX-6)
					astronave.pos.x+=1;
				break;
			default:
				break;
		}
	/* La nuova posizione dell'astronave viene scritta nel buffer */
		astronave.id_thread=NAVE;
		scritturaBuffer(astronave); 
	}

}
void* Spari(void* arg){
	int i,j=2;
	int controllo=1;

	while(!gameover){
	/* Inizializzazione delle posizioni degli spari */
		spari[0].vivo=1;
		spari[0].pos.x=astronave.pos.x+1;
		spari[0].pos.y=astronave.pos.y;
		spari[0].c='o';
		spari[0].d=(-1);	//Direzione a sinistra

		spari[1].vivo=1;
		spari[1].pos.x=astronave.pos.x+4;
		spari[1].pos.y=astronave.pos.y;
		spari[1].c='o';
		spari[1].d=(1);		//Direzione a destra
		if(key==SPACE){
			controllo=1;
			while(controllo==1){	//Entrambi gli spari sono vivi
			/* Salvataggio delle vecchie posizioni degli spari attivati */
				for(i=0;i<j;i++){
						spari[i].pos_vecchia.x=spari[i].pos.x;
						spari[i].pos_vecchia.y=spari[i].pos.y;

				}
			/* Movimento degli spari in vita fino ad ora */
				for(i=0;i<j;i++){
					if(spari[i].vivo!=0){
						spari[i].pos.x+=spari[i].d;
						spari[i].pos.y-=1;

					}
				}
			/* Se entrambi gli spari muoiono, si esce dal ciclo*/
				if(spari[0].vivo==0 && spari[1].vivo==0){
					controllo=0;
				}
			/* Scrittura degli spari nel buffer */
				for(i=0;i<2;i++){
					spari[i].id_sparo=i;
					spari[i].id_thread=SPARI;
					scritturaBuffer(spari[i]);
				}						
				usleep(80000);
			}
			key=0;	//Evita che vengano sparati missili se si rimane fermi
		}
	}


}
void* Nemici(void* arg){
	int i,j;	
	int y;	//y indica la posizione y della navicella nemica
	int flag=1;
/* I nemici si spostano comunque sempre in avanti; il controllo per le 
   collisioni viene effettuato nella funzione ControlloAll */

/* Settaggio delle vite dei nemici */
	for(i=0; i<M;i++){
		nemici[i].vivo=1;	
		nemici[i].morto=0;	//Indica se il nemico è stato colpito	
		nemici[i].d=1;		//All'inizio vanno tutti a destra
	}
/* Inizializzazione delle posizioni dei nemici */
	nemici[0].pos.x = 1;	
	nemici[0].pos.y = 1;
	y=nemici[0].pos.y;

	for(i=1; i<M; i++){
		nemici[i].pos.x=(nemici[i-1].pos.x)+6;	//Spazio tra i vari nemici
		if (nemici[i].pos.x>MAXX-3){	//Il nemico deve scendere perchè si è arrivati a MAXX 		
			nemici[i].pos.x=1;
			y=nemici[i-1].pos.y+3;	
			flag=flag*(-1);	
		}      
		if(flag<0){	 //Siamo in una fila pari, si inverte la direzione delle navicelle
			nemici[i].d=-1;
		}
		nemici[i].pos.y=y;
    	}

	while(gameover==0){	//I nemici di primo livello sono vivi
		while(vivi==1){
		/* Salvataggio posizioni vecchie dei nemici */
			for(i=0;i<M;i++){
				nemici[i].pos_vecchia.x=nemici[i].pos.x;
				nemici[i].pos_vecchia.y=nemici[i].pos.y;
			}

		/* Movimento dei nemici vivi */
			for (i=0;i<M;i++){
				if(nemici[i].vivo>0)
					nemici[i].pos.x+=nemici[i].d;

			/* Scrittura dei nemici nel buffer */
				nemici[i].id_thread=2;
				nemici[i].id_nemico=i;
				scritturaBuffer(nemici[i]); 
				
			}

			usleep(300000); 	//Ritardo nel movimento dei nemici
		}
    	}

}

void*Bombe(void* arg){
	int i=0,scelta;
	_Bool flag=true;
/* Inizializzazione delle bombe */
	for(i=0;i<M;i++){
		bombe[i].c='X';
		bombe[i].vivo=0;
	}

	while(gameover==0){
		for(i=0;i<=M;i++){
			if(i==M){
				i=0;			
			}
			if(vivi==1){
			/* Viene scelta una bomba in ordine, ma si va avanti se il nemico
					scelto è morto*/
				while(nemici[i].vivo<=0){
					i=(i+1)%M;
				}
			}else{
				while(nemici2[i].vivo<=0){
					i=(i+1)%M;
				}
			}
		/* Inizializzazione della bomba i-esima */
			bombe[i].vivo=1;
			if(vivi==1){
				bombe[i].pos.x=nemici[i].pos.x+1;
				bombe[i].pos.y=nemici[i].pos.y+3;
			}else{
				if(vivi2==1){
					bombe[i].c='@';
					bombe[i].pos.x=nemici2[i].pos.x+1;
					bombe[i].pos.y=nemici2[i].pos.y+3;
				}
			}
			while(bombe[i].vivo==1){
			/* Salvataggio della vecchia posizione della bomba */
				bombe[i].pos_vecchia.x=bombe[i].pos.x;
				bombe[i].pos_vecchia.y=bombe[i].pos.y;

			/* Movimento verticale della bomba */
				bombe[i].pos.y+=1;

			/* Scrittura della bomba i-esima nel buffer */
				bombe[i].id_thread=BOMBA;
				bombe[i].id_bomba=i;
				scritturaBuffer(bombe[i]);			
				usleep(100000);
				
			}
		}
	}
}
void* Alleati(void*arg){
	int vivi=1;
	int i;
/* Inizializzazione delle posizioni degli alleati */
	for(i=0; i<R;i++){
		alleati[i].vivo=2;	
		alleati[i].morto=0;	//Indica se l'i-esimo alleato è stata colpito per la seconda volta	
		alleati[i].d=(-1);		//All'inizio vanno tutti a sinistra
	}
/* Inizializzazione delle posizioni degli alleati */
	alleati[0].pos.x = 1;	
	alleati[0].pos.y = MAXY-10;

	for(i=1; i<R; i++){
		alleati[i].pos.x=(alleati[i-1].pos.x)+10;	//Spazio tra i vari alleati
		alleati[i].pos.y=alleati[i-1].pos.y;
    	}

	while(vivi>0 || gameover==0){	//Gli alleati sono vivi
			vivi=0;
	    		for(i=0;i<R;i++){
				if(alleati[i].vivo>0)
					vivi=1;
			}
			if(gameover==1){
				vivi=0;
			}
		/* Salvataggio posizioni vecchie degli alleati */
			for(i=0;i<R;i++){
				alleati[i].pos_vecchia.x=alleati[i].pos.x;
				alleati[i].pos_vecchia.y=alleati[i].pos.y;
			}

		/* Movimento degli alleati vivi */
			for (i=0;i<R;i++){
				if(alleati[i].vivo>0)
					alleati[i].pos.x+=alleati[i].d;

			/* Scrittura degli alleati nel buffer */
				alleati[i].id_thread=ALLEATI;
				alleati[i].id_alleato=i;
				scritturaBuffer(alleati[i]); 				
			}

			usleep(250000); 	//Ritardo nel movimento degli alleati
    	}
}
void* Nemici2(void* arg){
	int i,y;
	int prova=1;	
	/* I nemici di secondo livello vengono attivati quando vengono uccisi tutti i 
	   nemici di primo livello; essi partono da una posizione y più bassa*/

	while(!gameover){
		if(vivi==0){

			vivi2=1;

		/* Settaggio posizioni iniziali dei nemici2 */
		 	nemici2[0].pos.x =1; 
		        nemici2[0].pos.y =4;
		        nemici2[0].d =1;
			y=nemici2[0].pos.y;

		/* Settaggio degli attributi dei nemici */
		        for(i=0;i<M;i++){
		        	nemici2[i].vivo=2;
				nemici2[i].morto=0;
				nemici2[i].d=1;
		        }   

		 /* Inizializzazione delle posizioni dei nemici2 */
		        for(i=1;i<M;i++){
				nemici2[i].pos.x=(nemici2[i-1].pos.x)+10;
				if (nemici2[i].pos.x>MAXX-3){	//Il nemico deve scendere perchè si è arrivati a MAXX 		
					nemici2[i].pos.x=1;
					y=nemici2[i-1].pos.y+3;	
					prova=prova*(-1);
				}      
				if(prova<0){
					nemici2[i].d=(-1);
				}
				nemici2[i].pos.y=y;
		    	}

			while(!gameover){

				//Salvataggio delle posizioni vecchie dei nemici2
				for(i=0;i<M;i++){
					nemici2[i].pos_vecchia.x=nemici2[i].pos.x;
					nemici2[i].pos_vecchia.y=nemici2[i].pos.y;
				}

				//Movimento dei nemici2
				for (i=0;i<M;i++){
					if(nemici2[i].vivo>0){
						nemici2[i].pos.x+=nemici2[i].d;
			 		}
				/* Scrittura dei nemici2 nel buffer */
					nemici2[i].id_thread=NEMICI2;
					nemici2[i].id_nemico=i;
					scritturaBuffer(nemici2[i]); 
				}

				usleep(250000); 			   
			}
		}
	}
}
void ControlloAll(){
	int i, j, k;
/* Il ciclo termina quando la navicella perde tutte le vite, oppure questa elimina tutti gli avversari */

	while(gameover==0){ 
	/* Lettura di un elemento dal buffer e blocco del mutex    
	   per evitare che altre funzioni scrivano in esso */
		letturaBuffer();	
		pthread_mutex_lock(&mutex);	

	/* In base all'ID_THREAD del valore letto dal buffer si  
	   identifica l'oggetto e si svolgono i vari controlli */
		switch(letto.id_thread){
			case NAVE:
				attron(COLOR_PAIR(NAVE));
		/* Cancellazione della vecchia posizione dell'astronave e del conteggio delle vite */
				for(i=0;i<6;i++){
					for(j=0;j<6;j++){
					     mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
					}
				}
				mvprintw(MAXY+1,0,"  						                      "); 		
		/* Stampa della nuova posizione dell'astronave e del numero delle vite*/
    				for(i=0;i<6;i++){
					for(j=0;j<6;j++){
	    					mvaddch(letto.pos.y+i,letto.pos.x+j,carAstronave[i][j]); 
					}
    				}
				if(letto.vivo >= 0){
					mvprintw(MAXY+1,(MAXX/2)-5,"Vite:%d", letto.vivo);
					refresh();
				}
				attroff(COLOR_PAIR(NAVE));
				break;	
			case NEMICI:	
				attron(COLOR_PAIR(NEMICI));			
			/*Controllo se i nemici sono morti*/
				vivi=0;
				for(i=0;i<M;i++){
					if(nemici[i].vivo>0)
						vivi=1;
				}			
			/* Cancellazione delle vecchie posizioni dei nemici*/
				if(nemici[letto.id_nemico].vivo>0){	//Se il nemico è ancora vivo, viene cancellata la sua vecchia posizione
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
						}
					}
				} else { //Se il nemico è morto verrà cancellato solo una volta
					if(nemici[letto.id_nemico].morto==0){
					    	for(i=0;i<3;i++){
							for(j=0;j<3;j++){
								mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
mvaddch(letto.pos.y+i,letto.pos.x+j,' '); 
							}
						}
						nemici[letto.id_nemico].morto=1;
					}
				}												
	
			/* Controllo collisione tra il nemico e le pareti*/
				
				if(letto.pos.x>MAXX-4 || letto.pos.x<1){ 
					nemici[letto.id_nemico].pos.x-=letto.d;
           				nemici[letto.id_nemico].pos.y+=3;
           				nemici[letto.id_nemico].d=letto.d*(-1);	//Cambio direzione
        			}

				//Se il nemico arriva all'astronave, il gioco finisce
				if(nemici[letto.id_nemico].pos.y==MAXY-6 || nemici[letto.id_nemico].pos.y+1==MAXY-6 || nemici[letto.id_nemico].pos.y+2==MAXY -6){
					gameover=1;
				}
			/* Stampa dei nemici ancora in vita */
				if(nemici[letto.id_nemico].vivo!=0){
				    for(i=0;i<3;i++){
					for(j=0;j<3;j++){
			mvaddch(nemici[letto.id_nemico].pos.y+i,nemici[letto.id_nemico].pos.x+j,carNemici[i][j]); 
					}
				    }	
				}	
				attroff(COLOR_PAIR(NEMICI));
				break;
			case SPARI:
				attron(COLOR_PAIR(SPARI));
			/* Cancellazione della vecchia posizione dello sparo */
				mvaddch(letto.pos_vecchia.y, letto.pos_vecchia.x,' '); 

			/* Se il proiettile è in vita e si scontra con una navicella nemica 
			   ancora in vita, questo diventa un carattere bianco, e il valore 
			   della vita della navicella nemica viene decrementato */
				if(vivi==1){
					for(i=0;i<M;i++){
							if((letto.pos.y==nemici[i].pos.y || letto.pos.y==nemici[i].pos.y+1 || letto.pos.y==nemici[i].pos.y+2)&&(letto.pos.x==nemici[i].pos.x+1 || letto.pos.x==nemici[i].pos.x+2) && letto.vivo==1 && nemici[i].vivo>0){
								nemici[i].vivo--;
								spari[letto.id_sparo].c = ' ';
								spari[letto.id_sparo].vivo=0;
							}
					}
				}else{

					for(i=0;i<M;i++){
						if((letto.pos.y==nemici2[i].pos.y || letto.pos.y==letto.pos.y+1 || letto.pos.y==nemici2[i].pos.y+2)&&(letto.pos.x==nemici2[i].pos.x ||letto.pos.x==nemici2[i].pos.x+1 || letto.pos.x==nemici2[i].pos.x+2) && letto.vivo==1 && nemici2[i].vivo>0){
							nemici2[i].vivo--;
							spari[letto.id_sparo].c = ' ';
							spari[letto.id_sparo].vivo=0;
						}
				}


				}
			/* Controllo collisioni con le pareti */
				if(letto.pos.x>MAXX-2 || letto.pos.x<2){ 
					spari[letto.id_sparo].d=letto.d*(-1);	//Inversione direzione

        			}
			/* Controllo collisione con il tetto */
				if(letto.pos.y<1){
						spari[letto.id_sparo].vivo=0;
						spari[letto.id_sparo].c = ' ';
						spari[letto.id_sparo].pos.y+=1;
				}	
			/* Controllo collisione con una bomba, vengono eliminati entrambi */
				for(i=0; i<M;i++){
					if((letto.pos.x==bombe[i].pos.x)&&(letto.pos.y==bombe[i].pos.y)&& letto.vivo==1 && bombe[i].vivo>0){
						bombe[i].vivo=0;
						spari[letto.id_sparo].c = ' ';
						spari[letto.id_sparo].vivo=0;	
					} 
				}	
			/* Stampa della nuova posizione */
				if(spari[letto.id_sparo].vivo!=0){
					mvaddch(spari[letto.id_sparo].pos.y,spari[letto.id_sparo].pos.x,spari[letto.id_sparo].c);
				}
				attroff(COLOR_PAIR(SPARI));
				break;
			case BOMBA:
				attron(COLOR_PAIR(BOMBA));
			/* Cancellazione delle bombe*/
				mvaddch(letto.pos_vecchia.y,letto.pos_vecchia.x,' ');

			/* Controllo collisione con l'astronave */
				if((letto.pos.y==astronave.pos.y || letto.pos.y==astronave.pos.y+1 ||  letto.pos.y==astronave.pos.y+2 ||  letto.pos.y==astronave.pos.y+3 || letto.pos.y==astronave.pos.y+4 || letto.pos.y==astronave.pos.y+5) && (letto.pos.x==astronave.pos.x || letto.pos.x==astronave.pos.x+1 || letto.pos.x==astronave.pos.x+2 || letto.pos.x==astronave.pos.x+3 || letto.pos.x==astronave.pos.x+4 || letto.pos.x==astronave.pos.x+5)) {
					bombe[letto.id_bomba].vivo=0;
					astronave.vivo-=1;
					if(astronave.vivo==0){	//Se l'astronave non ha più vite, il gioco finisce
						gameover=1;
					}
				}
			/* Controllo collisione con il pavimento */
				if(letto.pos.y>MAXY-1){
					bombe[letto.id_bomba].vivo=0;
				}
			/* Controllo collisione con una roccia */
				for(i=0;i<R;i++){
						if((letto.pos.x==alleati[i].pos.x || letto.pos.x==alleati[i].pos.x+1 || letto.pos.x==alleati[i].pos.x+2 || letto.pos.x==alleati[i].pos.x+3 || letto.pos.x==alleati[i].pos.x+4) && (letto.pos.y==alleati[i].pos.y || letto.pos.y==alleati[i].pos.y+1 || letto.pos.y==alleati[i].pos.y+2) && letto.vivo==1 && alleati[i].vivo>0){
							alleati[i].vivo--;
							bombe[letto.id_bomba].vivo=0;
						}
				}
			/* Stampa delle bombe ancora in vita */
				if(bombe[letto.id_bomba].vivo==1)
					mvaddch(bombe[letto.id_bomba].pos.y,bombe[letto.id_bomba].pos.x,bombe[letto.id_bomba].c);
				attroff(COLOR_PAIR(BOMBA));
				break;
			
			case ALLEATI:
				attron(COLOR_PAIR(ALLEATI));
		/* Cancellazione delle vecchie posizioni degli alleati*/
				if(alleati[letto.id_alleato].vivo>0){	
					for(i=0;i<3;i++){
						for(j=0;j<5;j++){
							mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
						}
					}
				} else { //Se l'alleato è morto verrà cancellato solo una volta
					if(alleati[letto.id_alleato].morto==0){
					    	for(i=0;i<3;i++){
							for(j=0;j<5;j++){
								mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
mvaddch(letto.pos.y+i,letto.pos.x+j,' '); 
							}
						}
						alleati[letto.id_alleato].morto=1;
					}
				}												
	
			/* Controllo collisione tra gli alleati e le pareti*/
				
				if(letto.pos.x>MAXX-5 || letto.pos.x<1){ 
					alleati[letto.id_alleato].pos.x-=letto.d;
           				alleati[letto.id_alleato].d=letto.d*(-1);	//Cambio direzione
        			}	
			/* Collisione tra due alleati */
				for(i=0;i<R; i++){
					if(alleati[letto.id_alleato].vivo>0 && alleati[i].vivo>0){
					//Scontro a destra
						if(alleati[letto.id_alleato].pos.x+5==alleati[i].pos.x){
							alleati[letto.id_alleato].pos.x-=letto.d;
							alleati[letto.id_alleato].d=letto.d*(-1);
							alleati[i].pos.x-=alleati[i].d;
							alleati[i].d=alleati[i].d*(-1);
						}
					//Scontro a sinistra
						if(alleati[letto.id_alleato].pos.x-5==alleati[i].pos.x){
							alleati[letto.id_alleato].pos.x-=letto.d;
							alleati[letto.id_alleato].d=letto.d*(-1);
							alleati[i].pos.x-=alleati[i].d;
							alleati[i].d=alleati[i].d*(-1);
						}
					}
				}

			/* Stampa l'alleato ancora in vita */
				if(alleati[letto.id_alleato].vivo!=0){
				    for(i=0;i<3;i++){
					for(j=0;j<5;j++){
						if(letto.vivo==2)	mvaddch(alleati[letto.id_alleato].pos.y+i,alleati[letto.id_alleato].pos.x+j,carAlleati[i][j]); 
						if(letto.vivo==1)
mvaddch(alleati[letto.id_alleato].pos.y+i,alleati[letto.id_alleato].pos.x+j,carAlleato[i][j]); 
					}
				    }	
				}	
				attroff(COLOR_PAIR(ALLEATI));
				break;
			case NEMICI2:
				attron(COLOR_PAIR(NEMICI2));
				//Controllo se i nemici2 sono morti
				vivi2=0;
				for(i=0;i<M;i++){
					if(nemici2[i].vivo>=1)
						vivi2=1;
				}
				if(vivi2==0){
					gameover=2;
				}
					
				//Cancellazione dei nemici2				
				if(nemici2[letto.id_nemico].vivo>0){
					for(i=0;i<3;i++){
						for(j=0;j<3;j++){
							mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
						}
					}
				} else { //Se il nemico è morto allora dovrò cancellarlo una volta soltanto
					if(nemici2[letto.id_nemico].morto==0){
					    	for(i=0;i<3;i++){
							for(j=0;j<3;j++){
								mvaddch(letto.pos_vecchia.y+i,letto.pos_vecchia.x+j,' '); 
mvaddch(letto.pos.y+i,letto.pos.x+j,' '); 
							}
						}
						nemici2[letto.id_nemico].morto=1;
					}
				}												
	
				//Collisione tra i nemici2 e le pareti
				
				if(letto.pos.x>MAXX-4 || letto.pos.x<1){ 
					nemici2[letto.id_nemico].pos.x-=letto.d;
           				nemici2[letto.id_nemico].pos.y+=3;
           				nemici2[letto.id_nemico].d=letto.d*(-1);
        			}
				if(nemici2[letto.id_nemico].pos.y==MAXY-6 || nemici2[letto.id_nemico].pos.y+1==MAXY-6 || nemici2[letto.id_nemico].pos.y+2==MAXY -6){
					gameover=1;
				}
				//Stampa dei nemici2
				for(i=0;i<3;i++){
					for(j=0;j<3;j++){
						if(letto.vivo>0){
							if(letto.vivo==2)
				mvaddch(nemici2[letto.id_nemico].pos.y+i,nemici2[letto.id_nemico].pos.x+j,carNemici2[i][j]); 
							if(letto.vivo==1)
mvaddch(nemici2[letto.id_nemico].pos.y+i,nemici2[letto.id_nemico].pos.x+j,carEnem[i][j]);
						}
					    		
					}
				}
				attroff(COLOR_PAIR(NEMICI2));
				break;					
		}	
		if (gameover==1){
			clear();
			attron(COLOR_PAIR(SQUARE));
			printSqr();
			attroff(COLOR_PAIR(SQUARE));

			attron(COLOR_PAIR(LOSER));
			printGameover();
			attroff(COLOR_PAIR(LOSER));
		}else{
			if(gameover==2){
				clear();
				attron(COLOR_PAIR(SQUARE));
				printSqr();
				attroff(COLOR_PAIR(SQUARE));

				attron(COLOR_PAIR(WINNER));
				printWin();
				attroff(COLOR_PAIR(WINNER));
			}
		}
		refresh();
	/* Il ciclo del controllo è terminato,il mutex viene sbloccato */
		
		pthread_mutex_unlock(&mutex);		
	}
	
}

void scritturaBuffer(Oggetto obj) {
/* Decremento il valore delle locazioni disponibili, incremento quello delle locazioni presenti*/
	sem_wait( &DISPONIBILI);
	pthread_mutex_lock( &mutex);
/* Inserisco nel buffer l'elemento passatogli come parametro */
	buffer[inserito] = obj;
	inserito = (inserito + 1) % DIM_BUFFER;

	pthread_mutex_unlock(&mutex);
	sem_post( &PRESENTI);
}

void letturaBuffer() {
/* Decremento il valore delle locazioni presenti, incremento quello delle locazioni disponibili*/
	sem_wait( &PRESENTI);
	pthread_mutex_lock( &mutex);
/* Prelevo l'elemento i-esimo dal buffer */
	letto = buffer[prelevato];
	prelevato = (prelevato + 1) % DIM_BUFFER;

	pthread_mutex_unlock( &mutex);
	sem_post( &DISPONIBILI);
}

