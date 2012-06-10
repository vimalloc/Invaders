CC          = gcc
CPPFLAGS   += -g -Wall -o $@
SDL_CFLAGS  = `sdl-config --cflags`
SDL_LIBS    = `sdl-config --libs`

ALL : Invaders

clean :
	rm Invaders *.o

errors.o : errors.h errors.c
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c errors.c

linked_list.o : linked_list.h linked_list.c errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c linked_list.c

sprite.o : sprite.h sprite.c errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c sprite.c

bullet.o : bullet.h bullet.c sprite.o errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c bullet.c

gun.o : gun.h gun.c errors.o sprite.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c gun.c

ship.o : ship.h ship.c sprite.o errors.o gun.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c ship.c

alien.o : alien.h alien.c sprite.o gun.o errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c alien.c

level.o : level.h level.c alien.o linked_list.o errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c level.c

game_state.o : game_state.h game_state.c ship.o errors.o bullet.o linked_list.o alien.o level.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c game_state.c

game.o : game.h game.c game_state.o errors.o
	$(CC) $(CPPFLAGS) $(SDL_CFLAGS) -c game.c

Invaders : game.o
	$(CC) $(CPPFLAGS) errors.o linked_list.o sprite.o bullet.o gun.o ship.o game_state.o game.o alien.o level.o $(SDL_LIBS)
