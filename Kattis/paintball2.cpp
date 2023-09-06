#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef vector<double> vd;

const double EPS = 1e-8;
const double INF = 1e25;

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

struct circle {
    point c;
    double r;
    circle(point c, double r):c(c), r(r) {};
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
        if (fabs(c1.r - c2.r) < EPS) {
            return vector<point>{c1.c};
        } else {
            return vector<point>{};
        }
        
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

class UnionFind {                                // OOP style
public:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
  
  vd setMinX;
  vd setMaxX;
  vd setMinY;
  vd setMaxY;
  vd lowInt;
  vd farLowInt;

  UnionFind(int N, vd AsetMinX, vd AsetMaxX, vd AsetMinY, vd AsetMaxY, vd AlowInt, vd AfarLowInt):setMinX(AsetMinX), setMaxX(AsetMaxX), setMinY(AsetMinY), setMaxY(AsetMaxY), lowInt(AlowInt), farLowInt(AfarLowInt) {
    p.assign(N, 0); for (int i = 0; i < N; ++i) p[i] = i;
    rank.assign(N, 0);                           // optional speedup
    setSize.assign(N, 1);                        // optional feature
    numSets = N;                                 // optional feature
  }

  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }

  int numDisjointSets() { return numSets; }      // optional
  int sizeOfSet(int i) { return setSize[findSet(i)]; } // optional

  void unionSet(int i, int j) {
    if (isSameSet(i, j)) return;                 // i and j are in same set
    int x = findSet(i), y = findSet(j);          // find both rep items
    if (rank[x] > rank[y]) swap(x, y);           // keep x 'shorter' than y
    p[x] = y;                                    // set x under y
    if (rank[x] == rank[y]) ++rank[y];           // optional speedup
    setSize[y] += setSize[x];                    // combine set sizes at y
    setMinX[y] = min(setMinX[x], setMinX[y]);
    setMaxX[y] = max(setMaxX[x], setMaxX[y]);
    setMinY[y] = min(setMinY[x], setMinY[y]);
    setMaxY[y] = max(setMaxY[x], setMaxY[y]);
    lowInt[y] = min(lowInt[x], lowInt[y]);
    farLowInt[y] = min(farLowInt[x], farLowInt[y]);
    --numSets;                                   // a union reduces numSets
  }
};

int main() {
    int N; cin >> N;
    vector<circle> circles;
    for (int i = 0; i < N; ++i) {
        double x, y, r;
        cin >> x >> y >> r;
        circles.push_back(circle(point(x, y), r));
    }
    
    vd setMinX(N, 0);
    vd setMaxX(N, 0);
    vd setMaxY(N, 0);
    vd setMinY(N, 0);
    vd lowInt(N, 1000);
    vd farLowInt(N, 1000);

    for (int i=0 ; i< N; ++i) {
        setMinX[i] = circles[i].c.x - circles[i].r;
        setMaxX[i] = circles[i].c.x + circles[i].r;
        setMinY[i] = circles[i].c.y - circles[i].r; 
        setMaxY[i] = circles[i].c.y + circles[i].r;
        vector<point> ints = circleLineIntersection(circles[i], line(point(0, 0), point(0, 1000)));
        vector<double> intsD;
        for (point p : ints) {
            intsD.push_back(p.y);
        }
        if (ints.size() > 0) {
            lowInt[i] = *min_element(intsD.begin(), intsD.end());
        }

        ints = circleLineIntersection(circles[i], line(point(1000, 0), point(1000, 1000)));
        intsD.clear();
        for (point p : ints) {
            intsD.push_back(p.y);
        }
        if (ints.size() > 0) {
            farLowInt[i] = *min_element(intsD.begin(), intsD.end());
        }
    }

    UnionFind ufds(N, setMinX, setMaxX, setMinY, setMaxY, lowInt, farLowInt);

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (circleCircleIntersection(circles[i], circles[j]).size() > 0) {
                ufds.unionSet(i, j);
            }
        }
    }

    bool impossible = false;
    for (int i = 0; i < N; ++i) {
        if (ufds.setMaxY[i] >= 1000 && ufds.setMinY[i] <= 0) impossible = true;
    }

    if (impossible) {
        cout << "IMPOSSIBLE" << endl;
    } else {
        double inY = 1000, outY = 1000;
        for (int i = 0; i < N; ++i) {
           if (ufds.setMaxY[i] >= 1000 && ufds.setMinX[i] <= 0) { // blocking
                inY = min(inY, ufds.lowInt[i]);
           }

           if (ufds.setMaxY[i] >= 1000 && ufds.setMaxX[i] >= 1000) { // blocking
                outY = min(outY, ufds.farLowInt[i]);
           }
        }
        cout << fixed << setprecision(2) << 0.0 << " " << inY  << " " << 1000.0 << " " << outY << endl; 
    }

}