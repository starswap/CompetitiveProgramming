#include <bits/stdc++.h>
using namespace std;

// BEGIN LIBRARY CODE

typedef long long LL;

struct Edge {
  int u, v;
  LL cap, flow;
  Edge() {}
  Edge(int u, int v, LL cap): u(u), v(v), cap(cap), flow(0) {}
};

struct Dinic {
  int N;
  vector<Edge> E;
  vector<vector<int>> g;
  vector<int> d, pt;
  
  Dinic(int N): N(N), E(0), g(N), d(N), pt(N) {}

  void AddEdge(int u, int v, LL cap) {
    if (u != v) {
      E.emplace_back(u, v, cap);
      g[u].emplace_back(E.size() - 1);
      E.emplace_back(v, u, 0);
      g[v].emplace_back(E.size() - 1);
    }
  }

  bool BFS(int S, int T) {
    queue<int> q({S});
    fill(d.begin(), d.end(), N + 1);
    d[S] = 0;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) break;
      for (int k: g[u]) {
        Edge &e = E[k];
        if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
          d[e.v] = d[e.u] + 1;
          q.emplace(e.v);
        }
      }
    }
    return d[T] != N + 1;
  }

  LL DFS(int u, int T, LL flow = -1) {
    if (u == T || flow == 0) return flow;
    for (int &i = pt[u]; i < g[u].size(); ++i) {
      Edge &e = E[g[u][i]];
      Edge &oe = E[g[u][i]^1];
      if (d[e.v] == d[e.u] + 1) {
        LL amt = e.cap - e.flow;
        if (flow != -1 && amt > flow) amt = flow;
        if (LL pushed = DFS(e.v, T, amt)) {
          e.flow += pushed;
          oe.flow -= pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  LL MaxFlow(int S, int T) {
    LL total = 0;
    while (BFS(S, T)) {
      fill(pt.begin(), pt.end(), 0);
      while (LL flow = DFS(S, T))
        total += flow;
    }
    return total;
  }
};

// END LIBRARY CODE

// BEGIN PROBLEM CODE
const int INF = 31'000'000;

int N, Q, S;

int get_node_queue(int q, int n) {
    return 2 + 2 * N * q + 2 * n;
}

int get_node_link(int link_no) {
    int max_below = get_node_queue(Q - 1, N - 1) + 1;
    return max_below + link_no + 1;
}

int main() {
  cin >> N >> Q >> S;

  // Get the queue that each sensor feeds into
  vector<int> sensor_map(S);
  for (int s = 0; s < S; ++s) {
      int m; cin >> m;
      sensor_map[s] = m - 1;
  }
  
  int source = 0;
  int sink = 1;
  int V = get_node_link(N - 1) + 1; // Number of nodes

  Dinic dinic(V);
  vector<vector<int>> capacity(V, vector<int>(V, 0)); // Adjacency Matrix for capacities

  // Get the size of each queue
  for (int q = 0; q < Q; ++q) {
      int size; cin >> size;
      for (int n = 0; n < N; ++n) {
          int node = get_node_queue(q, n);
          capacity[node][node + 1] = size;
      }
  }

  int target = 0; // amount of data we want to push all the way down to Earth
  for (int n = 0; n < N; ++n) {
      int d; cin >> d;
      capacity[get_node_link(n)][sink] = d;
      for (int s = 0; s < S; ++s) {    
          int q = sensor_map[s];
          int amt; cin >> amt;
          capacity[source][get_node_queue(q, n)] += amt;
          target += amt;
      }
  }

  for (int q = 0; q < Q; ++q) {
      for (int n = 0; n < N - 1; ++n) {
          int node1 = get_node_queue(q, n) + 1;
          int node2 = get_node_queue(q, n+1);
          capacity[node1][node2] = INF;
      }
  }

  for (int q = 0; q < Q; ++q) {
      for (int n = 0; n < N; ++n) {
          int node1 = get_node_queue(q, n) + 1;
          int node2 = get_node_link(n);
          capacity[node1][node2] = INF;
      }
  }

  for (int i = 0; i < V; ++i) {
      for (int j = 0; j < V; ++j) {
          if (capacity[i][j] > 0) {
              dinic.AddEdge(i, j, capacity[i][j]);
          }
      }
  }

  int mf = dinic.MaxFlow(source, sink);
  cout << ((target == mf) ? "possible" : "impossible") << endl;;  

  return 0;
}

// END PROBLEM CODE