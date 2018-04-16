# Makefile for building Bellman-Ford algorithm
CC=g++
CFLAGS=-std=c++11
LDFLAGS=-lpthread
SOURCES=./src/main.cpp ./src/graph.cpp
EXECUTABLE=bellman-ford

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	rm $(EXECUTABLE)
