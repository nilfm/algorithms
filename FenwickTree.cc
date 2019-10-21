#include "FenwickTree.hh"
#include <iostream>

FenwickTree::FenwickTree(int max_size) {
	sz = max_size+1;
	tree = std::vector<int>(sz, 0);
}

FenwickTree::FenwickTree(const std::vector<int>& v) {
	sz = v.size()+1;
	tree = std::vector<int>(sz, 0);
	for (int i = 0; i < sz-1; i++) add(i, v[i]);
}

int FenwickTree::sum(int i) {
	i++;
	int sum = 0;
	while (i > 0) {
		sum += tree[i];
		i -= LSB(i);
	}
	return sum;
}

void FenwickTree::add(int i, int k) {
	i++;
	while (i < sz) {
		tree[i] += k;
		i += LSB(i);
	}
}
	
int FenwickTree::sum(int i, int j) {
	return sum(j) - sum(i-1);
}

int main() {
	std::vector<int> v = {1, 2, 3, 4, 5};
	std::cout << "Constructing tree..." << std::endl;
	FenwickTree T(v);
	std::cout << "Sum of range [1, 3] = " << T.sum(1, 3) << std::endl;
	std::cout << "Adding 10 to position 2" << std::endl;
	T.add(2, 10);
	std::cout << "Sum of range [1, 3] = " << T.sum(1, 3) << std::endl;
}
