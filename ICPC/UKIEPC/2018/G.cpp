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
};

struct line { 
    double a, b, c;
    line() {a = b = c = 0.0;}
    line(double a, double b, double c):a(a), b(b), c(c) {}
    line(point p1, point p2) {
        if (fabs(p1.x-p2.x) < EPS) {
            a = 1.0; b = 0.0; c = -p1.x;
        }
        else {
            a = -(p1.y-p2.y) / (p1.x-p2.x);
            b = 1.0;
            c = -(a*p1.x) - p1.y;      // NOTE: b always 1.0
        }
    }
    line(point p1, double m) {
        a = -m; b = 1; c = -((a * p1.x) + (b * p1.y));
    }
    double get_m() { return (b == 0) ? INF : -a / b;} // NOTE: may return INF
    double get_c() { return (b == 0) ? INF : -c / b;} // NOTE: may return INF
    double get_y(double x) {
        return get_m() * x + get_c();
    }

};

struct circle {
    point c;
    double r;
    circle(point c, double r):c(c), r(r) {};
};

vector<point> circleLineIntersection(circle c, line l) {
    double r = c.r;
    double cx = c.c.x;
    double cy = c.c.y;
    
    l.c += l.a * cx + l.b * cy;

    double x0 = -l.a*l.c/(l.a*l.a+l.b*l.b), y0 = -l.b*l.c/(l.a*l.a+l.b*l.b);
    if (l.c*l.c > r*r*(l.a*l.a+l.b*l.b)+EPS) { return {}; }
    else if (fabs (l.c*l.c - r*r*(l.a*l.a+l.b*l.b)) < EPS) { return vector<point>{point(x0 + cx, y0 + cy)}; }
    else {
        double d = r*r - l.c*l.c/(l.a*l.a+l.b*l.b);
        double mult = sqrt(d / (l.a*l.a+l.b*l.b));
        double ax, ay, bx, by;
        ax = x0 + l.b * mult;
        bx = x0 - l.b * mult;
        ay = y0 - l.a * mult;
        by = y0 + l.a * mult;
        point p1 = point(ax + cx, ay + cy);
        point p2 = point(bx + cx, by + cy);
        return ((p1 == p2) ? (vector<point>{p1}) : (vector<point>{p1, p2})); 
    }
}

vector<point> circleCircleIntersection(circle c1, circle c2) {
    if (fabs(c1.c.x - c2.c.x) < EPS && fabs(c2.c.y - c2.c.y) < EPS) { // handle appropriately
        return vector<point>{c1.c};
    } 
    else {  
        double old_x1 = c1.c.x;
        double old_y1 = c1.c.y;

        c1.c.x -= old_x1;
        c1.c.y -= old_y1;

        c2.c.x -= old_x1;
        c2.c.y -= old_y1;

        double x2 = c2.c.x;
        double y2 = c2.c.y;
        double r1 = c1.r;
        double r2 = c2.r;

        line corresponding(-2 * x2, -2 * y2, x2 * x2 + y2 * y2 + r1 * r1 - r2 * r2);
        vector<point> trans_int = circleLineIntersection(c1, corresponding);
        for (point &p : trans_int) {
            p.x += old_x1;
            p.y += old_y1;
        }
        return trans_int;
    }
}

point point_avg(vector<point> vp) {
    double x = 0;
    double y = 0;
    for (point p : vp) {x += p.x; y += p.y;}
    x /= vp.size();
    y /= vp.size();
    return point(x,y);
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

        vector<point> ints1 = circleCircleIntersection(c1, c2);
        vector<point> ints2 = circleCircleIntersection(c2, c3);
        vector<point> ints3 = circleCircleIntersection(c3, c1);
        ints1.insert(ints1.end(), ints2.begin(), ints2.end());
        ints1.insert(ints1.end(), ints3.begin(), ints3.end());
        for (int i = 0; i < ints1.size(); ++i) {
            for (int j = 0; j < ints1.size(); ++j) {
                for (int k = 0; k < ints1.size(); ++k) {
                    point avg = point_avg({ints1[i], ints1[j], ints1[k]});
                    if (ints1.size() > 0 && insideCircle(avg, c1) < 1  && insideCircle(avg, c2) < 1 && insideCircle(avg, c3) < 1) {
                        return true;
                    }
                }
            } 
        }

    }
    return false;
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