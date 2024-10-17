#include <bits/stdc++.h>
using namespace std;

const double INF = 1e20;
const double EPS = 1e-6; // consider e-9 depending on how large the numbers can get

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

struct edge {
    point a, b;
};

// Note that the first and last points must be the same
typedef vector<point> polygon;

// returns the area of polygon P
double area(const polygon &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                          // only do / 2.0 here
}

set<tuple<point, point, point>> seen; 
map<point, vector<point>> AL;

bool dfs(point p, point par, polygon& poly) {
  poly.push_back(p);
  if (p == poly[0]) return true;
  else {
    auto it = AL[p].begin();
    for (it = AL[p].begin(); it != AL[p].end(); ++it) {
      if (*it == par) {break;} 
    }
    point q = *((++it == AL[p].end()) ? AL[p].begin() : it);
    tuple<point, point, point> t{par, p, q};
    if (seen.count(t)) return false;
    bool res = dfs(q, p, poly);
    if (res) seen.insert(t);
    return res;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cout << fixed << setprecision(10);

  int F;
  cin >> F;

  point p1;
  point p2;

  for (int f = 0; f < F; ++f) {
      cin >> p1.x >> p1.y >> p2.x >> p2.y;
      AL[p1].push_back(p2);
      AL[p2].push_back(p1);
  }

  for (auto& [p1, v] : AL) {
    auto cmp = [p1](point p, point q) { return atan2((p.y - p1.y), (p.x - p1.x)) > atan2((q.y - p1.y), (q.x - p1.x)); };
    sort(v.begin(), v.end(), cmp);
  }

  double ans = 0;
  double maxi = 0;

  for (const auto& [p, v] : AL) {
    for (int i = 0; i < (int) v.size(); ++i) {
      polygon poly = {v[i]};

      if (dfs(p, v[i], poly)) {
        double a = area(poly);
        ans += a * a;
        maxi = max(a, maxi);

        // for (const point& p : poly ) {
          // cout << p.x << "," << p.y << endl;
        // }
        // cout << endl;
      }
    }
  }
  ans -= maxi * maxi;
  cout << ans << endl;

  return 0;
}
