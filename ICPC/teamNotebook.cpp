#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
const double INF = 1e19;

/* GEOMETRY */
struct point {
    double x, y;
    point():x(0),y(0) {};
    point(double ax, double ay):x(ax),y(ay) {};
};

struct line {
    point a, b;
    line(point aa, point ab):a(aa),b(ab) {}; 
};

struct vec {
    double dx, dy;
    vec(point a, point b):dx(b.x - a.x),dy(b.y - a.y) {}
};

bool operator < (point a, point b) {
    if (a.x == b.x) return a.y < b.y;
    else return a.x < b.x;
}

typedef vector<point> polygon;

double norm(vec a) {return sqrt(a.dx*a.dx + a.dy*a.dy);}

double cross(vec a, vec b) {return a.dx*b.dy - a.dy*b.dx;}

double dot(vec a, vec b) {return a.dx*b.dx + a.dy*b.dy;}

double ptToPt(point a, point b) {return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));}

double ptToLine(point p, line l) {
    double d1 = dot(vec(l.a, p), vec(l.b, l.a)) / norm(vec(l.b, l.a));
    double ax = ptToPt(l.a, p);
    return sqrt(ax*ax - d1*d1);
}

bool ccw(point x, point y, point z) { return cross(vec(x,y),vec(y,z)) > EPS; }

vector<point> CH(vector<point> &pts) {
    int n = pts.size();
    vector<point> H(n + 1);
    int k = 0;

    sort(pts.begin(), pts.end());
    for (int i = 0; i < n; ++i) {
        while ((k >= 2) && !ccw(H[k-2], H[k-1], pts[i])) k--;
        H[k] = pts[i]; k++; 
    }

    for (int t = k + 1, i = n - 2; i >= 0; --i) {
        while ((k >= t) && !ccw(H[k-2], H[k-1], pts[i])) k--;
        H[k] = pts[i]; k++; 
    }

    H.resize(k);
    return H;
}

double area(const vector<point> &pts) {
    // Shoelace Formula
    double area = 0;
    for (int i = 0; i < pts.size() - 1; ++ i) {
        area += (pts[i].x) * (pts[i+1].y);
        area -= (pts[i+1].x) * (pts[i].y);
    }
    return area / 2;
}

double ptToLineSegment(point p, line l) {
    double da = dot(vec(l.a, p), vec(l.a, l.b));
    double db = dot(vec(l.b, p), vec(l.b, l.a));

    if (da > EPS && db > EPS) { // in range
        double d1 = da / norm(vec(l.b, l.a));
        double ax = ptToPt(l.a, p);
        return sqrt(ax*ax - d1*d1);
    }
    else { // out of range
        return min(ptToPt(l.a, p), ptToPt(l.b, p));
    }
}

bool pointInPolygon(point p, polygon poly) {
    bool count = false;
    for (int i = 0; i < poly.size() - 1; ++i) {
        if ((poly[i].y > p.y != poly[i + 1].y > p.y)) {//  && // horizontal ray; check it lies in the vertical bounds of the side
            if (p.x < EPS + (poly[i+1].x - poly[i].x) / (poly[i+1].y - poly[i].y) * (p.y - poly[i].y) + poly[i].x) {
                count = !count;
            }
        }
    }
    return count;
}


/* DP */
// LIS
vector<int> p;
int endPoint;
vector<int> nums;

void printLis(int endPointL) {
  if (endPointL == -1) return;
  printLis(p[endPointL]);
  cout << nums[endPointL];
  if (endPoint == endPointL)
    cout << endl;
  else
    cout << " ";
}


int k = 0;
p.assign(n,0);
vector<int> endValLengthL(n,0);
vector<int> endILengthL(n,0);

for (int i=0;i<n;++i) {
    int ind = lower_bound(endValLengthL.begin(),endValLengthL.begin()+k,nums[i]) - endValLengthL.begin(); //first index in array where the value is greater than this one, or we need to place a new one.
    endValLengthL[ind] = nums[i];
    endILengthL[ind] = i;
    if (ind == k) {
        k++;
        endPoint = i;
    }
    if (ind == k-1) 
    endPoint = i;
    p[i] = (ind == 0) ? -1 : endILengthL[ind-1];      
}
// length = k
printLis(endPoint);


/* SYNTAX */

// Lambda syntax to produce normal ascending sort order.
sort(liz.begin(), liz.end(), [v](point a, point b) {
	return a < b;
});

// Custom comparator lambda syntax
auto comp = [polys] (int n) { return area(polys[n]) < area(polys[n]);};
set<int, decltype(comp)> containingPolygons(comp);


/*Network Flow*/
// Push-Relabel algorithm
int V;
vector<vector<int>> capacity, flow;
vector<int> height, excess;

void push(int u, int v) {
    int d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
}

void relabel(int u) {
    int d = INF;
    for (int i = 0; i < V; i++) {
        if (capacity[u][i] - flow[u][i] > 0)
            d = min(d, height[i]);
    }
    if (d < INF)
        height[u] = d + 1;
}

vector<int> find_max_height_vertices(int s, int t) {
    vector<int> max_height;
    for (int i = 0; i < V; i++) {
        if (i != s && i != t && excess[i] > 0) {
            if (!max_height.empty() && height[i] > height[max_height[0]])
                max_height.clear();
            if (max_height.empty() || height[i] == height[max_height[0]])
                max_height.push_back(i);
        }
    }
    return max_height;
}

int max_flow(int s, int t) {
    height.assign(V, 0);
    height[s] = V;
    flow.assign(V, vector<int>(V, 0));
    excess.assign(V, 0);
    excess[s] = INF;
    for (int i = 0; i < V; i++) {
        if (i != s)
            push(s, i);
    }

    vector<int> current;
    while (!(current = find_max_height_vertices(s, t)).empty()) {
        for (int i : current) {
            bool pushed = false;
            for (int j = 0; j < V && excess[i]; j++) {
                if (capacity[i][j] - flow[i][j] > 0 && height[i] == height[j] + 1) {
                    push(i, j);
                    pushed = true;
                }
            }
            if (!pushed) {
                relabel(i);
                break;
            }
        }
    }

    int max_flow = 0;
    for (int i = 0; i < V; i++)
        max_flow += flow[i][t];
    return max_flow;
}





// Minimum Cost Max Flow code for cost as double
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
        cout << cost << endl;
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

// PBDS
#include <bits/extc++.h>
using namespace __gnu_pbds;

#define ordered_set tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update>
order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero). //This is what you need 

// MOD Qs
// C++ Mod (-3) % 5 = -3

// Fill a DP table
fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(dp[0][0][0][0]), -1);

def KMP(STRING, PATTERN):

    lps = [0 for i in range(len(PATTERN))]
    i = 0
    j = 1
    while j < len(lps): # O(M)
        if PATTERN[i] != PATTERN[j]:
            j += 1
            if i > 0:
                i = lps[i-1]
        else:
            lps[j] = i+1
            i += 1
            j += 1

    s = 0
    p = 0
    while s < len(STRING):
        if STRING[s] != PATTERN[p]:
            p = lps[p-1]
            if p == 0:
                s += 1    
        else:
            s += 1
            p += 1
        
        if p == len(lps):
            return True
        
    return False
