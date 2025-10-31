#include <iostream>
#include <vector>
#include <queue>
using namespace std;



void topologicalSort(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);

    // Step 1: Compute indegree (number of incoming edges) for each vertex
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }

    // Step 2: Queue all vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0)
            q.push(i);
    }

    vector<int> topoOrder;

    // Step 3: Process until queue becomes empty
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);

        // Decrease indegree of neighbors
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0)
                q.push(v);
        }
    }

    // Step 4: Check for cycle (if not all vertices are processed)
    if (topoOrder.size() != V) {
        cout << "The graph contains a cycle. Topological sort not possible.\n";
        return;
    }

    // Step 5: Print topological order
    cout << "Topological Order: ";
    for (int node : topoOrder)
        cout << node << " ";
    cout << endl;
}

int main() {
    cout << "Topological Sort using Kahn's Algorithm\n";

    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);
    cout << "Enter directed edges (u v) meaning u → v:\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    topologicalSort(V, adj);
    return 0;
}
