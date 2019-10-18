// Dijkstra's algorithm: Shortest path in weighted graph in O((V+E)logV) time.

#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

using P = pair<int, int>;
using VP = vector<P>;
using VVP = vector<VP>;
int n, m;
VVP graph;

const int INF = 1e9;

template<class T>
class Comp {
public:
	bool operator()(const T& a, const T& b) {
		if (a.first != b.first) return a.first < b.first;
		return a.second < b.second;
	}
};

int dijkstra(int start, int end) {
	priority_queue<P, vector<P>, Comp<P>> pq;
	vector<int> dist(n, INF);
	pq.push(make_pair(0, start));
	dist[start] = 0;
	while (not pq.empty()) {
		auto p = pq.top(); pq.pop();
		int d = p.first, x = p.second;
		if (x != end) {
			for (P& adj : graph[x]) {
				int c = adj.first, y = adj.second;
				if (c+d < dist[y]) {
					pq.push(make_pair(c+d, y));
					dist[y] = c+d;
				}
			}
		}
	}
	return dist[end] == INF ? -1 : dist[end];
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
	int start, end;
	cout << "Enter start: ";
	cin >> start;
	cout << "Enter end: ";
	cin >> end;
	cout << dijkstra(start, end) << endl;
}
