CC=gcc
CFLAGS=-std=c11 -Werror -Wall
LDLIBS=-lm
OUTPUT=ps1

all: bmp.o playfair.o main.c
	echo "Building main"
	$(CC) $(CFLAGS) bmp.o playfair.o main.c $(LDLIBS) -o $(OUTPUT)

bmp.o: bmp.c bmp.h
	echo "Building bmp.o ..."
	$(CC) $(CFLAGS) -c bmp.c

playfair.o: playfair.c playfair.h
	echo "Building playfair.o ..."
	$(CC) $(CFLAGS) -c playfair.c

clean:
	echo "cleaning ..."
	rm -rf $(OUTPUT) bmp.o playfair.o