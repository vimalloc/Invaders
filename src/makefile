CC = gcc
CPPFLAGS += -g -Wall `sdl-config --cflags` -o $@

ALL : Invaders


clean :
	rm Invaders *.o

game.o : game.h game.c
	$(CC) $(CPPFLAGS) -c game.c -lSDL

errors.o : errors.h errors.c
	$(CC) $(CPPFLAGS) -c errors.c

Invaders : game.o errors.o
	$(CC) $(CPPFLAGS) game.o errors.o -lSDL
