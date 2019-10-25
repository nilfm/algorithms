#ifndef __UNION_FIND__
#define __UNION_FIND__

#include <vector>

class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank;
    int find(int i) {
        return parent[i] == -1 ? i : parent[i] = find(parent[i]);
    }
    bool valid(int i) {
        return i >= 0 and i < parent.size();
    }
public:
    UnionFind(int vertices) {
        parent = std::vector<int>(vertices, -1);
        rank = std::vector<int>(vertices, 1);
    }
    ~UnionFind() {}
    bool connected(int i, int j) {
        if (not valid(i) or not valid(j)) return false;
        return find(i) == find(j);
    }
    // If i and j are connected or invalid inputs, return false. Otherwise, join them and return true.
    bool join(int i, int j) {
        if (not valid(i) or not valid(j)) return false;
        if (connected(i, j)) return false;
        int ri = find(i);
        int rj = find(j);
        if (rank[ri] > rank[rj]) {
            parent[rj] = ri;
            rank[ri] = std::max(rank[ri], 1 + rank[rj]);
        }
        else {
            parent[ri] = rj;
            rank[rj] = std::max(rank[rj], 1 + rank[ri]);
        }
        return true;
    }
};

#endif
