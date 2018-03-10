#Makefile - PANAGIOTIS EVANGELIOU  AM:1115201500039

OBJS = ./main/main.o ./ManageFuns/ManageFuns.o
SOURCE = ./main/main.cc ./ManageFuns/ManageFuns.cc
HEADER = ./ManageFuns/ManageFuns.h
OUT = ./build/minisearch
CC = g++
FLAGS = -g -c -Wall

$(OUT): $(OBJS)
	$(CC) -g -Wall $(OBJS) -o $@

./main/main.o: ./main/main.cc
	$(CC) $(FLAGS) ./main/main.cc -o ./main/main.o

./ManageFuns/ManageFuns.o: ./ManageFuns/ManageFuns.cc
	$(CC) $(FLAGS) ./ManageFuns/ManageFuns.cc -o ./ManageFuns/ManageFuns.o

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
