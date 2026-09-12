CC = gcc
CFLAGS = $(shell pkg-config --cflags sdl2)
LIBS = $(shell pkg-config --libs sdl2)

main: main.c
	$(CC) $(CFLAGS) main.c game.c player.c -o jump-run $(LIBS)

clean:
	rm -f jump-run
