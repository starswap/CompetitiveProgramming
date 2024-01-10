#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
int log_N;
const int INF = 1000000001;
vector<vector<pair<int, int>>> AL;
vector<int> d;
vector<vector<int>> bin_lift;
vector<vector<int>> bin_lift_min_weight;

void root(int u, int p, int depth) {
    bin_lift[u][0] = p;
    d[u] = depth;
    for (auto[v, w] : AL[u]) {
        if (v == p) continue;
        bin_lift_min_weight[v][0] = w;
        root(v, u, depth + 1);
    }
}

void preprocess() {
    log_N = ceil(log2(N)) + 2;
    bin_lift.assign(N, vector<int>(log_N, 0));
    bin_lift_min_weight.assign(N, vector<int>(log_N, 0));
    d.assign(N, 0);
    root(0, 0, 0);
    for (int i = 1; i < log_N; ++i) {
        for (int n = 0; n < N; ++n) {
            bin_lift[n][i] = bin_lift[bin_lift[n][i - 1]][i - 1];
            bin_lift_min_weight[n][i] = min(bin_lift_min_weight[n][i - 1], bin_lift_min_weight[bin_lift[n][i - 1]][i - 1]);
        }
    }
}

pair<int, int> lift(int u, int x) {
    int min_weight = INF;
    for (int i = 0, mask = 1; i < log_N; mask <<= 1, ++i) {
        if (x & mask) {
            min_weight = min(min_weight, bin_lift_min_weight[u][i]);
            u = bin_lift[u][i]; 
        }
    }
    return make_pair(u, min_weight);
}

int lca_min_weight(int u, int v) {
    int min_weight = INF;
    if (d[v] < d[u]) {
        tie(u, min_weight) = lift(u, d[u] - d[v]);
    } else {
        tie(v, min_weight) = lift(v, d[v] - d[u]);
    }
    if (u == v) return min_weight;

    for (int i = log_N - 1; i >= 0; --i) {
        if (bin_lift[u][i] != bin_lift[v][i]) {
            min_weight = min(min_weight, bin_lift_min_weight[u][i]);
            u = bin_lift[u][i];
            min_weight = min(min_weight, bin_lift_min_weight[v][i]);
            v = bin_lift[v][i];
        }
    }
    min_weight = min(min_weight, bin_lift_min_weight[u][0]);
    min_weight = min(min_weight, bin_lift_min_weight[v][0]);
    return min_weight;
}

int query(int a, int b) {
    return lca_min_weight(a, b);
}

int main() {
    int M;
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M;
    AL.assign(N, vector<pair<int, int>>());
    for (int n = 0; n < N - 1; ++n) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
    }
    preprocess();
    int Q;
    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << query(a, b) << endl;
    }
    return 0;
}
