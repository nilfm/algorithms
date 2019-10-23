CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

SRC = *.cc
HEADERS = *.hh
TESTING = Testing.cc Testing.hh
ALL = CircularQueueTest dijkstra FenwickTree kmp kruskal LRUCacheTest manacher MaxMinStackTest QuickMedianTest Trie

all: $(ALL)

CircularQueueTest: CircularQueue.hh CircularQueueTest.cc $(TESTING)
	$(CC) $(CFLAGS) CircularQueueTest.cc Testing.cc -o CircularQueueTest
	
dijkstra: dijkstra.cc
	$(CC) $(CFLAGS) dijkstra.cc -o dijkstra
	
kmp: kmp.cc
	$(CC) $(CFLAGS) kmp.cc -o kmp
	
kruskal: kruskal.cc
	$(CC) $(CFLAGS) kruskal.cc -o kruskal
	
LRUCacheTest: LRUCache.hh LRUCacheTest.cc $(TESTING)
	$(CC) $(CFLAGS) LRUCacheTest.cc Testing.cc -o LRUCacheTest

manacher: manacher.cc
	$(CC) $(CFLAGS) manacher.cc -o manacher
	
MaxMinStackTest: MaxMinStack.hh MaxMinStackTest.cc $(TESTING)
	$(CC) $(CFLAGS) MaxMinStackTest.cc Testing.cc -o MaxMinStackTest
	
QuickMedianTest: QuickMedian.hh QuickMedianTest.cc $(TESTING) 
	$(CC) $(CFLAGS) QuickMedianTest.cc Testing.cc -o QuickMedianTest
	
Trie: Trie.hh Trie.cc $(TESTING)
	$(CC) $(CFLAGS) Trie.cc Testing.cc -o Trie
	
FenwickTree: FenwickTree.hh FenwickTree.cc $(TESTING)
	$(CC) $(CFLAGS) FenwickTree.cc Testing.cc -o FenwickTree

clean:
	rm $(ALL)
