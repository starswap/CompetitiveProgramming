#include <bits/stdc++.h>
using namespace std;

template <typename T>
class SegmentTree {
  typedef vector<T> vt; 

private:
  int n;
  const T LAZY_DEFAULT = -1;    // MODIFY THIS VALUE
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
      st[p] = lazy[p];                          // MODIFY HERE
      if (L != R) {
        if (lazy[l(p)] == LAZY_DEFAULT)
            lazy[l(p)] = lazy[p];
        else
            lazy[l(p)] = lazy[p];               // MODIFY HERE

        if (lazy[r(p)] == LAZY_DEFAULT)
            lazy[r(p)] = lazy[p];
        else
            lazy[r(p)] = lazy[p];               // MODIFY HERE
      }                              
      else {
        assert (lazy[p] >= A[L]);
        A[L] = lazy[p];                         // MODIFY HERE
      }
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

  SegmentTree(int sz) : n(sz), A(sz, 0), st(4*n, 0), lazy(4*n, LAZY_DEFAULT) {}

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

vector<int> A;
vector<int> B;

vector<int> occursB[10005];

int curr_[15 * 10000 + 5];

int main() {
    int N, K; cin >> N >> K;

    SegmentTree<int> st{N * K + 1};

    A.resize(N * K); B.resize(N * K);
    for (int n = 0; n < N * K; ++n) {
        cin >> A[n];
    }
    for (int n = 0; n < N * K; ++n) {
        cin >> B[n];
    }

    for (int n = 0; n < N * K; ++n) {
        occursB[B[n]].push_back(n + 1);
    }

    for (int i = 1; i <= N * K; ++i) {
        for (int j : occursB[A[i - 1]]) {
            curr_[j] = st.RMQ(0, j - 1) + 1;
        }

        for (int j : occursB[A[i - 1]]) {
            st.update(j, j, curr_[j]);
        }
    }

    st.
    cout << st.RMQ(0, N * K) << endl;

    return 0;
}
