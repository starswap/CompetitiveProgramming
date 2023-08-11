#include <bits/stdc++.h>
using namespace std;

const int INF = 10000000;

int N, M, K;
vector<int> list_bfs(vector<int> start_nodes, const vector<vector<int>> &AL) {
    vector<int> res(N, INF);
    vector<bool> visited(N, false);

    queue<pair<int, int>> q;
    for (int s : start_nodes) {
        q.emplace(s, 0);
        visited[s] = true;
    }

    while (q.size() > 0) {
        auto [u, d] = q.front(); q.pop();
        res[u] = d;
        for (int v : AL[u]) {
            if (!visited[v]) {
                q.emplace(v, d + 1);
                visited[v] = true;
            }
        }

    }

    return res;
}

int main() {
    cin >> N >> M >> K;
    
    vector<int> iron(M);
    vector<int> coal(K);
    vector<vector<int>> AL(N, vector<int>());
    vector<vector<int>> AL_rev(N, vector<int>());

    for (int m = 0; m < M; ++m) {
        cin >> iron[m];
        iron[m]--;
    }
    
    for (int k = 0; k < K; ++k) {
        cin >> coal[k];
        coal[k]--;
    }

    for (int i = 0; i < N; ++i) {
        int a; cin >> a;
        for (int j = 0; j < a; ++j) {
            int v;
            cin >> v;
            v--;
            AL[i].push_back(v);
            AL_rev[v].push_back(i); 
        }
    }

    vector<int> coal_dist = list_bfs(coal, AL_rev);
    vector<int> iron_dist = list_bfs(iron, AL_rev);
    vector<int> start_dist = list_bfs({0}, AL);
    
    int best = INF;
    for (int n = 0; n < N; ++n) {
        best = min(best, coal_dist[n] + iron_dist[n] + start_dist[n]);
    }

    if (best == INF) {
        cout << "impossible" << endl;
    } else {
        cout << best << endl;
    }

    return 0;
}