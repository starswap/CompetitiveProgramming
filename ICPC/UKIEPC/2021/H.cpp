#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<int> res;
vector<bool> visited;

void visit(int u, bool colouring) {
    if (visited[u]) return;
    visited[u] = true;
    if (colouring)  {
        res.push_back(u);
    }
    for (int v : AL[u]) {
        visit(v, !colouring);
    }
    if (!colouring) {
        res.push_back(u);
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    
    AL.assign(V, vector<int>());
    for (int e = 0; e < E; ++e) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    visited.assign(V, false);

    visit(0, true);
    for (int i = 0; i < res.size(); ++i) {
        cout << res[i] + 1 << " ";
    }
    cout << endl;

    return 0;
}