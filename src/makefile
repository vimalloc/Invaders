CC = gcc
CPPFLAGS += -g -Wall `sdl-config --cflags` -o $@

ALL : Invaders


clean :
	rm Invaders *.o

game.o : game.h game.c
	$(CC) $(CPPFLAGS) -c game.c -lSDL

errors.o : errors.h errors.c
	$(CC) $(CPPFLAGS) -c errors.c

ship.o : ship.h ship.c
	$(CC) $(CPPFLAGS) -c ship.c

Invaders : game.o errors.o ship.o
	$(CC) $(CPPFLAGS) game.o errors.o ship.o -lSDL
