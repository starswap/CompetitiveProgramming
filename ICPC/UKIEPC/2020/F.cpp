#include <bits/stdc++.h>
using namespace std;

// method
//      Find shortest paths DAG
//          Do dijkstra, maintaining a parents list for each one. When you 
//      Find the shortest path costs as well
//      For each node with someone there
//          DFS from there to track all the places that they can go
//      For each node we could buy a group ticket from
//          Compute the cost that we can save. We can do this by computing the group ticket cost and then we also know the shortest path cost from this node to the end. So we just do total - number * og_cost + number * grp_cost; 

const long long INF = 1'000'000'000'000'000;

int N, M, P, G;
vector<int> V;
vector<vector<pair<int, int>>> AL;
vector<vector<int>> SP_DAG_AL;
vector<long long> dist;

void find_sp_dag() {
    priority_queue<pair<long long, int>> pq; // cost, node
    vector<vector<int>> parents(N,vector<int>());
    dist[0] = 0;

    pq.emplace(0, 0);
    while (pq.size() != 0) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost != -dist[u]) continue; // outdated;

        for (int parent : parents[u]) {
            SP_DAG_AL[u].push_back(parent);
        }

        for (const auto &[v, w] : AL[u]) {
            if (dist[u] + w < dist[v]) { // can relax;
                dist[v] = dist[u] + w; // do relax
                parents[v].clear();
                parents[v].push_back(u);
                pq.emplace(-dist[v], v);
            } else if (dist[u] + w == dist[v]) {
                parents[v].push_back(u);
            }
        }
    }
}

vector<set<int>> on_paths;
void dfs(int u, int t, int p) {
    if (!on_paths[u].count(t)) {
        on_paths[u].insert(t);
        for (int v : SP_DAG_AL[u]) {
            if (v != p) {
                dfs(v, t, u);
            }
        }
    }
}

void fill_on_paths() {
    for (int family_node : V) {
        dfs(family_node, family_node, -1);
    }
}

long long compute_answer() {
    long long max_saving = 0;
    for (int i = 0; i < N; ++i) {
        int n = 0;
        for (int v : V) {
            n += (on_paths[i].count(v));
        }
        long long saving = n * dist[i] - n * G; 
        max_saving = max(saving, max_saving);
    }

    long long ans = 0;
    for (int u : V) {
        ans += dist[u];
    }
    ans -= max_saving;
    return ans;
}

int main() {
    cin >> N >> M >> P >> G;
    V.assign(P, -1);

    for (int p = 0; p < P; ++p) {
        cin >> V[p];
        V[p]--;
    }

    AL.assign(N, vector<pair<int, int>>());
    SP_DAG_AL.assign(N, vector<int>());
    dist.assign(N, INF);
    on_paths.resize(N);

    for (int m = 0; m < M; ++m) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        AL[u].emplace_back(v, w);
        AL[v].emplace_back(u, w);
    } 

    find_sp_dag();
    fill_on_paths();
    long long ans = compute_answer();
    cout << ans << endl;

    return 0;
}