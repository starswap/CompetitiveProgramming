#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ver = int;

const ver ALL = -1;
vector<vector<ver>> AL;

template <typename T>
T modpow(T base, T exp, T modulus) {
    base %= modulus;
    T result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

template<ll a, ll mod>
struct TreeHash {
    public:
        static TreeHash empty() {return TreeHash(0);} // singleton is 1
        static TreeHash singleton() {return TreeHash(0).level();}
        friend TreeHash operator +(const TreeHash& t, const TreeHash& b) {
            return TreeHash((t.value + b.value) % mod);
        }
        friend ostream& operator << (ostream &o, const TreeHash& t) {
            o << t.value;
            return o;
        }
        TreeHash level() {
            return TreeHash(modpow(a, value, mod));
        }
        TreeHash plusUnder(const TreeHash& h) {
            return TreeHash((value * modpow(a, h.value, mod)) % mod);
        }
        TreeHash operator +=(const TreeHash& other) {
            value = (other.value + value) % mod;
            return *this;
        }
        TreeHash():value(0) {}; 
    ll value;
    private:
        TreeHash(ll v):value(v) {}
};

struct TreeHashCollection {
    public:
        using TH1 = TreeHash<5, 1000000007>;
        using TH2 = TreeHash<31, 16431563>;
        using TH3 = TreeHash<19, 11111117>;
        TH1 h1;
        TH2 h2;
        TH3 h3;

        static TreeHashCollection empty() {return TreeHashCollection(TH1::empty(), TH2::empty(), TH3::empty());}
        static TreeHashCollection singleton() {return TreeHashCollection(TH1::singleton(), TH2::singleton(), TH3::singleton());}
        friend TreeHashCollection operator +(const TreeHashCollection& t, const TreeHashCollection& b) { return TreeHashCollection(t.h1 + b.h1, t.h2 + b.h2, t.h3 + b.h3); }
        friend ostream& operator << (ostream& o, const TreeHashCollection& t) {
            o << "TreeHashCollection(" << t.h1 << ", " << t.h2 << ", " << t.h3 << ")";
            return o;
        }
        friend bool operator <(const TreeHashCollection& t, const TreeHashCollection& t2) {
            return (t.h1.value < t2.h1.value) || (t.h1.value == t2.h1.value && t.h2.value < t2.h2.value) || (t.h1.value == t2.h1.value && t.h2.value == t2.h2.value && t.h3.value < t2.h3.value);
        }
  
        TreeHashCollection level() { return TreeHashCollection(h1.level(), h2.level(), h3.level()); }
        TreeHashCollection plusUnder(const TreeHashCollection& h) { return TreeHashCollection(h1.plusUnder(h.h1), h2.plusUnder(h.h2), h3.plusUnder(h.h3)); }
        TreeHashCollection operator +=(const TreeHashCollection& other) {
            h1 += other.h1;
            h2 += other.h2;
            h3 += other.h3;
            return *this;
        }
        TreeHashCollection():h1(TH1::empty()), h2(TH2::empty()), h3(TH3::empty()) {}
    private:
        TreeHashCollection(TH1 h1, TH2 h2, TH3 h3):h1(h1), h2(h2), h3(h3) {}
};

ll hash_pair(ver u, ver n) {
    return (ll) u * (1000000LL) + (ll) n;
}
unordered_map<ll, TreeHashCollection> hash_cache;

TreeHashCollection doPartialHash(ver u, ver n) {
    auto pair = hash_pair(u, n);
    if (hash_cache.count(pair)) return hash_cache[pair];
    else {
        TreeHashCollection h = TreeHashCollection::empty();
        for (ver v : AL[u]) {
            if (v != n) {
                h = h + doPartialHash(v, u);
            }
        }
        hash_cache[pair] = h.level(); 
        return hash_cache[pair];
    }
}

TreeHashCollection hashTree(ver u) {
    if (AL[u].size() == 0) return TreeHashCollection::singleton();
    ver v = AL[u][0];
    TreeHashCollection h = doPartialHash(u, v).plusUnder(doPartialHash(v, u));
    return h;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int N;
    cin >> N;
    AL.resize(N);
    for (int n = 0; n < N - 1; ++n) {
        ver u, v;
        cin >> u >> v;
        u--; v--;
        AL[u].push_back(v);
        AL[v].push_back(u);
    }
    
    set<TreeHashCollection> signs;

    for (int n = 0; n < N; ++n) {
        signs.insert(hashTree(n));
    }

    cout << signs.size() << endl;
    return 0;
}
