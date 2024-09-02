#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<vector<int>> AL;

const int MAX_K = 20;
int DP[(1 << MAX_K)];
map<pair<int, int>, int> edge_covers;
const int INF = 1e9+7;

bool compute_path(int u, int v, int i, int p, int k) {
    if (v == i) return true;
    if (i != v) {
        for (int j : AL[i]) {
            if (j == p) continue;
            if (compute_path(u, v, j, i, k)) {
                edge_covers[{min(i, j), max(i, j)}] |= (1 << k);
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        AL.assign(N, vector<int>());
        for (int n = 0; n < N - 1; ++n) {
            int u, v; cin >> u >> v;
            u--; v--;
            AL[u].push_back(v);
            AL[v].push_back(u);
        }

        int K; cin >> K;
        vector<pair<int, int>> pairs(K);
        edge_covers.clear();
        for (int k = 0; k < K; ++k) {
            cin >> pairs[k].first;
            cin >> pairs[k].second;
            pairs[k].first--;
            pairs[k].second--;
            compute_path(pairs[k].first, pairs[k].second, pairs[k].first, -1, k);
        }

        set<int> vs;
        for (const auto &[k, v] : edge_covers) {
            vs.insert(v);
        }

        for (int i = 0; i < (1 << K); ++i) {
            DP[i] = INF;
        }

        queue<int> q;
        q.push(0);
        DP[0] = 0;
        vector<int> seen((1 << K), false);
        seen[0] = true;
        while (!q.empty()) {
            int f = q.front(); q.pop();

            for (int s : vs) {
                DP[f | s] = min(DP[f | s], DP[f] + 1);
            }

            for (int t = 0; t < K; ++t) {
                int m = (f | (1 << t));
                if ((f & (1 << t)) == 0 && !seen[m]) {
                    seen[m] = true;
                    q.push(m);
                }
            }
        }

        cout << DP[(1 << K) - 1] << endl;
    }
    return 0;
}