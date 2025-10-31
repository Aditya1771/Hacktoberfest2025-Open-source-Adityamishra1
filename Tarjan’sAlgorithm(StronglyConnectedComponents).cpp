#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<vector<int>> graph;
vector<int> disc, low, inStack;
stack<int> st;
int timer = 0;

void tarjanSCC(int u) {
    disc[u] = low[u] = ++timer;
    st.push(u); inStack[u] = true;

    for (int v : graph[u]) {
        if (!disc[v]) {
            tarjanSCC(v);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        cout << "SCC: ";
        while (true) {
            int node = st.top(); st.pop();
            inStack[node] = false;
            cout << node << " ";
            if (node == u) break;
        }
        cout << endl;
    }
}

int main() {
    int V, E;
    cout << "🔗 Tarjan's Strongly Connected Components\n";
    cin >> V >> E;
    graph.resize(V);
    disc.assign(V, 0);
    low.assign(V, 0);
    inStack.assign(V, 0);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < E; i++) {
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }

    for (int i = 0; i < V; i++)
        if (!disc[i])
            tarjanSCC(i);
}
