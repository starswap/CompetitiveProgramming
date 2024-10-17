#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<int> targets;
map<pair<int, string>, int> AL_string;
map<int, int> target_set;
vector<vector<int>> AL;
int V = 0;
ll best = 1'000'000'000'000'000;

pair<ll, ll> dfs(int u, int p) {
    int is_target = target_set[u];
    ll et = 0;
    targets[u] = is_target;
    for (int v : AL[u]) {
        if (v == p) continue;
        auto [edge_trav, ls] = dfs(v, u);
        et += edge_trav + ls;
        targets[u] += ls;
    }
    return make_pair(et, targets[u]);
}

void dfs2(int u, int p, ll par) {
    if (!target_set[u]) {
        ll curr = par + targets[0] - 2LL * targets[u];
        best = min(best, curr);
        for (int v : AL[u]) {
            if (v == p) continue;
            dfs2(v, u, curr);
        }
    }
}

int main() {
    int N; cin >> N;
    for (int n = 0; n < N; ++n) {
        string path;
        cin >> path;
        path += '/';

        int last_slash = 0;
        int curr = 0;
        for (int i = 1; i < (int) path.size(); ++i) {
            if (path[i] == '/') {
                string key = path.substr(last_slash + 1, i - last_slash - 1);
                pair<int, string> edge(curr, key);
                if (!AL_string.count(edge)) {
                    AL_string[edge] = ++V;
                    curr = V;
                } else {
                    curr = AL_string[edge];
                }
                last_slash = i;
            }
        }
        target_set[curr]++;
    }

    AL.resize(V + 1);
    targets.resize(V + 1);

    for (const auto& [p, v] : AL_string) {
        const auto& [u, str] = p;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    auto [root_sc, root_leaves] = dfs(0, -1);   
    best = root_sc;
    for (int v : AL[0]) {
        dfs2(v, 0, root_sc);
    }

    cout << best << endl;
    return 0;
}