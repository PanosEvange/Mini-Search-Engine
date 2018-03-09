#Makefile - PANAGIOTIS EVANGELIOU  AM:1115201500039

OBJS = ./main/main.o ./manageFuns/manageFuns.o
SOURCE = ./main/main.cc ./manageFuns/manageFuns.cc
HEADER = ./manageFuns/manageFuns.h
OUT = ./build/minisearch
CC = g++
FLAGS = -g -c -Wall

$(OUT): $(OBJS)
	$(CC) -g -Wall $(OBJS) -o $@

./main/main.o: ./main/main.cc
	$(CC) $(FLAGS) ./main/main.cc -o ./main/main.o

./manageFuns/manageFuns.o: ./manageFuns/manageFuns.cc
	$(CC) $(FLAGS) ./manageFuns/manageFuns.cc -o ./manageFuns/manageFuns.o

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
