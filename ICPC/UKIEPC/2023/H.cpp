#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll INF = 1e16;
int N, Q;
const ll LAZY_DEFAULT = 0;

struct segment_tree_info {
    ll leftmost;
    ll rightmost;
    bool increasing_ex_ends;
    ll biggest_min_ex_ends;
    ll smallest_min_ex_ends;
    bool is_leftmost_minimum;
    bool is_rightmost_minimum;
    bool is_homogenous;
    int length;
    int number_mins_internal;

    segment_tree_info():leftmost(INF), rightmost(INF), increasing_ex_ends(true), biggest_min_ex_ends(INF), smallest_min_ex_ends(INF), is_leftmost_minimum(true), is_rightmost_minimum(true), is_homogenous(true), length(0), number_mins_internal(0) {} // Arbitrary default construction
    segment_tree_info(ll a, ll b, bool c, ll d, ll e, bool f, bool g, bool h, int i, int j):leftmost(a), rightmost(b), increasing_ex_ends(c), biggest_min_ex_ends(d), smallest_min_ex_ends(e), is_leftmost_minimum(f), is_rightmost_minimum(g), is_homogenous(h), length(i), number_mins_internal(j) {}
    segment_tree_info(ll x):leftmost(x),rightmost(x),increasing_ex_ends(true), biggest_min_ex_ends(-INF), smallest_min_ex_ends(INF), is_leftmost_minimum(true), is_rightmost_minimum(true), is_homogenous(true), length(1), number_mins_internal(0) {}

    friend segment_tree_info operator + (segment_tree_info old, ll di) {
        return {
            old.leftmost + di,
            old.rightmost + di,
            old.increasing_ex_ends,
            old.biggest_min_ex_ends + di,
            old.smallest_min_ex_ends + di,
            old.is_leftmost_minimum,
            old.is_rightmost_minimum,
            old.is_homogenous,
            old.length,
            old.number_mins_internal
        };
    }
};

class SegmentTree {
private:
  int n;

  vector<ll> A;
  vector<segment_tree_info> st;
  vector<ll> lazy;

  int l(int p) { return  p<<1; }
  int r(int p) { return (p<<1)+1; }

  segment_tree_info conquer(segment_tree_info left, segment_tree_info right) {
    ll midpoint_min = INF;
    if (left.is_rightmost_minimum && left.rightmost < right.leftmost && !left.is_homogenous) {
        midpoint_min = left.rightmost; // left.rightmost is new minimum
    } else if (right.is_leftmost_minimum && left.rightmost > right.leftmost && !right.is_homogenous) {
        midpoint_min = right.leftmost; // right.leftmost is new minimum
    } else if (right.leftmost == left.rightmost && right.is_leftmost_minimum && left.is_rightmost_minimum && !left.is_homogenous && !right.is_homogenous) {
        midpoint_min = left.rightmost; // left.rightmost and right.leftmost are new combined middle minimum
    }

    bool flow_ok;
    if (midpoint_min == INF) {
        flow_ok = left.biggest_min_ex_ends < right.smallest_min_ex_ends;
    } else {
        flow_ok = left.biggest_min_ex_ends < midpoint_min && midpoint_min < right.smallest_min_ex_ends;
    }

    // if we are joining together a homogenous right with a left of a different value reconsider rightmost min.

    bool new_is_rightmost_minimum = right.is_rightmost_minimum;
    bool new_is_leftmost_minimum = left.is_leftmost_minimum;

    if (right.is_homogenous) {
        new_is_rightmost_minimum = (right.rightmost < left.rightmost) || (right.rightmost == left.rightmost && left.is_rightmost_minimum);
    }

    if (left.is_homogenous) {
        new_is_leftmost_minimum = (left.leftmost < right.leftmost) || (left.leftmost == right.leftmost && right.is_leftmost_minimum);
    }

    return segment_tree_info{
        left.leftmost,
        right.rightmost,
        left.increasing_ex_ends && right.increasing_ex_ends && flow_ok,
        max(max(left.biggest_min_ex_ends, right.biggest_min_ex_ends), (midpoint_min == INF) ? -INF : midpoint_min),
        min(min(left.smallest_min_ex_ends, right.smallest_min_ex_ends), (midpoint_min == INF) ? INF : midpoint_min),
        new_is_leftmost_minimum,
        new_is_rightmost_minimum,
        left.is_homogenous && right.is_homogenous && left.rightmost == right.leftmost,
        left.length + right.length,
        left.number_mins_internal + right.number_mins_internal + (midpoint_min != INF)
    };
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != LAZY_DEFAULT) {
      st[p] = st[p] + lazy[p];
      if (L != R) {
        if (lazy[l(p)] == LAZY_DEFAULT)
            lazy[l(p)] = lazy[p];
        else
            lazy[l(p)] += lazy[p];

        if (lazy[r(p)] == LAZY_DEFAULT)
            lazy[r(p)] = lazy[p];
        else
            lazy[r(p)] += lazy[p];
      }                              
      else
        A[L] += lazy[p];
      lazy[p] = LAZY_DEFAULT;
    }
  }

  void build(int p, int L, int R) {
    if (L == R)
      st[p] = segment_tree_info{A[L]};
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }
  
  segment_tree_info query(int p, int L, int R, int i, int j) {
    propagate(p, L, R);
    if (i > j) return true; // no idea how this works
    if ((L >= i) && (R <= j)) return st[p];
    int m = (L+R)/2;
    segment_tree_info left = query(l(p), L  , m, i          , min(m, j));
    segment_tree_info right = query(r(p), m+1, R, max(i, m+1), j       );
    if (i > min(m, j)) return right;
    else if (max(i, m + 1) > j) return left; 
    else return conquer(left, right);
  }

  void update(int p, int L, int R, int i, int j, ll val) {
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
  SegmentTree(const vector<ll> &initialA) : n((int)initialA.size()), st(4*n), lazy(4*n, LAZY_DEFAULT) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, ll val) { update(1, 0, n-1, i, j, val); }

  bool check(int i, int j) {
    segment_tree_info x = query(1, 0, n-1, i, j);

    bool ok = x.increasing_ex_ends;
    if (x.is_leftmost_minimum) {
        ok &= x.leftmost < x.smallest_min_ex_ends; 
    }
    if (x.is_rightmost_minimum) {
        ok &= x.rightmost > x.biggest_min_ex_ends;
    }
    if (x.is_leftmost_minimum && x.is_rightmost_minimum && x.number_mins_internal == 0 && !x.is_homogenous) {
        ok &= x.leftmost < x.rightmost;
    }
    return ok;
  }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    vector<ll> A(N);

    for (int n = 0; n < N; ++n) {
        cin >> A[n];
    }

    SegmentTree st(A);

    cin >> Q;
    for (int q = 0; q < Q; ++q) {
        string req;
        cin >> req;
        if (req == "update") {
            int s, f, d;
            cin >> s >> f >> d; s--; f--;
            st.update(s, f, d);
        } else if (req == "check") {
            int s, f;
            cin >> s >> f; s--; f--;
            cout << (st.check(s, f) ? "YES" : "NO") << '\n';
        }
    }
    return 0;
}
     