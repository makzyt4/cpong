CC=gcc
CFLAGS=-Wall -Werror
TARGET=bin/cpong
SOURCES=$(wildcard src/*.c)
LDFLAGS=-lSDL2

default: all

all:
	$(CC) $(LDFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm $(TARGET)
