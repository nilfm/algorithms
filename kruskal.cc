// Kruskal's algorithm: find the minimum spanning tree of a graph in O(E*log(E)) time

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

using P = pair<int, int>;
using VP = vector<P>;
using VVP = vector<VP>;
int n, m;
VVP graph;

vector<int> parent, ranking;

int find(int x) {
    return (parent[x] == -1 ? x : parent[x] = find(parent[x]));
}

struct Triplet {
    int c, x, y;
    Triplet(int _c, int _x, int _y) : c(_c), x(_x), y(_y) {}
    bool operator<(const Triplet& other) {
        if (c != other.c) return c < other.c;
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

VP kruskal() {
    vector<Triplet> v(m, {0, 0, 0});
    int k = 0;
    for (int i = 0; i < (int)graph.size(); i++) {
        for (auto& p : graph[i]) {
            v[k] = Triplet(p.first, i, p.second);
            k++;
        }
    }
    sort(v.begin(), v.end());
    int cnt = 0;
    VP res;
    parent = vector<int>(n, -1);
    ranking = vector<int>(n, 1);
    for (Triplet& t : v) {
        int x = t.x, y = t.y;
        int rx = find(x);
        int ry = find(y);
        if (rx != ry) {
            if (ranking[rx] > ranking[ry]) {
                parent[ry] = rx;
                ranking[rx] = max(ranking[rx], 1 + ranking[ry]);
            }
            else {
                parent[rx] = ry;
                ranking[ry] = max(ranking[ry], 1 + ranking[rx]);
            }
            res.push_back(make_pair(x, y));
            cnt++;
        }
        if (cnt >= n-1) return res;
    }
    return VP();
}

int main() {
    cout << "Enter number of vertices: ";
    cin >> n;
    graph = VVP(n);
    cout << "Enter number of edges: ";
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y, c;
        cout << "(x, y, cost) = ";
        cin >> x >> y >> c;
        graph[x].push_back(make_pair(c, y));
    }
    VP mst = kruskal();
    for (auto& p : mst) {
        cout << p.first << "-" << p.second << endl;
    }
}
