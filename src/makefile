CC = gcc
CPPFLAGS += -g -Wall `sdl-config --cflags` -o $@

ALL : Invaders


clean :
	rm Invaders *.o

game.o : game.h game.c
	$(CC) $(CPPFLAGS) -c game.c -lSDL

Invaders : game.o
	$(CC) $(CPPFLAGS) game.o -lSDL
