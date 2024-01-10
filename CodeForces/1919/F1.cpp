#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

template <typename T>
class SegmentTree {
  typedef vector<T> vt; 

private:
  int n;
  const T LAZY_DEFAULT = -10000000000000005;    // MODIFY THIS VALUE
  vt A, st;
  vt lazy;

  int l(int p) { return  p<<1; }
  int r(int p) { return (p<<1)+1; }

  T conquer(T a, T b) {
    if (a == LAZY_DEFAULT) return b;
    if (b == LAZY_DEFAULT) return a;
    return max(a, b);                            // MODIFY THIS FUNCTION
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != LAZY_DEFAULT) {
      st[p] += lazy[p];                          // MODIFY HERE
      if (L != R) {
        if (lazy[l(p)] == LAZY_DEFAULT)
            lazy[l(p)] = lazy[p];
        else
            lazy[l(p)] += lazy[p];               // MODIFY HERE

        if (lazy[r(p)] == LAZY_DEFAULT)
            lazy[r(p)] = lazy[p];
        else
            lazy[r(p)] += lazy[p];               // MODIFY HERE
      }                              
      else
        A[L] += lazy[p];                         // MODIFY HERE
      lazy[p] = LAZY_DEFAULT;
    }
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
  
  T RMQ(int p, int L, int R, int i, int j) {
    propagate(p, L, R);
    if (i > j) return LAZY_DEFAULT;
    if ((L >= i) && (R <= j)) return st[p];
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, T val) {
    propagate(p, L, R);
    if (i > j) return;
    if ((L >= i) && (R <= j)) {
      lazy[p] = val;
      propagate(p, L, R);
    }
    else {
      int m = (L+R)/2;
      update(l(p), L  , m, i          , min(m, j), val);
      update(r(p), m+1, R, max(i, m+1), j        , val);
      assert(lazy[l(p)] == LAZY_DEFAULT);
      assert(lazy[r(p)] == LAZY_DEFAULT);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

public:
  SegmentTree() {}

  SegmentTree(int sz) : n(sz), st(4*n), lazy(4*n, LAZY_DEFAULT) {}

  SegmentTree(const vt &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, T val) { update(1, 0, n-1, i, j, val); }

  T RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }

  void assign(int n_, T x) {
    n = n_;
    st.assign(4 * n_, x);
    lazy.assign(4 * n, LAZY_DEFAULT);
    A.assign(n, x);
  }

  void set_array(const vt& initialA) {
    n = initialA.size();
    A = initialA;
    st.resize(4 * n);
    lazy.assign(4 * n, LAZY_DEFAULT);
    build(1, 0, n-1);
  }
};

int N, Q;
ll sigmaA = 0;
vector<int> A;
vector<int> B;
vector<ll> C;
vector<int> V;
vector<ll> VS;

ll query() {
    static SegmentTree<ll> VST(VS);
    int p, x, y;
    ll z;
    cin >> p >> x >> y >> z; p--;
    sigmaA -= A[p];
    sigmaA += x;
    A[p] = x;
    B[p] = y;
    ll newVP = x - y;
    if (p != N - 1) {
        C[p] = z;
    } 
    ll delta = newVP - V[p];
    VST.update(0, p, delta);

    V[p] = newVP;

    return sigmaA - VST.RMQ(0, N);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> Q;
    A.assign(N, -1);
    B.assign(N, -1);
    C.assign(N - 1, -1);
    for (int n = 0; n < N; ++n) {
        cin >> A[n];
        sigmaA += A[n];
    }

    for (int n = 0; n < N; ++n) {
        cin >> B[n];
    }
    
    for (int n = 0; n < N - 1; ++n) {
        cin >> C[n];
    }
    V.assign(N, 0);
    VS.assign(N + 1, 0);
    for (int n = 0; n < N; ++n) {
        V[n] = A[n] - B[n];
    }
    for (int n = N - 1; n >= 0; --n) {
        VS[n] = VS[n + 1] + V[n];
    }

    for (int q = 0; q < Q; ++q) {
        cout << query() << endl;
    }

    return 0;
}
