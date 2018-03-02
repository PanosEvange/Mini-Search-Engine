#Makefile - PANAGIOTIS EVANGELIOU  AM:1115201500039

OBJS = ./main/main.o ./manageFuns/manageFuns.o
SOURCE = ./main/main.c ./manageFuns/manageFuns.c
HEADER = ./manageFuns/manageFuns.h
OUT = ./build/minisearch
CC = gcc
FLAGS = -g -c -Wall

$(OUT): $(OBJS)
	$(CC) -g -Wall $(OBJS) -o $@

./main/main.o: ./main/main.c
	$(CC) $(FLAGS) ./main/main.c -o ./main/main.o

./manageFuns/manageFuns.o: ./manageFuns/manageFuns.c
	$(CC) $(FLAGS) ./manageFuns/manageFuns.c -o ./manageFuns/manageFuns.o

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
