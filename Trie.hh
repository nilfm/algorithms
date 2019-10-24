#ifndef __TRIE__
#define __TRIE__

#include <vector>
#include <string>
#include <map>
#include <stack>
#include <memory>

const char END = '$';


struct TrieNode {
    std::map<char, std::shared_ptr<TrieNode>> children;
    TrieNode() {}   
    TrieNode(const TrieNode& other) {
        copy(children, other.children);
    }  
    TrieNode& operator=(const TrieNode& other) {
        if (this == &other) return *this;
        copy(children, other.children);
        return *this;
    }
    static void copy(std::map<char, std::shared_ptr<TrieNode>>& me, const std::map<char, std::shared_ptr<TrieNode>>& other) {
        for (auto p : other) {
            me[p.first] = std::make_shared<TrieNode>();
            copy(me[p.first]->children, (p.second)->children);
        }
    }
};

class Trie {
private:
    std::shared_ptr<TrieNode> head;
    int sz;
    
    void find(std::string start, std::vector<std::string>& v, std::shared_ptr<TrieNode> head, std::string curr) {
        if (head == nullptr) return;
        for (auto p : head->children) {
            if (p.first == END) {
                v.push_back(start+curr);
            }
            else {
                find(start, v, p.second, curr+p.first);
            }
        }
    }
    
public:
    Trie() {
        sz = 0;
        head = std::make_shared<TrieNode>();    
    }
    Trie(const std::vector<std::string>& v) {
        sz = 0;
        head = std::make_shared<TrieNode>();
        for (std::string s : v) insert(s);
    }
    Trie(const Trie& other) {
        sz = other.sz;
        head = std::make_shared<TrieNode>();
        *head = *(other.head);
    }
    Trie(Trie&& other) {
        sz = other.sz;
        head = other.head;
        other.sz = 0;
        other.head = nullptr;
    }
    Trie& operator=(const Trie& other) {
        if (this == &other) return *this;
        sz = other.sz;
        head = std::make_shared<TrieNode>();
        *head = *(other.head);    
        return *this;
    }
    Trie& operator=(Trie&& other) {
        if (this == &other) return *this;
        head = other.head;
        sz = other.sz;
        return *this;
    }

    ~Trie() {}

    // Returns true if s wasn't there and was successfully inserted
    bool insert(std::string s) {
        s.push_back(END);
        bool res = false;
        std::shared_ptr<TrieNode> curr = head;
        for (int i = 0; i < (int)s.size(); i++) {
            if (not (curr->children).count(s[i])) {
                res = true;
                (curr->children)[s[i]] = std::make_shared<TrieNode>();
            }
            curr = (curr->children)[s[i]];
        }
        if (res) sz++;
        return res;
    }    

    // Returns true if s was there and was successfully removed
    bool remove(std::string s) {
        s.push_back(END);
        std::stack<std::shared_ptr<TrieNode>> to_remove;
        std::shared_ptr<TrieNode> curr = head;
        for (int i = 0; i < (int)s.size(); i++) {
            if (not (curr->children).count(s[i])) {
                return false;
            }
            to_remove.push(curr);
            if (s[i] != END) curr = (curr->children)[s[i]];
        }
        //Remove the end marker
        (curr->children).erase(END);
        
        int i = s.size()-1;
        while (not to_remove.empty() and (curr->children).size() == 0) {
            curr = to_remove.top();
            to_remove.pop();
            (curr->children).erase(s[i]);
            i--;
        }
        sz--;
        return true;
    }
    
    // Returns true if s is in the trie
    bool contains(std::string s) {
        s.push_back(END);
        std::shared_ptr<TrieNode> curr = head;
        for (int i = 0; i < (int)s.size(); i++) {
            if (not (curr->children).count(s[i])) {
                return false;
            }
            curr = (curr->children)[s[i]];
        }
        return true;
    }    
    
    // Returns the number of words stored
    int size() {
        return sz;
    }

    // Returns all words contained in the trie starting with start, in alphabetical order
    std::vector<std::string> words(std::string start = "") {
        std::vector<std::string> res;
        std::shared_ptr<TrieNode> curr = head;
        for (int i = 0; i < (int)start.size(); i++) {
            if (not (curr->children).count(start[i])) {
                return std::vector<std::string>();
            }
            curr = (curr->children)[start[i]];
        }
        find(start, res, curr, "");
        return res;
    }
};

#endif
