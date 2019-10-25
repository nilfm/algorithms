CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic

LIBS := StringAlgorithm.hh
TESTING := Testing.cc Testing.hh
ALL := CircularQueue FenwickTree KMP LRUCache MaxMinStack QuickMedian Trie
TESTS := $(ALL:%=Tests/%Test)

all: $(ALL)

Tests/%Test: Tests/%Test.cc $(TESTING)
	@ $(CC) $(CFLAGS) $@.cc Testing.cc -o $@

test: $(TESTS)
	@run-parts --exit-on-error Tests

clean:
	@echo "Removing all executables"
	@rm Tests/*Test
