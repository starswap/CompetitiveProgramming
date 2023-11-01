#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int main() {
    int N, T, K;
    cin >> N >> T;

    map<pair<int, int>, vector<int>> times_for_pairs;
    vector<vector<int>> AL(N + 1);
    for (int t = 1; t <= T; ++t) {
        int m_i; cin >> m_i;
        for (int j = 0; j < m_i; ++j) {
            int vj, uj; cin >> vj >> uj;
            times_for_pairs[make_pair(min(vj, uj), max(vj, uj))].push_back(t);
            AL[vj].push_back(uj);
            AL[uj].push_back(vj);
        }
    }

    cin >> K;
    vector<int> a(K);

    vector<vector<int>> occurs_at_ind(T + 1); 
    for (int k = 0; k < K; ++k) {
        cin >> a[k];
        occurs_at_ind[a[k]].push_back(k + 1);
    }


    priority_queue<pair<double, int>> pq;
    vector<double> cost(N + 1, INF);
    
    cost[1] = 1;
    pq.emplace(-cost[1], 1); // time state when you are
    while (pq.size() > 0) {
        auto [dist, u] = pq.top(); pq.pop();
        dist = -dist;
        if (cost[u] != dist) continue;
        for (int v : AL[u]) {
            int best_idx = INF;
            for (int time : times_for_pairs[make_pair(min(u, v), max(u, v))]) {
                auto it = lower_bound(occurs_at_ind[time].begin(), occurs_at_ind[time].end(), dist);
                int next_time = INF;
                if (it != occurs_at_ind[time].end()) next_time = *it + 1;
                best_idx = min(best_idx, next_time);
            }
            if (best_idx < cost[v]) {
                cost[v] = best_idx;
                pq.emplace(-cost[v], v);
            }
        }
    }

    int ans;
    if (N == 1) ans = 1;
    else if (cost[N] == INF) ans = -1;
    else ans = cost[N] - 1;
    cout << ans << endl;
    return 0;
}

