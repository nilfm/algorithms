#ifndef __LRU_CACHE__
#define __LRU_CACHE__

#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>

template<class K, class V>
struct Node {
	int key, value;
	std::shared_ptr<Node<K, V>> prev;
	std::shared_ptr<Node<K, V>> next;
	Node() {}
	Node(K k, V v) {
		key = k;
		value = v;
		prev = std::make_shared<Node<K, V>>();
		next = std::make_shared<Node<K, V>>();
	}
};

template<class K, class V>
class LinkedList {
private:
	std::shared_ptr<Node<K, V>> front;
	std::shared_ptr<Node<K, V>> rear;
	bool empty() {
		return rear == nullptr;
	}
public:
	LinkedList() {
		front = nullptr;
		rear = nullptr;
	}
	std::shared_ptr<Node<K, V>> add_page(K key, V value) {
		std::shared_ptr<Node<K, V>> page = std::make_shared<Node<K, V>>(key, value);
		if (front == nullptr and rear == nullptr) {
			front = rear = page;
		}
		else {
			page->next = front;
			front->prev = page;
			front = page;
		}
		return page;
	}
	void move_page_to_head(std::shared_ptr<Node<K, V>> page) {
		if (page == front) return;
		else if (page == rear) {
			rear = rear->prev;
			rear->next = nullptr;
		}
		else {
			page->prev->next = page->next;
			page->next->prev = page->prev;
		}
		page->next = front;
		page->prev = nullptr;
		front->prev = page;
		front = page;
	}
	void remove_rear_page() {
		if (empty()) return;
		if (front == rear) {
			front = rear = nullptr;
		}
		else {
			std::shared_ptr<Node<K, V>> temp = rear;
			rear = rear->prev;
			rear->next = nullptr;
		}
	}
	std::shared_ptr<Node<K, V>> get_rear_page() {
		return rear;
	}
};

template<class K, class V>
class LRUCache {
private:
	int max_size;
	int sz;
	std::shared_ptr<LinkedList<K, V>> page_list;
	std::unordered_map<K, std::shared_ptr<Node<K, V>>> page_map;
	
public:
	// Constructs an LRU Cache with space for max_size elements (K, V pairs)
	LRUCache(int _max_size) {
		max_size = _max_size;
		sz = 0;
		page_list = std::make_shared<LinkedList<K, V>>();
	}
	~LRUCache() {}
	
	// Returns the value associated with key K. If not present, returns V()
	V get(K key) {
		if (not page_map.count(key)) return V();
		V val = page_map[key]->value;
		page_list->move_page_to_head(page_map[key]);
		return val;
	}
	
	// Inserts the key-value pair into the LRU Cache. Returns true if the key wasn't there already, and false otherwise.
	bool put(K key, V value) {
		if (page_map.count(key)) {
			page_map[key]->value = value;
			page_list->move_page_to_head(page_map[key]);
			return false;
		}
		if (full()) {
			K k = page_list->get_rear_page()->key;
			page_map.erase(k);
			page_list->remove_rear_page();
			sz--;
		}
		std::shared_ptr<Node<K, V>> page = page_list->add_page(key, value);
		sz++;
		page_map[key] = page;
		return true;
	}
	
	// Returns true if the cache is full
	bool full() {
		return sz == max_size;
	}
	
	// Returns true if the cache is empty
	bool empty() {
		return sz == 0;
	}
	
	// Returns the number of key-value pairs in the cache
	int size() {
		return sz;
	}
	
};

#endif
