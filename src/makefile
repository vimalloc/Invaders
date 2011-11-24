CC = gcc
CPPFLAGS += -g -Wall `sdl-config --cflags --libs` -o $@

ALL : Invaders

clean :
	rm Invaders *.o

errors.o : errors.h errors.c
	$(CC) $(CPPFLAGS) -c errors.c

sprite.o : sprite.h sprite.c errors.o
	$(CC) $(CPPFLAGS) -c sprite.c

gun.o : gun.h gun.c errors.o
	$(CC) $(CPPFLAGS) -c gun.c

ship.o : ship.h ship.c sprite.o errors.o gun.o
	$(CC) $(CPPFLAGS) -c ship.c

game_state.o : game_state.h game_state.c ship.o errors.o
	$(CC) $(CPPFLAGS) -c game_state.c

game.o : game.h game.c game_state.o errors.o
	$(CC) $(CPPFLAGS) -c game.c

Invaders : game.o
	$(CC) $(CPPFLAGS) gun.o ship.o sprite.o game.o errors.o game_state.o -lSDL
