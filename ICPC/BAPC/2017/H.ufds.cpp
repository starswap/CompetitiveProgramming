#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const double INF = 1e20;
const double EPS = 1e-6; // consider e-6 ?? 

class UnionFind {                                // OOP style
private:
  vi p, rank, setSize;                           // vi p is the key part
  int numSets;
public:
  UnionFind(int N) {
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
    --numSets;                                   // a union reduces numSets
  }
};

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

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool lineIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;         // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true;
}

bool segIntersect(point p, point q, point r, point s, point &i) {
    if (p == r || p == s) { i = p; return true; }
    else if (q == r || q == s) { i = q; return true; }
    return lineIntersect(line(p, q), line(r, s), i) && 
           min(p.x, q.x) < i.x + EPS && max(p.x, q.x) > i.x - EPS &&
           min(r.x, s.x) < i.x + EPS && max(r.x, s.x) > i.x - EPS &&
           min(p.y, q.y) < i.y + EPS && max(p.y, q.y) > i.y - EPS &&
           min(r.y, s.y) < i.y + EPS && max(r.y, s.y) > i.y - EPS;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int N;
    cin >> N;

    vector<pair<point, point>> segs;
    for (int n = 0; n < N; ++n) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        segs.emplace_back(point(x1, y1), point(x2, y2));
    }

    int ans = 0;
    UnionFind ufds(N);
    for (int i = 0; i < N; ++i) {
        set<point> instct_pts;
        for (int j = 0; j < i; ++j) {
            point intsct;
            if (segIntersect(segs[i].first, segs[i].second, segs[j].first, segs[j].second, intsct) && !(instct_pts.count(intsct)) ) {
                if (ufds.isSameSet(i, j)) {
                    ans += 1;
                } else {
                    ufds.unionSet(i, j);
                }
                instct_pts.insert(intsct);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
