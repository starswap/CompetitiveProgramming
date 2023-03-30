#include <bits/stdc++.h>
using namespace std;

//All we need to do is fill up the edges list.

struct Edge {
    int from, to, capacity;
    double cost;

    Edge(int from, int to, int capacity, double cost):from(from),to(to),capacity(capacity),cost(cost) {}
};

vector<vector<int>> adj, capacity;
vector<vector<double>> cost;

const double EPS = 1e-7;
const double INF = 1e9;

void shortest_paths(int n, int v0, vector<double>& d, vector<int>& p) {
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
            if (capacity[u][v] > 0 && d[v] - (d[u] + cost[u][v]) > EPS) {
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

double min_cost_flow(int N, vector<Edge> edges, double K, int s, int t) {
    // N = number of nodes.
    // K = flow that we want
    // s = source
    // t = sink
    // Edges are directed.
    adj.assign(N, vector<int>());
    cost.assign(N, vector<double>(N, 0));
    capacity.assign(N, vector<int>(N, 0));
    for (Edge e : edges) {
        // cout << e.from << " " << " " << e.to << " " << e.cost << endl;
        adj[e.from].push_back(e.to);
        adj[e.to].push_back(e.from);
        cost[e.from][e.to] = e.cost;
        cost[e.to][e.from] = -e.cost;
        capacity[e.from][e.to] = e.capacity;
    }

    int flow = 0;
    double cost = 0;
    vector<double> d;
    vector<int> p;
    while (flow < K) {
        shortest_paths(N, s, d, p);
        if (fabs(d[t] - INF) < EPS)
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
        
        cost += static_cast<double>(f) * d[t];
        // cout << cost << endl;
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

struct point {
    double x, y, h;
    point():x(0),y(0),h(0) {}
};

double dist(point p1, point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dh = p1.h - p2.h;
    return hypotl(hypotl(dx,dy),dh);
}


int main() {
    int N, S, T;
    double Q;
    cin >> N >> S >> T >> Q;

    vector<point> pts(N);


    for (int n = 0 ; n < N ; ++n) {
        cin >> pts[n].x;
        cin >> pts[n].y;
        cin >> pts[n].h;
    }

    vector<int> springs, towns;
    for (int s = 0; s < S; ++s) {
        int i;
        cin >> i; i--;
        springs.push_back(i); 
    }

    for (int t = 0; t < T; ++t) {
        int i;
        cin >> i; i--;
        towns.push_back(i); 
    }

    // Super-Source to springs
    vector<Edge> edges;
    for (int ss : springs) {
        edges.push_back(Edge(0, ss + 2, 1, 0));
    }

    // hilltops to hilltops
    for (int i = 0 ; i < N ; ++i) {
        for (int j = 0 ; j < i; ++j) {
            double d = dist(pts[i], pts[j]);
            if (d - Q < EPS) {
                if (pts[i].h > pts[j].h) {
                    edges.push_back(Edge(i + 2, j + 2, S + T, d)); // aa
                }
                else if (pts[i].h < pts[j].h) {
                    edges.push_back(Edge(j + 2, i + 2, S + T, d)); //aa
                }
            }
        }
    }

    // villages to super-sink 
    for (int tt : towns) {
        edges.push_back(Edge(tt + 2, 1, 1, 0)); // aa
    }

    cout << fixed << setprecision(10);

    double ans = min_cost_flow(N + 2, edges, T, 0, 1);
    if (ans == -1) {
        cout << "IMPOSSIBLE" << endl;
    }
    else {
        cout << ans << endl;
    }

    return 0;    
}

