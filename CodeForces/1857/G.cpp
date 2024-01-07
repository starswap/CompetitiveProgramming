#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 998244353;

typedef vector<int> vi;

template <typename T>
T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  assert(result < modulus);
  return result;
}

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

struct edge {
    int u, v, w;
};

int solve(vector<edge> &es, ll N, ll S) {
    sort(es.begin(), es.end(), [](edge a, edge b) {
        return a.w < b.w;
    });
    long long ans = 1;
    UnionFind ufds(N);
    for (auto [u, v, w] : es) {
        ll this_ans = modpow(S - (ll) w + 1, ((ll) ufds.sizeOfSet(u) * (ll) ufds.sizeOfSet(v) - 1), MOD);
        ans = (ans * this_ans) % MOD;
        ufds.unionSet(u, v);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, S;
        cin >> N >> S;
        vector<edge> es(N - 1);
        for (int n = 0; n < N - 1; ++n) {
            int u, v, w;
            cin >> u >> v >> w;
            es[n].u = --u;
            es[n].v = --v;
            es[n].w = w;
        }
        cout << solve(es, N, S) << endl;
    }
    return 0;
}