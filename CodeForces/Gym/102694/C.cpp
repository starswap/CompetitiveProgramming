#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int N;
int log_N;
vector<vector<int>> AL;
vector<int> d;
vector<vector<int>> bin_lift;

void root(int u, int p, int depth) {
    bin_lift[u][0] = p;
    d[u] = depth;
    for (int v : AL[u]) {
        if (v == p) continue;
        root(v, u, depth + 1);
    }
}

void preprocess() {
    log_N = ceil(log2(N)) + 2;
    bin_lift.assign(N, vector<int>(log_N, 0));
    d.assign(N, 0);
    root(0, 0, 0);
    for (int i = 1; i < log_N; ++i) {
        for (int n = 0; n < N; ++n) {
            bin_lift[n][i] = bin_lift[bin_lift[n][i - 1]][i - 1];
        }
    }
}

int lift(int u, int x) {
    for (int i = 0, mask = 1; i < log_N; mask <<= 1, ++i) {
        if (x & mask) u = bin_lift[u][i]; 
    }
    return u;
}

tuple<int, int, int> lca(int u, int v) {
    int u_dist = 0; 
    int v_dist = 0;
    if (d[v] < d[u]) {
        u_dist += d[u] - d[v];
        u = lift(u, d[u] - d[v]);
    } else {
        v_dist += d[v] - d[u];
        v = lift(v, d[v] - d[u]);
    }
    if (u == v) return make_tuple(u, u_dist, v_dist);

    for (int i = log_N - 1; i >= 0; --i) {
        if (bin_lift[u][i] != bin_lift[v][i]) {
            u = bin_lift[u][i];
            u_dist += (1 << i);
            v = bin_lift[v][i];
            v_dist += (1 << i);
        }
    }
    return make_tuple(bin_lift[u][0], u_dist + 1, v_dist + 1);
}

int query(int a, int b, int c) {
    auto [l, a_dist, b_dist] = lca(a, b);
    if (c >= a_dist + b_dist) { // succeeds
        return b; 
    } else if (c <= a_dist) { // runs out before reaching lca
        return lift(a, c);
    } else { // runs out on way down
        return lift(b, (a_dist + b_dist - c));
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    AL.assign(N, vector<int>());
    for (int n = 0; n < N - 1; ++n) {
        int u, v; cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    preprocess();
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int a, b, c;
        cin >> a >> b >> c;
        a--; b--;
        cout << query(a, b, c) + 1 << endl;
    }
    return 0;
}