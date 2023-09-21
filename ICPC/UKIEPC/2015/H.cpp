#include <bits/stdc++.h>
using namespace std;

const double INF = 1e20;
const double EPS = 1e-6; // consider e-9 depending on how large the numbers can get
const double PI = 3.14159265358979323;

struct point {
  double x, y, id;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y, int __id) : x(_x), y(_y), id(__id) {}  // constructor
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
  vec operator * (double scalar) {
    return vec(x * scalar, y * scalar);
  }
  vec operator / (double scalar) {
    return vec(x / scalar, y / scalar);
  }
};

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }

typedef vector<point> polygon;

bool ccw(point p, point q, point r) {
  return cross(vec(p, q), vec(p, r)) > 0;
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

double compute_angle(point A, point B, point C) {
    if (A.y < C.y + EPS) A.y = C.y;
    if (B.y < C.y + EPS) B.y = C.y;
    if (A == C) A.x -= 10;
    if (B == C) B.x += 10;
    double a = dist(B, C);
    double b = dist(A, C);
    double c = dist(A, B);
    return 12.0 * acos((a * a + b * b  - c * c)/(2 * a * b)) / M_PI;
}

int main() {
    int N;
    cin >> N;

    vector<point> pts;

    for (int i = 0; i < N; ++i) {
        int X, Y;
        cin >> X >> Y;
        pts.push_back(point(X, Y, i));
    }

    // Already given sorted
    // sort(pts.begin(), pts.end());
    
    for (int i = 1; i < N; ++i) {
        assert(pts[i].x != pts[i-1].x);
    }

    vector<point> left(N);
    vector<point> right(N);

    int k = 0;
    vector<point> H(N);
    for (int i = 0; i < N; ++i) {                  // build upper hull
      while ((k >= 2) && ccw(H[k-2], H[k-1], pts[i])) --k;
      H[k++] = pts[i];
      left[pts[i].id] = (k >= 2) ? H[k - 2] : H[k - 1];
    }

    k = 0;
    for (int i = N - 1; i >= 0; --i) {       // build upper hull
      while ((k >= 2) && !ccw(H[k-2], H[k-1], pts[i])) --k;
      H[k++] = pts[i];
      right[pts[i].id] = (k >= 2) ? H[k - 2] : H[k - 1];
    }

    vector<double> angles(N);
    for (point p : pts) {
      angles[p.id] = compute_angle(left[p.id], right[p.id], p);
    }

    for (double a : angles) {
        cout << fixed << setprecision(10) << a << endl;
    }
    
    return 0;
}