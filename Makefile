CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

LIBS := StringAlgorithm.hh
TESTING := Testing.cc Testing.hh
ALL := CircularQueue FenwickTree KMP LRUCache MaxMinStack QuickMedian Trie Manacher Kruskal Dijkstra
TESTS := $(ALL:%=Tests/%Test)

.PHONY: clean all

all: test

Tests/%Test: Tests/%Test.cc $(TESTING)
	@ $(CXX) $(CFLAGS) $@.cc Testing.cc -o $@

test: $(TESTS) $(TESTING)
	@run-parts --exit-on-error Tests

test-%: Tests/$@ $(TESTING)
	@ $(CXX) $(CFLAGS) $@.cc Testing.cc -o $@
	@ Tests/$@Test

clean:
	@echo "Removing all executables"
	@rm Tests/*Test
