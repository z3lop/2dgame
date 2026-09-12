CC = gcc
CFLAGS = $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4)

main: main.c
	$(CC) $(CFLAGS) main.c -o main $(LIBS)

clean:
	rm -f hello_world
