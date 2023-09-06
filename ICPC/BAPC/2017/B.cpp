#include <bits/stdc++.h>
using namespace std;
#define double long double

const double INF = 1e20;
const double EPS = 1e-6;

typedef complex<double> C;
typedef vector<double> vd;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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
double norm_sq(vec v) {
    return v.x*v.x + v.y*v.y;
}

point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}                                                // return a new point

vec set_norm(const vec &v, double new_norm) {
    double new_dx = v.x*new_norm/(sqrt(norm_sq(v)));
    double new_dy = v.y*new_norm;
    return vec(new_dx, new_dy);
}

struct circle {
    point c;
    double r;
    circle(point c, double r):c(c), r(r) {};
    bool operator < (circle other) const {
        if (other.c == c)                  
            return r < other.r; 
        else 
            return other.c < c;          
 
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

bool isBetween(point a, point b, point pt) {
    return ((pt.x > a.x - EPS && pt.x - EPS < b.x) || (pt.x > b.x - EPS && pt.x - EPS < a.x)) && ((pt.y > a.y - EPS && pt.y - EPS < b.y) || (pt.y > b.y - EPS && pt.y - EPS < a.y));
}

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
    if (fabs(c1.c.x - c2.c.x) < EPS && fabs(c1.c.y - c2.c.y) < EPS) { // handle appropriately
        return vector<point>{};
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

int insideCircle(point p, circle c) {
  double dx = p.x-c.c.x;
  double dy = p.y-c.c.y;
  double Euc = dx*dx + dy*dy;
  double rSq = c.r*c.r; 
  return fabs(Euc - rSq) < EPS ? 0 : Euc > rSq ? 1 : -1;    // 1 = outside
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

bool can_go_directly(point p, point q, const vector<circle>& circles) {
    set<circle> curr_circle; 
    line l(p, q);

    vector<pair<point, circle>> intscts;
    for (const circle& c : circles) {
       if (insideCircle(p, c) < 1 && insideCircle(q, c) < 1) return true; // same circle
        vector<point> thisI = circleLineIntersection(c, l);
        for (point pt : thisI) {
            if (isBetween(p, q, pt)) {
                intscts.emplace_back(pt, c);
            }
        }
        switch (insideCircle(min(p, q), c)) {
            case(-1): curr_circle.insert(c); break;
            case(0): { // we are going to have one intersection here
                if (thisI.size() == 2) {
                    point otherInt = (thisI[0] == min(p, q)) ? thisI[1] : thisI[0];
                    if (otherInt < min(p, q)) {curr_circle.insert(c);} // if we are going towards the centre of this circle then we want that intersection to put us in (don't include), otherwise do.
                } else if (thisI.size() == 1) { // tangent. The 1 intersection should take us out.
                    curr_circle.insert(c);
                }
            }
        } 
    }

    sort(intscts.begin(), intscts.end());
    point last(-INF, -INF); 
    for (auto [pt, c] : intscts) {
        if (curr_circle.size() == 0 && !(last == pt)) return false;
        if (curr_circle.count(c)) {curr_circle.erase(c);}
        else {
            curr_circle.insert(c);
        }
        last = pt;
    }

    return curr_circle.size() > 0;
}

vector<vector<pair<int, double>>> AL;

bool dijkstra(int s, int t, int V, double &cost_total) {
    priority_queue<pair<double, int>> pq;
    vector<double> cost(V, INF);
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

    cost_total = cost[t];
    return (parent[t] != -1);
}


int main() {
    double x_b, y_b, x_m, y_m;
    cin >> x_b >> y_b >> x_m >> y_m;
    point b(x_b, y_b);
    point m(x_m, y_m);
    vector<circle> circles;
    int N;
    cin >> N;
    rep(i, 0, N) {
        double c_x, c_y, r;
        cin >> c_x >> c_y >> r;
        circles.push_back(circle(point(c_x, c_y), r));       
    }
    // cout << can_go_directly(b, m, circles);
    vector<point> pts({b, m});
    rep(i, 0, N) {
        rep(j, 0, i) {
            vector<point> ints = circleCircleIntersection(circles[i], circles[j]);
            for (point pt : ints) {pts.push_back(pt);}
        }
    }

    AL.assign(pts.size(), vector<pair<int, double>>());
    rep(i, 0, pts.size()) {
        rep(j, 0, i) {
            if (can_go_directly(pts[i], pts[j], circles)) {
                AL[i].emplace_back(j, dist(pts[i], pts[j]));
                AL[j].emplace_back(i, dist(pts[i], pts[j]));
            }
        }
    }
    
    double cost;
    if (dijkstra(0, 1, pts.size(), cost)) {
        cout << fixed << setprecision(10) << cost << endl; 
    } else {
        cout << "impossible" << endl;
    }
    
    
    return 0;
}