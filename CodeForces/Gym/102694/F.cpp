#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree {
  typedef vector<T> vt; 

private:
  int n;
  const T LAZY_DEFAULT = 0;
  vt A, st;

  int l(int p) { return  p<<1; }
  int r(int p) { return (p<<1)+1; }

  T conquer(T a, T b) {
    return a + b;
  }

  void build(int p, int L, int R) {
    if (L == R)
      st[p] = A[L];
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }
  
  T RSQ(int p, int L, int R, int i, int j) {
    if (i > j) return LAZY_DEFAULT;
    if ((L >= i) && (R <= j)) return st[p];
    int m = (L+R)/2;
    return conquer(RSQ(l(p), L  , m, i          , min(m, j)),
                   RSQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, T val) {
    if (L == R && R == i) {
      st[p] += val;
      A[i] += val;
    }
    else {
      int m = (L+R)/2;
      if (i <= m) {
          update(l(p), L, m, i, val);
      } else {
          update(r(p), m + 1, R, i, val);
      } 
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

public:
  SegmentTree() {}

  SegmentTree(int sz) : n(sz), st(4*n) {}

  SegmentTree(const vt &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, T val) { update(1, 0, n-1, i, val); }

  T RSQ(int i, int j) { return RSQ(1, 0, n-1, i, j); }

  void assign(int n_, T x) {
    n = n_;
    st.assign(4 * n_, x);
    A.assign(n, x);
  }

  void set_array(const vt& initialA) {
    n = initialA.size();
    A = initialA;
    st.resize(4 * n);
    build(1, 0, n-1);
  }
};

typedef long long ll;
int N, Q;
vector<int> parent;
vector<vector<int>> AL;
SegmentTree<ll> thneedville;
vector<pair<int, int>> euler_tour;

int prep_euler_tour(int u, int p, int t) {
    parent[u] = p;
    euler_tour[u].first = t;
    for (int v : AL[u]) {
        if (p == v) continue;
        t = prep_euler_tour(v, u, t + 1);
    }
    euler_tour[u].second = t;
    return t;
}

void update(int a, int b, int x) {
    thneedville.update(euler_tour[a].first, +x);
    thneedville.update(euler_tour[b].first, -x);
}

ll query(int a, int b) {
    int child = parent[a] == b ? a : b;
    return abs(thneedville.RSQ(euler_tour[child].first, euler_tour[child].second));
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> Q;
        AL.assign(N, vector<int>());
        for (int n = 0; n < N - 1; ++n) {
            int u, v; cin >> u >> v;
            u--; v--;
            AL[u].push_back(v);
            AL[v].push_back(u);
        }

        parent.assign(N, -1);
        euler_tour.resize(N);
        prep_euler_tour(0, -1, 0);
        thneedville.assign(N, 0);
        for (int q = 0; q < Q; ++q) {
            int a, b, x;
            cin >> a >> b >> x;
            a--; b--;
            if (x != 0) {
                update(a, b, x);
            } else {            
                cout << query(a, b) << endl;
            }
        }
    }
    return 0;
}