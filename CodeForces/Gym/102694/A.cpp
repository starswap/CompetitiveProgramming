#include <bits/stdc++.h>
using namespace std;

int N;
vector<vector<int>> AL;

pair<int, int> tree_diam(int u, int p) {
    int best_diam = 0;
    int best_path = 0;
    int second_best_path = 0;
    for (int c : AL[u]) {
        if (c == p) continue;
        auto [diam, path] = tree_diam(c, u);
        best_diam = max(best_diam, diam);
        if (path >= best_path) {second_best_path = best_path; best_path = path;}
        else if (path > second_best_path) {second_best_path = path;}
    } 
    best_diam = max(best_diam, best_path + second_best_path + 1);
    return make_pair(best_diam, best_path + 1);
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
    cout << 3 * (tree_diam(0, -1).first - 1) << endl;
    return 0;
}
