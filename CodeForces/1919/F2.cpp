#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<ll> vll;

typedef array<array<ll, 2>, 2> arr_t;
class DPSegmentTree {
  typedef vector<arr_t> vt; 

private:
  int n;
  vt A, st;

  int l(int p) { return  p<<1; }
  int r(int p) { return (p<<1)+1; }

  arr_t conquer(arr_t a, arr_t b) {
    arr_t res;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            res[i][j] = min(a[i][0] + b[0][j], a[i][1] + b[1][j]);
        }
    }
    return res;
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

  void update(int p, int L, int R, int i, arr_t val) {
    if (L == R && R == i) {
      A[L] = val;
      st[p] = val;
    }
    else {
      int m = (L+R)/2;
      if (i <= m) {
          update(l(p), L  , m, i, val);
      } else {
          update(r(p), m+1, R, i, val);
      }
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

public:
  DPSegmentTree() {}

  DPSegmentTree(int sz) : n(sz), st(4*n) {}

  DPSegmentTree(const vt &initialA) : DPSegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, arr_t val) { update(1, 0, n-1, i, val); }

  arr_t get_result() { return st[1]; }

  void set_array(const vt& initialA) {
    n = initialA.size();
    A = initialA;
    st.resize(4 * n);
    build(1, 0, n-1);
  }
};

int N, Q;
vector<int> A;
vector<int> B;
vector<ll> C;
DPSegmentTree dpseg;

arr_t compute_unit(int i) {
    arr_t node;
    node[0][0] = A[i];
    node[0][1] = B[i];
    if (i > 0)
        node[1][0] = A[i] + C[i - 1]; 
    node[1][1] = B[i];
    return node;
}

void build() {
    vector<arr_t> init;
    for (int i = 0 ; i < N; ++i) {
        init.push_back(compute_unit(i));
    }
    dpseg.set_array(init);
}

ll query() {
    int p, x, y; ll z;
    cin >> p >> x >> y >> z; p--;
    A[p] = x;
    B[p] = y;
    if (p != N - 1) {
        C[p] = z;
        dpseg.update(p + 1, compute_unit(p + 1));
    }
    dpseg.update(p, compute_unit(p));
    arr_t res = dpseg.get_result();
    return min(res[0][0], res[0][1]);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> Q;
    A.assign(N, -1);
    B.assign(N, -1);
    C.assign(N - 1, -1);
    for (int n = 0; n < N; ++n) {
        cin >> A[n];
    }

    for (int n = 0; n < N; ++n) {
        cin >> B[n];
    }
    
    for (int n = 0; n < N - 1; ++n) {
        cin >> C[n];
    }
    
    build();

    for (int q = 0; q < Q; ++q) {
        cout << query() << endl;
    }

    return 0;
}
