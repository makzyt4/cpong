CC=gcc
CFLAGS=-Wall -Werror -pedantic
TARGET=bin/cpong
SOURCES=$(wildcard src/*.c)
LDFLAGS=-lSDL2

default: all

all:
	mkdir -p bin
	$(CC) $(LDFLAGS) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -rf bin/
