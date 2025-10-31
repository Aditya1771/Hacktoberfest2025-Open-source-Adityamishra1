#include <iostream>
#include <vector>
using namespace std;

struct Edge { int u, v, w; };

void bellmanFord(int V, int E, vector<Edge>& edges, int src) {
    vector<int> dist(V, 1e9);
    dist[src] = 0;

    for (int i = 1; i < V; i++)
        for (auto &e : edges)
            if (dist[e.u] + e.w < dist[e.v])
                dist[e.v] = dist[e.u] + e.w;

    for (auto &e : edges)
        if (dist[e.u] + e.w < dist[e.v]) {
            cout << "⚠️ Negative weight cycle detected\n";
            return;
        }

    cout << "\n✅ Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "Node " << i << " → " << dist[i] << endl;
}

int main() {
    int V, E, src;
    cout << "🚗 Bellman-Ford Algorithm\nEnter vertices and edges: ";
    cin >> V >> E;
    vector<Edge> edges(E);
    cout << "Enter edges (u v weight):\n";
    for (int i = 0; i < E; i++) cin >> edges[i].u >> edges[i].v >> edges[i].w;
    cout << "Enter source: "; cin >> src;
    bellmanFord(V, E, edges, src);
}
