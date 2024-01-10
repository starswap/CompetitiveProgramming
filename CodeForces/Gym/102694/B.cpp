#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> AL;
set<int> furthest_nodes;
int diam = 0;

void bfs(int start_node) {
    vector<int> dist(N, -1);
    dist[start_node] = 0;
    queue<pair<int, int>> q;
    q.emplace(start_node, 0);
    while (!q.empty()) {
        auto [u, d] = q.front(); q.pop();
        for (int v : AL[u]) {
            if (dist[v] == -1) {
                dist[v] = d + 1;
                q.emplace(v, d + 1);
            }
        }
    }
    int maxi = 0;
    for (int d : dist) {maxi = max(maxi, d);}
    for (int i = 0; i < N; ++i) {
        if (dist[i] == maxi) {
            furthest_nodes.insert(i);
        }
    }
    diam = maxi;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    AL.assign(N, vector<int>());
    for (int i = 0; i < N - 1; ++i) {
        int u, v; cin >> u >> v; u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    bfs(0);
    bfs(*furthest_nodes.begin());

    for (int i = 0; i < N; ++i) {
        if (furthest_nodes.count(i)) {
            cout << diam + 1 << endl;
        }
        else {
            cout << diam << endl;
        }
    }
    return 0;
}
