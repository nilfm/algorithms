// Dijkstra's algorithm: Shortest path in weighted graph in O((V+E)logV) time.

#include "../Testing.hh"
#include "../Graph.hh"
#include <vector>
#include <unordered_map>
#include <queue>
#include <cassert>

class DijkstraTest {
private:
    const double INF = 1e9;
    std::vector<std::unordered_map<int, double>> adj;
public:
    DijkstraTest(int vertices) {
        adj = std::vector<std::unordered_map<int, double>>(vertices);
    }
    ~DijkstraTest() {}
    
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

    // Uses Bellman-Ford's algorithm for testing purposes
    // Returns a vector with the visited vertices in order
    std::vector<int> dijkstra(int start, int end) {
        std::vector<double> dist(adj.size(), INF);
        std::vector<int> parent(adj.size(), -1);
        dist[start] = 0;
        for (int i = 0; i < adj.size(); i++) {
            for (int j = 0; j < adj.size(); j++) {
                for (auto& p : adj[j]) {
                    int k = p.first;
                    double d = p.second;
                    if (dist[k] + d < dist[j]) {
                        dist[j] = dist[k] + d;
                        parent[j] = k;
                    }
                }    
            }
        }
        std::vector<int> res;
        if (dist[end] == INF) return res;
        int curr = end;
        while (curr != start) {
            res.push_back(curr);
            curr = parent[curr];
        }
        res.push_back(start);
        std::reverse(res.begin(), res.end());
        return res;
    }
};

int main() {
    Testing::initialize_random();
    int NUM_TESTS = 200;
    Testing::introduce("Dijkstra", NUM_TESTS);
    Graph g(1000);
    DijkstraTest t(1000);
    for (int i = 0; i < NUM_TESTS; i++) {
        Testing::percentage(i, NUM_TESTS);
        int vertex1 = Testing::random_int(0, 999);
        int vertex2 = Testing::random_int(0, 999);
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
        int start = Testing::random_int(0, 999);
        int end = Testing::random_int(0, 999);
        assert(g.dijkstra(start, end) == t.dijkstra(start, end));
    } 
    Testing::success();
}
