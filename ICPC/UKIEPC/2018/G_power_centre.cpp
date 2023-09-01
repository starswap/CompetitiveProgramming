#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-12;
const double INF = 1e30;

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator < (point other) const {          // override < operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
  }
  point operator + (point other) const {
    return point(x + other.x, y + other.y);
  }
  point operator - (point other) const {
    return point(x - other.x, y - other.y);
  }
};

struct circle {
    point c;
    double r;
    circle(point c, double r):c(c), r(r) {};
};

struct vec {
  double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
  vec(point p): x(p.x), y(p.y) {}
  vec(const point&a, const point &b):x(b.x - a.x), y(b.y - a.y) {}
  vec operator - (vec other) const {
    return vec(x - other.x, y - other.y);
  }
  vec operator + (vec other) const {
    return vec(x + other.x, y + other.y);
  }
};

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }
double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(cross(vec(p, q), vec(p, r))) < EPS;
}

point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}               

bool power_centre(circle c_a, circle c_b, circle c_c, point &target) {
    vec a(c_a.c); vec b(c_b.c); vec c(c_c.c);
    b = b - a;
    c = c - a;
    if (fabs(cross(b,c)) < EPS) { // collinearity check
        return false;
    } else {
        double u = c_a.r*c_a.r-c_c.r*c_c.r+dot(c,c);
        double v = c_a.r*c_a.r-c_b.r*c_b.r+dot(b,b);
        double w = cross(c,b)*2;
        target = translate(point((b.y*u-c.y*v)/w, -(b.x*u-c.x*v)/w), a);
        return true;
    }
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

vector<point> key_nodes;
vector<int> radii;
int n;

vector<vector<vector<int>>> get_partitions(const vector<int>& vv, unsigned int i, int p) {
    if (i == vv.size()) {
        vector<vector<int>> single_partition(p, vector<int>());
        return vector<vector<vector<int>>>(1, single_partition);
    } else {
        vector<vector<vector<int>>> sub_partitions = get_partitions(vv, i + 1, p);
        vector<vector<vector<int>>> new_partitions;
        for (auto partition : sub_partitions) {
            for (int loc = 0; loc < p; ++loc) {
                partition[loc].push_back(vv[i]);
                new_partitions.push_back(partition);
                partition[loc].pop_back();
            }
        }
        return new_partitions;
    }
}

int insideCircle(point p, circle c) {
  double dx = p.x-c.c.x;
  double dy = p.y-c.c.y;
  double Euc = dx*dx + dy*dy;
  double rSq = c.r*c.r; 
  return fabs(Euc - rSq) < EPS ? 0 : Euc > rSq ? 1 : -1;    // outside/border/inside
}

bool solve() {
    if (collinear(key_nodes[0], key_nodes[1], key_nodes[2])) {
        double maxi = max(dist(key_nodes[0], key_nodes[1]), dist(key_nodes[1], key_nodes[2]));
        maxi = max(maxi, dist(key_nodes[0], key_nodes[2]));
        int r_sum = reduce(radii.begin(), radii.end());
        return (r_sum * 2 > maxi - EPS);
    } else {
        auto maxi = max_element(radii.begin(), radii.end());
        int T = *maxi;
        radii.erase(maxi);
        vector<vector<vector<int>>> partitions = get_partitions(radii, 0, 3);

        for (auto partition : partitions) {
            int r1 = reduce(partition[0].begin(), partition[0].end()) * 2 + T;
            int r2 = reduce(partition[1].begin(), partition[1].end()) * 2 + T;
            int r3 = reduce(partition[2].begin(), partition[2].end()) * 2 + T;
            circle c1(key_nodes[0], r1);
            circle c2(key_nodes[1], r2);
            circle c3(key_nodes[2], r3);

            point centre;

            if (power_centre(c1, c2, c3, centre) && insideCircle(centre, c1) < 1  && insideCircle(centre, c2) < 1 && insideCircle(centre, c3) < 1) {
                return true;
            }
        }
        return false;
    }
}

int main() {

    for (int i = 0; i < 3; ++i) {
        int x, y;
        cin >> x >> y;
        key_nodes.emplace_back(x, y);
    }
    cin >> n;
    radii.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> radii[i];
    }

    cout << (solve() ? "possible" : "impossible") << endl;    
    return 0;
}