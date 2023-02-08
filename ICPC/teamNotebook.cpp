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