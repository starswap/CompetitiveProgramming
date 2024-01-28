#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;

#define LSOne(S) ((S) & -(S))                    // the key operation

class FenwickTree {                              // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree() {}
  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= m)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // do the conversion first
      ++f[s[i]];                                 // in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};


int N, M, Q; 
ll ans = 0;
vector<ll> deltas;
vector<int> harbour_locs;
map<int, int> Hs;
FenwickTree ft;

void init() {
    deltas.assign(N, 0);
    auto nearest_left = Hs.begin();
    auto nearest_right = next(nearest_left);
    for (int i = 0 ; i < N; ++i) {
        if (i == nearest_left->first) {deltas[i] = ans; continue;}
        if (i == nearest_right->first) {
            deltas[i] = ans;
            nearest_left++;
            nearest_right++;
            ans = 0;
        } else {
            ans += ((ll) (nearest_left->second)) * ((ll) (nearest_right->first - i));            
        }
    }
  ft = FenwickTree(deltas);
}

inline ll range(ll l, ll r) {
  return (((r - l)*(r - l - 1))/2);
}

void type1query(int k, int C) {
    auto [j, A] = *prev(Hs.upper_bound(k));
    auto [l, B] = *Hs.upper_bound(k);
    ft.update(k, ((ll) A) * range(j, k));
    ft.update(l, - A * range(j, l));
    ft.update(l, ((ll) C) * range(k, l));
    Hs[k] = C;
}

ll type2query(int lo, int hi) {
    auto [j, A] = *prev(Hs.upper_bound(lo));
    auto [k, D] = *Hs.lower_bound(lo);
    auto [k2, C] = *prev(Hs.upper_bound(hi)); 
    auto [l, B] = *Hs.lower_bound(hi);
    ll corrA = (lo == j) ? 0 : (((ll) A) * (range(j, k) - range(lo - 1, k)));
    ll corrB = ((ll) C) * range(hi, l);
    return  ft.rsq(l) - ft.rsq(j) - corrA - corrB;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> M >> Q;
    harbour_locs.resize(M);
    for (int m = 0; m < M; ++m) {
        cin >> harbour_locs[m];
        harbour_locs[m]--;
    }
    for (int m = 0; m < M; ++m) {
        int v;
        cin >> v;
        Hs[harbour_locs[m]] = v;
    }

    init();

    for (int q = 0; q < Q; ++q) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, v; cin >> x >> v;
            x--;
            type1query(x, v);
        } else {
            int l, r; cin >> l >> r;
            l--; r--;
            cout << type2query(l, r) << endl;
        }
    }

    return 0;
}