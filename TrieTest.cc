#include "Trie.hh"
#include "Testing.hh"
#include <iostream>
#include <set>
#include <cassert>
#include <algorithm>

class TrieTest {
private:
    std::set<std::string> trie;
    
    bool startswith(const std::string& s, const std::string& start) {
        if (start.size() > s.size()) return false;
        for (int i = 0; i < (int)start.size(); i++) if (s[i] != start[i]) return false;
        return true;
    }
    
public:
    TrieTest() { }
    TrieTest(const std::vector<std::string>& v) {
        trie = std::set<std::string>(v.begin(), v.end());
    }

    ~TrieTest() {}

    // Returns true if s wasn't there and was successfully inserted
    bool insert(std::string& s) {
        if (trie.count(s)) return false;
        trie.insert(s);
        return true;
        
    }    

    // Returns true if s was there and was successfully removed
    bool remove(std::string& s) {
        if (trie.count(s)) {
            trie.erase(s);
            return true;
        }
        else return false;
    }
    
    // Returns true if s is in the trie
    bool contains(std::string& s) {
        return trie.count(s);
    }    
    // Returns the number of trie stored
    int size() {
        return trie.size();
    }

    // Returns all words contained in the trie starting with start, in alphabetical order
    std::vector<std::string> words(std::string start = "") {
        std::vector<std::string> res;
        for (auto s : trie) {
            if (startswith(s, start)) res.push_back(s); 
        }
        return res;
    }
    
    std::string random() {
        if (size() == 0) return "";
        int rnd = rand()%size();
        auto it = trie.begin();
        for (; rnd; rnd--);
        return *it;
    }
};


int main() {
    Testing::initialize_random();
    Trie t;
    TrieTest test;
    int NUM_TESTS = 20000;
    Testing::introduce("Trie", NUM_TESTS);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        std::string ins = Testing::random_string(Testing::random_int(1, 15));

        bool ins1 = t.insert(ins);
        bool ins2 = test.insert(ins);
        assert(ins1 == ins2);
        
        if (t.size() != 0 and Testing::random_int(0, 2)) {
            std::string to_remove = test.random();
            bool rem1 = t.remove(to_remove);
            bool rem2  = test.remove(to_remove);
            assert(rem1 == rem2);
        }
        std::string check = Testing::random_string(Testing::random_int(1, 5));
        assert(t.words(check) == test.words(check));
    }
    Testing::success();
}
