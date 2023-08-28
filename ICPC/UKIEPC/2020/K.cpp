#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, long long>>> AL;
vector<long long> d;
vector<tuple<int, int, long long>> EL;
vector<long long> cycle_values;
void dfs(int u, long long w) {
    if (d[u] == -1) {
        d[u] = w;
        for (auto &[v, w2] : AL[u]) {
            dfs(v, w ^ w2);
        }
    }
}

long long query(int u, int v) {
    long long acc = d[u] ^ d[v];
    for (int bit = 62; bit >= 0; bit--) {
        long long mask = (1LL << bit);
        if (acc & mask) {
            for (long long c_j : cycle_values) {
                if (c_j & mask && c_j < (mask << 1)) { // msb
                    acc ^= c_j;
                }
            }
        }
    }
    return acc;
}

int main() {
    int V, E, Q;
    cin >> V >> E >> Q;
    AL.assign(V, vector<pair<int, long long>>());
    for (int e = 0; e < E; ++e) {
        int x, y;
        long long w;
        cin >> x >> y >> w;
        x--;
        y--;
        AL[x].emplace_back(y, w);
        AL[y].emplace_back(x, w);
        EL.emplace_back(x, y, w);
    }

    d.assign(V, -1);
    dfs(0, 0);
    for (auto &[u, v, w] : EL) {
        cycle_values.push_back(w ^ d[u] ^ d[v]);
    }

    for (int bit = 62; bit >= 0; bit--) {
        long long c_1 = 0;
        long long mask = (1LL << bit);
        for (long long &c_j : cycle_values) {
            if (c_j & mask && c_j < (mask << 1)) { // msb
                if (c_1 == 0) {
                    c_1 = c_j;
                } else {
                    c_j ^= c_1;
                }
            }
        }
    }

    vector<long long> cycle_values_no_zeros;
    for (long long x : cycle_values) {
        if (x != 0) {
            cycle_values_no_zeros.push_back(x);
        }
    }

    cycle_values = cycle_values_no_zeros;

    for (int q = 0; q < Q; ++q) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << query(a, b) << endl;
    }

}