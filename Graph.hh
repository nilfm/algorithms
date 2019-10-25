#ifndef __GRAPH__
#define __GRAPH__

#include "UnionFind.hh"
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <algorithm>

// Represents a weighted undirected graph
class Graph {
private:
    const double INF = 1e9;
    std::vector<std::unordered_map<int, double>> adj;
public:
    Graph(int vertices) {
        adj = std::vector<std::unordered_map<int, double>>(vertices);
    }
    ~Graph() {}
    
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
        UnionFind u(adj.size());
        int used = 0;
        std::vector<std::pair<int, int>> res;
        for (auto& p : edges) {
            int i = p.second.first;
            int j = p.second.second;
            if (not u.connected(i, j)) {
                u.join(i, j);
                res.push_back(std::make_pair(i, j));
                used++;
                if (used == adj.size()-1) return res;    
            }
        }
        return std::vector<std::pair<int, int>>();
    }

    // Returns a vector with the visited vertices in order
    std::vector<int> dijkstra(int start, int end) {
        std::priority_queue<std::pair<int, int>> pq;
        std::vector<double> dist(adj.size(), INF);
        pq.push(std::make_pair(0, start));
        dist[start] = 0;
        while (not pq.empty()) {
            auto p = pq.top(); pq.pop();
            double d = -p.first, x = p.second;
            if (x != end) {
                for (auto& q : adj[x]) {
                    int c = q.second, y = q.first;
                    if (c+d < dist[y]) {
                        pq.push(std::make_pair(-c-d, y));
                        dist[y] = c+d;
                    }
                }
            }
        }
        std::vector<int> res;
        if (dist[end] == INF) return res;
        int curr = end;
        while (curr != start) {
            for (auto& p : adj[curr]) {
                if (dist[curr] - dist[p.first] == p.second) {
                    res.push_back(curr);
                    curr = p.first;
                    break;    
                }
            }
        }
        res.push_back(start);
        std::reverse(res.begin(), res.end());
        return res;
    }
};

#endif
