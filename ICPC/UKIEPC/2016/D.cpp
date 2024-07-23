
#include <bits/stdc++.h>
using namespace std;
/* (Max Flow) (Network Flow) with Dinic Blocking Flow O(V^2 * E)*/
typedef long long LL;

const double EPS = 1e-7;
const int INF = 1e8;
const int TWO_LIGHT_COST = 43;
const int NOT_TWO_LIGHT_COST = 11;

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

double sq(double x) {
    return x * x;
}

int B, H, R, C; 
int hash_point(int r, int c) {
    return 2 + r * C + c;
}

int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

int main() {
    cin >> B >> H >> R >> C;
    vector<vector<int>> light_strengths(R, vector<int>(C, 0));
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            char ch; cin >> ch;
            light_strengths[r][c] = ch - '0';
        }
    }

    vector<vector<double>> light_levels(R, vector<double>(C, 0));
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            for (int i = 0; i < R; ++i) {
                for (int j = 0; j < C; ++j) {
                    light_levels[i][j] += light_strengths[r][c] / (sq(r - i) + sq(c - j) + H * H);
                }
            }
        }
    }
    set<int> dark_cells;
    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (light_levels[r][c] < B - EPS ) {
                dark_cells.insert(hash_point(r, c));
            }
        }
    }

    int N = 2 + R * C;
    int S = 0;
    int T = 1;
    Dinic dinic(N);

    for (int r = 0; r < R; ++r) {
        for (int c = 0; c < C; ++c) {
            if (r == 0 || r == R - 1 || c == 0 || c == C - 1) {
                dinic.AddEdge(hash_point(r, c), T, INF);
            }
            if (dark_cells.contains(hash_point(r, c))) {
                dinic.AddEdge(S, hash_point(r, c), INF);
            }
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < R && nc >= 0 && nc < C) {
                    if (!dark_cells.contains(hash_point(nr, nc)) && !dark_cells.contains(hash_point(r, c))) {
                        dinic.AddEdge(hash_point(nr, nc), hash_point(r, c), TWO_LIGHT_COST);
                    } else {
                        dinic.AddEdge(hash_point(nr, nc), hash_point(r, c), NOT_TWO_LIGHT_COST);
                    }
                }
            }
        }
    }
    
    cout << dinic.MaxFlow(S, T) << endl;

    return 0;
}