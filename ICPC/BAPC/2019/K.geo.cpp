#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

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
  vec operator * (double scalar) {
    return vec(x * scalar, y * scalar);
  }
  vec operator / (double scalar) {
    return vec(x / scalar, y / scalar);
  }
};

double cross(vec a, vec b) {
    return a.x*b.y - a.y*b.x;
}

// returns true if point r is on the left side of line pq, accepting collinear
bool ccw(point p, point q, point r) {
  return cross(vec(p, q), vec(p, r)) > -EPS;
}

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

int main() {
    int n;
    cin >> n;

    double Px, Py;
    cin >> Px >> Py;
    point P(Px, Py);

    double Gix, Giy;
    cin >> Gix >> Giy;
    point O(Gix, Giy);

    vector<point> poly_rest; // except O
    for (int i = 0; i < n - 1; ++i) {
        cin >> Gix >> Giy;
        poly_rest.push_back(point(Gix, Giy));
    }
    poly_rest.push_back(poly_rest[0]);

    vector<double> f(n, 0.0);
    for (int k = 0; k < n - 1; ++k) {
        point Q = poly_rest[k];
        point R = poly_rest[k+1];
        if (!ccw(O, P, Q) && ccw(O, P, R)) { // in the correct triangle
            vec v1(O, Q);
            vec v2(O, R);
            vec x(O, P);

            double k1 = (v1 * v2.x - v2 * v1.x).y;
            double k2 = (v1 * v2.y - v2 * v1.y).x;

            // Use v1 and v2 as a basis
            vec i_b(v2.y/k2, -v1.y/k2);
            vec j_b(v2.x/k1, -v1.x/k1);
            vec x_b(i_b * x.x + j_b * x.y);

            double a = x_b.x; // multiplier of OR vector
            double b = x_b.y; // multiplier of OQ vector

            f[k + 1] = a;
            f[k + 2] = b;
            f[0] = 1 - a - b;
            break;
        }
    }

    for (double fi : f) {
        cout << fixed << setprecision(10) << fi << endl;
    }    
    return 0;
}
