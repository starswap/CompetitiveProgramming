#include <bits/stdc++.h>
using namespace std;

// Min Cost Max Flow when cost is an integer
struct Edge
{
    int from, to, capacity, cost;
    Edge(int from, int to, int capacity, int cost):from(from),to(to),capacity(capacity),cost(cost) {}
};

vector<vector<int>> adj, cost, capacity;

const int INF = 1e9;

void shortest_paths(int n, int v0, vector<int>& d, vector<int>& p) {
    d.assign(n, INF);
    d[v0] = 0;
    vector<bool> inq(n, false);
    queue<int> q;
    q.push(v0);
    p.assign(n, -1);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int v : adj[u]) {
            if (capacity[u][v] > 0 && d[v] > d[u] + cost[u][v]) {
                d[v] = d[u] + cost[u][v];
                p[v] = u;
                if (!inq[v]) {
                    inq[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int min_cost_flow(int N, vector<Edge> edges, int K, int s, int t) {
    adj.assign(N, vector<int>());
    cost.assign(N, vector<int>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    int cost = 0;
    vector<int> d, p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (d[t] == INF)
            break;

        // find max flow on that path
        int f = K - flow;
        int cur = t;
        while (cur != s) {
            f = min(f, capacity[p[cur]][cur]);
            cur = p[cur];
        }

        // apply flow
        flow += f;
        cost += f * d[t];
        cur = t;
        while (cur != s) {
            capacity[p[cur]][cur] -= f;
            capacity[cur][p[cur]] += f;
            cur = p[cur];
        }
    }

    if (flow < K)
        return -1;
    else
        return cost;
}

int costFunc(int sr, int sc, int kr, int kc) {
    return abs(kr - sr) + abs(kc - sc);
}


int main() {
    int N;
    cin >> N;

    vector<Edge> edges;
    // 0 = source
    // 1 = sink
    // 2 - N + 1 = spaces
    // N + 2 - 2*n + 1 = kings

    // Source to spaces    
    for (int s = 0; s < N; ++s) {
        edges.push_back(Edge(0, 2 + s, 1, 0));
    }

    // kings to sink
    for (int k = 0; k < N; ++k) {
        edges.push_back(Edge(N + 2 + k, 1, 1, 0));
    }

    // spaces to kings
    for (int k = 0 ; k < N ; ++k) {
        int r, c;
        cin >> r >> c;
        r--; c--;
        for (int s = 0; s < N; ++s) {
            edges.push_back(Edge(2 + s, N + 2 + k, 1, costFunc(s, s, r, c)));
        }
    }

    cout << min_cost_flow(2 * N + 2, edges, N, 0, 1) << endl;
    return 0;
}