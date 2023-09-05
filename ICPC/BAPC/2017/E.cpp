#include <bits/stdc++.h>
using namespace std;

typedef complex<double> C;
typedef vector<double> vd;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef struct {
    double x, y;
} point;


typedef vector<int> vi;
vi match, vis;

int Aug(int L, const vector<vector<int>> &AL) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R], AL)) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

int AugPathPP(const vector<vector<int>> &AL, int Vleft) { // Left is 0..Vleft-1. Right is Vleft..V-1
    int V = AL.size();
    unordered_set<int> freeV;
    for (int L = 0; L < Vleft; ++L) freeV.insert(L);
    match.assign(V, -1);
    int MCBM = 0;
    for (int L = 0; L < Vleft; ++L) {              // O(V+E)
        vi candidates;
        for (auto &R : AL[L])
            if (match[R] == -1)
                candidates.push_back(R);
        if ((int)candidates.size() > 0) {
            ++MCBM;
            freeV.erase(L);                            // L is matched
            int a = rand()%(int)candidates.size();     // randomize this
            match[candidates[a]] = L;
        }
    }                                              // for each free vertex
    for (auto &f : freeV) {                        // (in random order)
        vis.assign(Vleft, 0);                        // reset first
        MCBM += Aug(f, AL);                              // try to match f
    }
    return MCBM;    // the answer is 2 for Figure 4.38
}

double dist(point p, point q) {
    return hypot(fabs(p.y - q.y), fabs(p.x - q.x));
}

bool is_possible(double d, const vector<point>& blue, const vector<point> &red, int N, int R, int B)  {
    int Vleft = B;
    vector<vector<int>> AL(B + R, vector<int>());

    for (int i = 0; i < B; ++i) {
        for (int j = 0; j < R; ++j) {
            if (dist(blue[i], red[j]) < d) {
                AL[i].push_back(B + j);
                AL[B + j].push_back(i);
            }
        }
    }

    int matching = AugPathPP(AL, Vleft);
    int minimum_vertex_cover = matching;
    int maximum_independent_set = R + B - minimum_vertex_cover;
    return maximum_independent_set >= N;
}

double solve(const vector<point> &blue, const vector<point>& red, int N, int R, int B) {
    double lo = 0;
    double hi = 2e4;
    const double target = 1e-6;
    while (hi - lo > target) {
        double mi = (lo + hi) / 2;
        if (is_possible(mi, blue, red, N, R, B))
            lo = mi;
        else
            hi = mi;
    }
    return (hi + lo) / 2;
}

int main() {
    int N, B, R;
    cin >> N >> B >> R;
    vector<point> blue(B);
    vector<point> red(R);
    
    rep(i, 0, B) {
        cin >> blue[i].x;
        cin >> blue[i].y;
    }
    
    rep(i, 0, R) {
        cin >> red[i].x;
        cin >> red[i].y;
    }

    cout << fixed << setprecision(10) << solve(blue, red, N, R, B) << endl;

    return 0;
}