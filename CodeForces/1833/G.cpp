// global cut set
// go through all children
// return the number left to cut there
// if 1 and 1 - cut those and this.
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> AL;
vector<int> cut_edges;
bool poss = true;

int dfs(int u, int p, int n) {
    vector<int> kids;
    for (auto [v, n] : AL[u]) {
        if (v == p) continue;
        int d = dfs(v, u, n);
        if (d != 0) {
            kids.push_back(d);
        }
    }
    if (kids.size() == 0) {
        return 1;
    } else if (kids.size() == 1) {
        if (kids[0] == 2) {
            cut_edges.push_back(n);
            return 0;
        } else {
            return kids[0] + 1;
        }
    } else if (kids.size() == 2) {
        if (kids[0] == kids[1] && kids[1] == 1) {
            cut_edges.push_back(n);
            return 0;
        } else {
            poss = false;
            return 1;
        }
    } else { // >= 3
        poss = false;
        return 1;
    }
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        AL.assign(N, vector<pair<int, int>>());
        for (int n = 0; n < N - 1; ++n) {
            int u, v; cin >> u >> v; u--; v--;
            AL[u].emplace_back(v, n + 1);
            AL[v].emplace_back(u, n + 1);
        }
        cut_edges.clear();
        poss = true;
        if (dfs(0, -1, -1) == 0 && poss) {
            cut_edges.pop_back();
            cout << cut_edges.size() << endl;
            for (int i : cut_edges) {
                cout << i << " ";
            }
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}