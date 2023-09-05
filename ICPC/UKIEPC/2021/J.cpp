#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

const long long INF = 1000000000000000;
int V, E, P, T;
vector<vector<long long>> dist;
vector<vector<pair<int, long long>>> AL;
vector<vector<int>> DG_AL;

void compute_APSP() {
    for (int i = 0; i < V;++i) dist[i][i] = 0;
    for (int k = 0; k < V; ++k) {
        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                dist[u][v] = min(dist[u][v], dist[u][k] + dist[k][v]);
            }
        }
    }
}

int dijkstra_get_second_last(int s, int t) {
    priority_queue<pair<long long, int>> pq;
    vector<long long> cost(V, INF);
    vi parent(V, -1);

    cost[s] = 0;
    pq.emplace(-cost[s], s);
    while (pq.size() > 0) {
        auto [dist, u] = pq.top(); pq.pop();
        dist = -dist;
        if (cost[u] != dist) continue;

        for (auto &[v, edge_cost] : AL[u]) {
            if (dist + edge_cost < cost[v]) {
                cost[v] = dist + edge_cost;
                pq.emplace(-cost[v], v);
                parent[v] = u;
            }
        }
    }

    return parent[t];
}

set<int> first_approach_nodes;
void get_first_approach_nodes(int u, int first_cant_use, bool first) {
    if (first_approach_nodes.count(u)) return;
    else {
        first_approach_nodes.insert(u);
        for (auto [v, w] : AL[u]) {
            if (!(first && v == first_cant_use)) {
                get_first_approach_nodes(v, first_cant_use, false);
            }
        }
    }
}


enum State {
    UNSEEN,
    EXPLORING,
    DONE
};

vector<bool> dead_end_node;
vector<State> visited;
bool cycle_flag = false;
vector<long long> dp;
long long largest_score(int u) {
    if (visited[u] == EXPLORING) {
        cycle_flag = true; return -1;
    }
    else if (dp[u] != -1) { return dp[u]; }
    else if (dead_end_node[u]) {return 0;}
    else {
        visited[u] = EXPLORING;
        long long maxi = 0;
        for (int v : DG_AL[u]) {
            maxi = max(maxi, dist[u][v] + largest_score(v));
        }
        visited[u] = DONE;
        dp[u] = maxi;
        return maxi;
    }
}

void get_dead_end_nodes() {
    dead_end_node.assign(V, false);
    for (int u = 0; u < V; ++u) {
        dead_end_node[u] = AL[u].size() == 1;
    }
}

int main() {
    cin >> V >> E >> P >> T; P--; T--;
    dist.assign(V,vector<long long>(V, INF));
    AL.assign(V, vector<pair<int, long long>>());

    for (int e = 0; e < E; ++e) {
        int a, b, c;
        cin >> a >> b >> c; a--; b--;
        AL[a].emplace_back(b, c);
        AL[b].emplace_back(a, c);
        dist[a][b] = c;
        dist[b][a] = c;
    }

    compute_APSP();

    int sl = dijkstra_get_second_last(P, T);
    get_first_approach_nodes(T, sl, true);

    long long maxi = 0;
    for (int node : first_approach_nodes) {
        maxi = max(maxi, dist[T][node]);
    }

    vector<int> final_first_approach_nodes;
    for (int node : first_approach_nodes) {
        if (dist[T][node] == maxi && node != T) {
            final_first_approach_nodes.push_back(node);
        }
    }

    get_dead_end_nodes();

    DG_AL.assign(V, vector<int>());
    for (int u = 0; u < V; ++u) {
        long long maxi = *max_element(dist[u].begin(), dist[u].end());
        for (int v = 0; v < V; ++v) {
            if (dist[u][v] == maxi && !dead_end_node[u]) {
                DG_AL[u].push_back(v);
            }
        }
    }

    long long ans = 0;
    visited.assign(V, UNSEEN);
    dp.assign(V, -1);
    for (int u : final_first_approach_nodes) {
        ans = max(ans, largest_score(u) + dist[T][u]);
    }
    
    if (cycle_flag) {
        cout << "impossible" << endl;
    } else {
        cout << ans + dist[P][T] << endl;
    }

    return 0;
}