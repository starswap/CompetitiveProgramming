#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<bool> visited;
vector<vector<int>> components;
vector<int> assignments;
int ptr = 0;

int dfs_component_size(int u, int p) {
    visited[u] = true;
    int answer = 1; 
    for (int v : AL[u]) {
        if (v == p) continue;
        if (!visited[v]) {
            answer += dfs_component_size(v, u);
        }
    }
    components[ptr].push_back(u);
    return answer;
}

int main() {
    int N, M, K; cin >> N >> M >> K;
    vector<unordered_set<int>> i_is_followed_by(N);
    AL.assign(N, vector<int>());

    for (int m = 0; m < M; ++m) {
        int u, v; cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    visited.assign(N, false);


    int min_component = 1'000'000'00;
    components.assign(N, vector<int>());

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {
            int component_size = dfs_component_size(i, -1);
            min_component = min(component_size, min_component);
            ptr++;
        }
    }

    if (min_component < K) {
        cout << "impossible" << '\n';
    } else {
        assignments.assign(N, 0);

        for (const auto& component : components) {
            int game_vers = 1;
            for (const auto& u : component) {
                assignments[u] = game_vers;
                if (game_vers < K) {
                    game_vers++;
                }
            }
        }
        
        for (int game_vers : assignments) {
            cout << game_vers << ' ';
        }
        cout << '\n';

    }
    return 0;
}
