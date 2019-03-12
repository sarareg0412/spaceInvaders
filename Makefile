a.out:	main.o screen.o gameArea.o scritte.o
	cc main.o screen.o gameArea.o scritte.o -o main -lncurses -lpthread
main.o:	screen.h gameArea.h main.c
			cc -c main.c -lncurses -lpthread
screen.o:	screen.h screen.c
		cc -c screen.c -lncurses -lpthread
gameArea.o:	gameArea.h gameArea.c
		cc -c gameArea.c -lncurses -lpthread
scritte.o:	scritte.h scritte.c
		cc -c scritte.c -lncurses -lpthread
