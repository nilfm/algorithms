CC = g++
CFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

SRC = *.cc
HEADERS = *.hh
TESTING = Testing.cc Testing.hh
ALL = CircularQueueTest dijkstra FenwickTreeTest KMPTest kruskal LRUCacheTest manacher MaxMinStackTest QuickMedianTest TrieTest
TEST = CircularQueueTest FenwickTreeTest MaxMinStackTest QuickMedianTest TrieTest LRUCacheTest KMPTest

all: $(ALL)

CircularQueueTest: CircularQueue.hh CircularQueueTest.cc $(TESTING)
	$(CC) $(CFLAGS) CircularQueueTest.cc Testing.cc -o CircularQueueTest
	
dijkstra: dijkstra.cc
	$(CC) $(CFLAGS) dijkstra.cc -o dijkstra
	
KMPTest: KMPTest.cc StringAlgorithms.hh $(TESTING)
	$(CC) $(CFLAGS) KMPTest.cc Testing.cc -o KMPTest
	
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
	
TrieTest: Trie.hh TrieTest.cc $(TESTING)
	$(CC) $(CFLAGS) TrieTest.cc Testing.cc -o TrieTest
	
FenwickTreeTest: FenwickTree.hh FenwickTreeTest.cc $(TESTING)
	$(CC) $(CFLAGS) FenwickTreeTest.cc Testing.cc -o FenwickTreeTest

test: $(TEST)
	@(./CircularQueueTest && ./FenwickTreeTest && ./MaxMinStackTest && ./QuickMedianTest && ./TrieTest && ./LRUCacheTest && ./KMPTest)

clean:
	rm $(ALL)
