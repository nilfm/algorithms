#ifndef __TRIE__
#define __TRIE__

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <memory>

struct TrieNode {
	std::map<char, std::shared_ptr<TrieNode>> children;
};

class Trie {
private:
	std::shared_ptr<TrieNode> head;
	int sz;
	
	void words(std::string start, std::vector<std::string>& v, std::shared_ptr<TrieNode> head, std::string curr);
	
public:
	Trie();
	Trie(const std::vector<std::string>& v);
	~Trie();
	

	// Returns true if s wasn"t there and was successfully inserted
	bool insert(std::string& s);
	
	// Returns true if s was there and was successfully removed
	bool remove(std::string& s);
	
	// Returns true if s is in the trie
	bool contains(std::string& s);
	
	// Returns the number of words stored
	int size();
	
	// Returns all words contained in the trie starting with start, in alphabetical order
	std::vector<std::string> words(std::string start);
};

#endif
