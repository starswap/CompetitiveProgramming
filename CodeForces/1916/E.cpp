#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;

class SegmentTree {                              // To modify, change Conquer; Propagate; LAZY_DEFAULT
private:
  int n;                                         // n = (int)A.size()
  const int LAZY_DEFAULT = 0;
  vi A, st, lazy;                                // the arrays

  int l(int p) { return  p<<1; }                 // go to left child
  int r(int p) { return (p<<1)+1; }              // go to right child

  int conquer(int a, int b) {
    if (a == -1) return b;                       // corner case
    if (b == -1) return a;
    return max(a, b);                            // RMQ
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != LAZY_DEFAULT) {               // has a lazy flag
      st[p] += lazy[p];
      if (L != R) {                              // not a leaf
        lazy[l(p)] += lazy[p];
        lazy[r(p)] += lazy[p];                   // propagate downwards
      }                              
      else                                       // L == R, a single index
        A[L] += lazy[p];                         // time to update this
      lazy[p] = LAZY_DEFAULT;                    // erase lazy flag
    }
  }

  void build(int p, int L, int R) {              // O(n)
    if (L == R)
      st[p] = A[L];                              // base case
    else {
      int m = (L+R)/2;
      build(l(p), L  , m);
      build(r(p), m+1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }
  
  int RMQ(int p, int L, int R, int i, int j) {   // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return -1;                        // infeasible
    if ((L >= i) && (R <= j)) return st[p];      // found the segment
    int m = (L+R)/2;
    return conquer(RMQ(l(p), L  , m, i          , min(m, j)),
                   RMQ(r(p), m+1, R, max(i, m+1), j        ));
  }

  void update(int p, int L, int R, int i, int j, int val) { // O(log n)
    propagate(p, L, R);                          // lazy propagation
    if (i > j) return;
    if ((L >= i) && (R <= j)) {                  // found the segment
      lazy[p] = val;                             // update this
      propagate(p, L, R);                        // lazy propagation
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

  SegmentTree(const vi &initialA) : SegmentTree((int)initialA.size()) {
    A = initialA;
    build(1, 0, n-1);
  }

  void update(int i, int j, int val) { update(1, 0, n-1, i, j, val); }

  int RMQ(int i, int j) { return RMQ(1, 0, n-1, i, j); }

  void assign(int n_, int x) {
    n = n_;
    st.assign(4 * n_, x);
    lazy.assign(4 * n, LAZY_DEFAULT);
    A.assign(n, x);
  }
};

const int UNSEEN = -1;
int N;
vector<vector<int>> cs;
vector<int> A;
vector<pair<int, int>> euler_tour;
vector<int> activity_last_seen;
vector<vector<int>> turnoffs;

int construct_euler_tour(int u, int t) {
    euler_tour[u].first = t;
    for (int c : cs[u]) {
        t = construct_euler_tour(c, t + 1);
    }
    euler_tour[u].second = t;
    return t;
}

void construct_turnoffs(int u) {
    int a = A[u];
    int old_last_seen = activity_last_seen[a];
    if (old_last_seen != UNSEEN) {
        turnoffs[old_last_seen].push_back(u);
    }
    activity_last_seen[a] = u;
    for (int c : cs[u]) {
        construct_turnoffs(c);
    }
    activity_last_seen[a] = old_last_seen;
}

SegmentTree compressed_tree;
ll get_answer(int lca) {
    ll ans = 0;
    for (int c : cs[lca]) {
        ans = max(ans, get_answer(c));
    }
    // turn off
    for (int off : turnoffs[lca]) {
        compressed_tree.update(euler_tour[off].first, euler_tour[off].second, -1);
    }
    // turn on
    compressed_tree.update(euler_tour[lca].first, euler_tour[lca].second, 1);

    int best = 1; // possible to choose to live at the root
    int snd = 1;
    for (int c : cs[lca]) {
        auto [l, r] = euler_tour[c]; // nodes in that subtree
        int this_one = compressed_tree.RMQ(l, r);
        if (this_one >= best) {snd = best; best = this_one;}
        else if (this_one > snd) {snd = this_one;}
    }

    ans = max(ans, (ll) best * (ll) snd); 
    return ans;
}

ll solve() {
    euler_tour.assign(N, make_pair(0, 0));
    construct_euler_tour(0, 0);
    activity_last_seen.assign(N, UNSEEN);
    turnoffs.assign(N, vector<int>());
    construct_turnoffs(0);
    compressed_tree.assign(N, 0);
    return get_answer(0);
} 

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        cs.assign(N, vector<int>());
        for (int n = 1; n < N; ++n) {
            int p; cin >> p;
            p--;
            cs[p].push_back(n);
        }
        A.assign(N, 0);
        for (int n = 0; n < N; ++n) {
            cin >> A[n]; A[n]--;
        }
        cout << solve() << endl;
    }
    
    return 0;
}