#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const double EPS = 1e-6;

struct BaseOneBillion {
private:
    double mantissa;
    ll exponent;

public: 
    static const ll BLN = 1000000000;

    BaseOneBillion(double man, ll exp):mantissa(man), exponent(exp) {}

    friend BaseOneBillion operator *(BaseOneBillion x, BaseOneBillion y) {
        ll exp = x.exponent + y.exponent;
        double man = x.mantissa * y.mantissa;
        if (man >= BLN) {
            exp += 1;
            man /= BLN;
        }
        return BaseOneBillion(man, exp);
    }

    friend double operator /(BaseOneBillion x, BaseOneBillion y) {
        ll dexp = x.exponent - y.exponent;
        if (dexp > 1 || (dexp == 1 && x.mantissa > y.mantissa - EPS)) {
            return BLN;
        } else if (dexp < -1 || (dexp == -1 && x.mantissa + EPS < y.mantissa)) {
            return 0;
        } else {
            return (pow((double) BLN, dexp)) * (x.mantissa / y.mantissa);
        }
    }

    friend bool operator == (BaseOneBillion x, BaseOneBillion y) {
        return x.exponent == y.exponent && fabs(x.mantissa - y.mantissa) < EPS;
    }
};

class SegmentTree {
  typedef vector<BaseOneBillion> vt; 

private:
  int n;
  vt A, st;
  const BaseOneBillion FAILED = BaseOneBillion(0, -1000000000); 

  int l(int p) { return  p<<1; }
  int r(int p) { return (p<<1)+1; }

  BaseOneBillion conquer(BaseOneBillion a, BaseOneBillion b) {
    if (a == FAILED) return b;
    if (b == FAILED) return a;
    return a * b;
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
  
  BaseOneBillion query(int p, int L, int R, int i, int j) {
    if (i > j) return FAILED;
    if ((L >= i) && (R <= j)) return st[p];
    int m = (L+R)/2;
    return conquer(query(l(p), L  , m, i          , min(m, j)),
                   query(r(p), m+1, R, max(i, m+1), j        ));
  }


  void update(int p, int L, int R, int i, BaseOneBillion val) {
    if (L == i && R == i) {
      A[i] = val;
      st[p] = val;
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
  SegmentTree(int sz, BaseOneBillion v) : n(sz), A(sz, v), st(4*n, v) {}

  void update(int i, BaseOneBillion val) { update(1, 0, n-1, i, val); }

  BaseOneBillion query(int i, int j) { return query(1, 0, n-1, i, j); }

};

vector<vector<int>> AL;

vector<pair<int, int>> euler_tour;
int gen_euler_tour(int u, int p, int t) {
    euler_tour[u].first = t;
    for (int v : AL[u]) {
        if (v == p) continue;
        t = gen_euler_tour(v, u, t + 1);
    }
    euler_tour[u].second = t;
    return t;
}

void type1query(int x, int y, SegmentTree &st) {
    x--;
    st.update(euler_tour[x].first, BaseOneBillion(y, 0));
}

double type2query(int x, int y, SegmentTree &st) {
    x--; y--;
    BaseOneBillion valX = st.query(euler_tour[x].first, euler_tour[x].second);
    BaseOneBillion valY = st.query(euler_tour[y].first, euler_tour[y].second);
    return valX / valY;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    AL.assign(N, vector<int>());
    for (int n = 0; n < N - 1; ++n) {
        int u, v;
        cin >> u >> v; u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }

    euler_tour.resize(N);
    gen_euler_tour(0, -1, 0);

    SegmentTree st(N, BaseOneBillion(1, 0));

    cout << setprecision(10) << fixed;
    int Q; cin >> Q;
    for (int q = 0; q < Q; ++q) {
        int t, x, y; cin >> t >> x >> y;
        if (t == 1) {
            type1query(x, y, st);
        } else {
            cout << type2query(x, y, st) << endl;
        }
    }
    return 0;
}