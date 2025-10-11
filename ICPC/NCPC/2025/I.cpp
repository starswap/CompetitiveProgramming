#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<unordered_set<int>> i_is_followed_by(N);

    for (int m = 0; m < M; ++m) {
        int u, v; cin >> u >> v;
        u--; v--;
        
        i_is_followed_by[v].insert(u);
    }

    for (int i = 0; i < N; ++i) {
        vector<int> to_remove;
        for (auto v : i_is_followed_by[i]) {
            if (i_is_followed_by[v].count(i)) {
                i_is_followed_by[v].erase(i);
                to_remove.push_back(v);
            }
        }
        for (int v : to_remove) {
            i_is_followed_by[i].erase(v);
        }
    }

    int best_degree = -1;
    int best_vertex = 0;
    for (int i = 0; i < N; ++i) {
        if ((int) i_is_followed_by[i].size() > best_degree) {
            best_degree = i_is_followed_by[i].size();
            best_vertex = i + 1;
        }
    }

    cout << best_vertex << " " << best_degree << '\n';
    return 0;
}
