#Makefile - PANAGIOTIS EVANGELIOU  AM:1115201500039

OBJS = main.o ./manageFuns/manageFuns.o
SOURCE = main.c ./manageFuns/manageFuns.c
HEADER = ./manageFuns/manageFuns.h
OUT = minisearch
CC = gcc
FLAGS = -g -c -Wall

$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $@

main.o: main.c
	$(CC) $(FLAGS) main.c

./manageFuns/manageFuns.o: ./manageFuns/manageFuns.c
	 $(CC) $(FLAGS) ./manageFuns/manageFuns.c

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
