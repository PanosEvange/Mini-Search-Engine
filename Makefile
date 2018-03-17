#Makefile - PANAGIOTIS EVANGELIOU  AM:1115201500039

OBJS = ./main/main.o ./ManageFuns/ManageFuns.o ./DocMap/DocMap.o ./PostingList/PostingList.o ./PostingList/DocInfo.o ./Trie/Trie.o ./Heap/Heap.o
SOURCE = ./main/main.cc ./ManageFuns/ManageFuns.cc ./DocMap/DocMap.cc ./PostingList/PostingList.cc ./PostingList/DocInfo.cc ./Trie/Trie.cc ./Heap/Heap.cc
HEADER = ./ManageFuns/ManageFuns.h ./DocMap/DocMap.h ./PostingList/PostingList.h ./PostingList/DocInfo.h ./Trie/Trie.h ./Heap/Heap.h
OUT = ./build/minisearch
CC = g++
FLAGS = -g -c -Wall

$(OUT): $(OBJS)
	$(CC) -g -Wall $(OBJS) -o $@

./main/main.o: ./main/main.cc
	$(CC) $(FLAGS) ./main/main.cc -o ./main/main.o

./ManageFuns/ManageFuns.o: ./ManageFuns/ManageFuns.cc
	$(CC) $(FLAGS) ./ManageFuns/ManageFuns.cc -o ./ManageFuns/ManageFuns.o

./DocMap/DocMap.o: ./DocMap/DocMap.cc
	$(CC) $(FLAGS) ./DocMap/DocMap.cc -o ./DocMap/DocMap.o

./PostingList/PostingList.o: ./PostingList/PostingList.cc
	$(CC) $(FLAGS) ./PostingList/PostingList.cc -o ./PostingList/PostingList.o

./PostingList/DocInfo.o: ./PostingList/DocInfo.cc
	$(CC) $(FLAGS) ./PostingList/DocInfo.cc -o ./PostingList/DocInfo.o

./Trie/Trie.o: ./Trie/Trie.cc
	$(CC) $(FLAGS) ./Trie/Trie.cc -o ./Trie/Trie.o

./Heap/Heap.o: ./Heap/Heap.cc
	$(CC) $(FLAGS) ./Heap/Heap.cc -o ./Heap/Heap.o

clean:
	rm -f $(OBJS) $(OUT)

count:
	wc $(SOURCE) $(HEADER)
