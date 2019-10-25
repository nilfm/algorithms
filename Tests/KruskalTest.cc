// Kruskal's algorithm: find the minimum spanning tree of a graph in O(E*log(E)) time

#include "../Graph.hh"
#include "../Testing.hh"
#include <vector>
#include <algorithm>
#include <cassert>

// Represents a weighted undirected graph
class KruskalTest {
private:
    std::vector<std::unordered_map<int, double>> adj;
public:
    KruskalTest(int vertices) {
        adj = std::vector<std::unordered_map<int, double>>(vertices);
    }
    ~KruskalTest() {}
    
    bool add(int i, int j, double cost) {
        if (i == j) return false;
        if (cost < 0) return false;
        if (i < 0 or j < 0 or i >= adj.size() or j >= adj.size()) return false;
        if (adj[i].count(j)) return false;
        adj[i].insert(std::make_pair(j, cost));
        adj[j].insert(std::make_pair(i, cost));
        return true;
    }
    
    bool remove(int i, int j) {
        if (i < 0 or j < 0 or i >= adj.size() or j >= adj.size()) return false;
        if (not adj[i].count(j)) return false;
        adj[i].erase(j);
        adj[j].erase(i);
        return true;
    }
    
    bool update(int i, int j, double cost) {
        if (i < 0 or j < 0 or i >= adj.size() or j >= adj.size()) return false;
        if (not adj[i].count(j)) return false;
        adj[i][j] = cost;
        adj[j][i] = cost;
        return true;
    }
    
    // Returns the minimum spanning tree of the graph, if it's connected. Otherwise, returns an empty vector.
    std::vector<std::pair<int, int>> kruskal() {
        std::vector<std::pair<int, std::pair<int, int>>> edges;
        for (int i = 0; i < (int)adj.size(); i++) {
            for (auto& p : adj[i]) {
                if (i < p.first) {
                    edges.push_back(std::make_pair(p.second, std::make_pair(i, p.first)));
                }
            }
        }
        std::sort(edges.begin(), edges.end());
        std::vector<int> group(adj.size());
        for (int i = 0; i < (int)adj.size(); i++) group[i] = i;
        
        int used = 0;
        std::vector<std::pair<int, int>> res;
        for (auto& p : edges) {
            int i = p.second.first;
            int j = p.second.second;
            if (group[i] != group[j]) {
                for (int k = 0; k < (int)adj.size(); k++) {
                    if (group[k] == group[j]) group[k] = group[i];
                }
                res.push_back(std::make_pair(i, j));
                used++;
                if (used == adj.size()-1) return res;    
            }
        }
        return std::vector<std::pair<int, int>>();
    }
};

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 200;
    Testing::introduce("Kruskal", NUM_TESTS);
    Graph g(10000);
    KruskalTest t(10000);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int vertex1 = Testing::random_int(0, 9999);
        int vertex2 = Testing::random_int(0, 9999);
        double cost = (double)Testing::random_int(0, 9999)/Testing::random_int(1, 999);
        if (Testing::random_int(0, 2)) {
            bool add1 = g.add(vertex1, vertex2, cost);
            bool add2 = t.add(vertex1, vertex2, cost);
            assert(add1 == add2);
        }
        else {
            bool rem1 = g.remove(vertex1, vertex2);
            bool rem2 = t.remove(vertex1, vertex2);
            assert(rem1 == rem2);
        }
        assert(g.kruskal() == t.kruskal());
    } 
    Testing::success();
}
