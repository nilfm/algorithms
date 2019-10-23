CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

SRC = *.cc
HEADERS = *.hh
ALL = CircularQueueTest dijkstra FenwickTree kmp kruskal LRUCacheTest manacher MaxMinStackTest QuickMedianTest Trie

all: $(ALL)

CircularQueueTest: CircularQueue.hh CircularQueueTest.cc
	$(CC) $(CFLAGS) CircularQueueTest.cc -o CircularQueueTest
	
dijkstra: dijkstra.cc
	$(CC) $(CFLAGS) dijkstra.cc -o dijkstra
	
kmp: kmp.cc
	$(CC) $(CFLAGS) kmp.cc -o kmp
	
kruskal: kruskal.cc
	$(CC) $(CFLAGS) kruskal.cc -o kruskal
	
LRUCacheTest: LRUCache.hh LRUCacheTest.cc
	$(CC) $(CFLAGS) LRUCacheTest.cc -o LRUCacheTest

manacher: manacher.cc
	$(CC) $(CFLAGS) manacher.cc -o manacher
	
MaxMinStackTest: MaxMinStack.hh MaxMinStackTest.cc
	$(CC) $(CFLAGS) MaxMinStackTest.cc -o MaxMinStackTest
	
QuickMedianTest: QuickMedian.hh QuickMedianTest.cc
	$(CC) $(CFLAGS) QuickMedianTest.cc -o QuickMedianTest
	
Trie: Trie.hh Trie.cc
	$(CC) $(CFLAGS) Trie.cc -o Trie
	
FenwickTree: FenwickTree.hh FenwickTree.cc
	$(CC) $(CFLAGS) FenwickTree.cc -o FenwickTree

clean:
	rm $(ALL)
