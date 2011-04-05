CC = gcc
CPPFLAGS += -g -Wall `sdl-config --cflags` -o $@

ALL : Invaders

clean :
	rm Invaders *.o

game.o : game.h game.c
	$(CC) $(CPPFLAGS) -c game.c

errors.o : errors.h errors.c
	$(CC) $(CPPFLAGS) -c errors.c

game_state.o : game_state.h game_state.c
	$(CC) $(CPPFLAGS) -c game_state.c

Invaders : game.o errors.o game_state.o ship.h
	$(CC) $(CPPFLAGS) game.o errors.o game_state.o -lSDL
