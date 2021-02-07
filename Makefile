CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=`pkg-config --libs gtk+-3.0`
CFLAGS+= -DMY_USE_LIST
CFLAGS+=`pkg-config --cflags gtk+-3.0`

all: main

main: main.o main_UI.o gtk_functions.o
	$(CC) $^ $(LDFLAGS) -o $@

main_UI: main_UI.o gtk_functions.o
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $< $^


clean:
	rm -f %.o
	rm -f main
	rm -f main_UI