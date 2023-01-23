#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<vector<int>> ALExtra;
vector<tuple<int, int, int>> EL;

int N, M;

vector<int> post_order;
vector<bool> visited;
void dfs1(int u) {
    if (!visited[u]) {
        visited[u] = true;
        for (int v : ALExtra[u]) {
            dfs1(v);
        }
        post_order.push_back(u);
    }
}

bool can(int m) {
    ALExtra = AL;
    for (auto &[u, v, w] : EL) {
        if (w <= m) {
            ALExtra[v].push_back(u);
        }
    }
    post_order.clear();
    visited.assign(N, false);
    for (int u = 0; u < N; ++u) {
        if (!visited[u]) {
            dfs1(u);
        }
    }
    
    reverse(post_order.begin(), post_order.end());
    visited.assign(N, false);
    
    dfs1(post_order[0]);
    for (int u = 0; u < N; ++u) {
        if (visited[u] == false) return false;
    }
    return true;
}

int solve() {
    int L = -1; // not included
    int R = 1000000000;  // included
    
    while (R - L > 1) {
        int M = (L + R) / 2;
        if (can(M)) {
            R = M;
        }
        else {
            L = M;
        }
    } 

    return can(R) ? R : -1;
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        cin >> M;
        AL.assign(N, vector<int>());
        EL.clear();

        for (int m = 0; m < M; m++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--; v--;
            AL[u].push_back(v);
            EL.emplace_back(u, v, w);
        }

        cout << solve() << endl;
 
    } 
    return 0;
}