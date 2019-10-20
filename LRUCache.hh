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
	Node(const Node& other) {
		key = other.key;
		value = other.value;
		prev = next = nullptr;
	}
	Node(Node&& other) {
		key = other.key;
		other.key = K();
		value = other.value;
		other.value = V();
		prev = other.prev;
		other.prev = nullptr;
		next = other.next;
		other.next = nullptr;
	}
	Node& operator=(const Node& other) {
		if (this == &other) return *this;
		key = other.key;
		value = other.value;
		prev = next = nullptr;
		return *this;
	}
	Node& operator=(Node&& other) {
		if (this == &other) return *this;
		key = other.key;
		other.key = K();
		value = other.value;
		other.value = V();
		prev = other.prev;
		other.prev = nullptr;
		next = other.next;
		other.next = nullptr;
		return *this;
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
	LinkedList(const LinkedList& other) {
		if (other.front == nullptr) {
			front = rear = nullptr;
		}
		else {
			front = std::make_shared<Node<K, V>>(*(other.front));
			std::shared_ptr<Node<K, V>> temp_other = (other.front)->next;
			std::shared_ptr<Node<K, V>> temp = front;
			while (temp_other) {
				temp->next = std::make_shared<Node<K, V>>(*temp_other);
				(temp->next)->prev = temp;
				temp = temp->next;
				temp_other = temp_other->next;
			}
			rear = temp;
		}
	}
	LinkedList(LinkedList&& other) {
		front = other.front;
		other.front = nullptr;
		rear = other.rear;
		other.rear == nullptr;
	}
	LinkedList& operator=(const LinkedList& other) {
		if (this == &other) return *this;
		if (other.front == nullptr) {
			front = rear = nullptr;
		}
		else {
			front = std::make_shared<Node<K, V>>(*(other.front));
			std::shared_ptr<Node<K, V>> temp_other = (other.front)->next;
			std::shared_ptr<Node<K, V>> temp = front;
			while (temp_other) {
				temp->next = std::make_shared<Node<K, V>>(*temp_other);
				(temp->next)->prev = temp;
				temp = temp->next;
				temp_other = temp_other->next;
			}
			rear = temp;
		}
		return *this;
	}
	LinkedList& operator=(LinkedList&& other) {
		if (this == &other) return *this;
		front = other.front;
		other.front = nullptr;
		rear = other.rear;
		other.rear == nullptr;
		return *this;
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
	
	std::unordered_map<K, std::shared_ptr<Node<K, V>>> get_map() {
		std::unordered_map<K, std::shared_ptr<Node<K, V>>> ret;
		std::shared_ptr<Node<K, V>> curr = front;
		while (curr) {
			ret[curr->key] = curr;
			curr = curr->next;
		}
		return ret;
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
	LRUCache(const LRUCache& other) {
		max_size = other.max_size;
		sz = other.sz;
		page_list = std::make_shared<LinkedList<K, V>>(*(other.page_list));
		page_map = page_list->get_map();
	}
	LRUCache(LRUCache&& other) {
		max_size = other.max_size;
		other.max_size = 0;
		sz = other.sz;
		other.sz = 0;
		page_list = std::move(other.page_list);
		page_map = std::move(other.page_map);
	}
	LRUCache& operator=(const LRUCache& other) {
		if (this == &other) return *this;
		max_size = other.max_size;
		sz = other.sz;
		page_list = std::make_shared<LinkedList<K, V>>(*(other.page_list));
		page_map = page_list->get_map();
		return *this;
	}
	LRUCache& operator=(LRUCache&& other) {
		if (this == &other) return *this;
		max_size = other.max_size;
		other.max_size = 0;
		sz = other.sz;
		other.sz = 0;
		page_list = std::move(other.page_list);
		page_map = std::move(other.page_map);
		return *this;
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
