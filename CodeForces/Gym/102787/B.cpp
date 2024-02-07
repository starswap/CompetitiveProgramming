#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
  return result;
}

template <ll MOD, ll P>
struct Hash {
    ll length;
    ll hash;

    Hash(ll l, ll h): length(l), hash(h) {}

    friend Hash<MOD, P> operator +(Hash<MOD, P> h1, Hash<MOD, P> h2) {
        return Hash<MOD, P>(h1.length + h2.length, ((modpow(P, h1.length, MOD) * (h2.hash)) + h1.hash) % MOD);
    }

    friend bool operator == (Hash<MOD, P> h1, Hash<MOD, P> h2) {
        return h1.length == h2.length && h1.hash == h2.hash;
    }
};


template <ll MOD, ll P>
struct Hasher {
    ll map[26];
    Hasher() {
        for (int i = 0; i < 26; ++i) {
            map[i] = rand();
        }
    }

    Hash<MOD, P> compute(string s) {
        ll hash = 0;
        ll p = 0;
        for (char c : s) {
            hash += modpow(P, map[c - 'a'] + p, MOD);
            hash %= MOD;
            p++;
        }
        return Hash<MOD, P>(s.size(), hash);
    }
    
    Hash<MOD, P> compute(char c) {
        return Hash<MOD, P>(1, modpow(P, map[c - 'a'], MOD));
    }
};

struct Hashes {
    static const Hashes zero;
    Hash<1000000007, 2> h1;
    Hash<998244353, 3> h2;
    Hash<998244357, 2> h3;

    Hashes(Hash<1000000007, 2> h1, Hash<998244353, 3> h2, Hash<998244357, 2> h3):h1(h1), h2(h2), h3(h3) {}

    friend Hashes operator +(Hashes hs1, Hashes hs2) {
        return Hashes(hs1.h1 + hs2.h1, hs1.h2 + hs2.h2, hs1.h3 + hs2.h3);
    }

    friend bool operator == (Hashes hs1, Hashes hs2) {
        return hs1.h1 == hs2.h1 && hs1.h2 == hs2.h2 && hs1.h3 == hs2.h3;
    }
};
const Hashes Hashes::zero(Hash<1000000007, 2>(0, 0), Hash<998244353, 3>(0, 0), Hash<998244357, 2>(0, 0));

struct HashesAndReverse {
    static const HashesAndReverse zero;
    Hashes hs;
    Hashes hs_reversed;

    HashesAndReverse(Hashes hs, Hashes hs_reversed):hs(hs), hs_reversed(hs_reversed) {}

    friend HashesAndReverse operator +(HashesAndReverse handr1, HashesAndReverse handr2) {
        return HashesAndReverse(handr1.hs + handr2.hs, handr2.hs_reversed + handr1.hs_reversed);
    }

    friend bool operator == (HashesAndReverse handr1, HashesAndReverse handr2) {
        return handr1.hs == handr2.hs || handr1.hs_reversed == handr2.hs_reversed;
    }
};
const HashesAndReverse HashesAndReverse::zero(Hashes::zero, Hashes::zero);


struct Treap {
    int priority;
    HashesAndReverse value;
    HashesAndReverse subtreesum;
    int totalnodes;
    vector<Treap *> children;
    Treap(HashesAndReverse v):value(v), subtreesum(v) {
        totalnodes = 1;
        children.assign(2, nullptr);
        priority = rand();
    }
    ~Treap() {
        for (Treap* c : children) {
            if (c != nullptr) delete c;
        }
    }
};

int treap_size(Treap* t) {
    return (t == nullptr) ? 0 : t->totalnodes;
}

HashesAndReverse subtree_sum(Treap* t) {
    return (t == nullptr) ? HashesAndReverse::zero : t->subtreesum;
}

void recalc(Treap* t) {
    if (t == nullptr) return;
    t->totalnodes = 1;
    t->subtreesum = subtree_sum(t->children[0]) + t->value + subtree_sum(t->children[1]);
    for (Treap* c : t->children) t->totalnodes += treap_size(c);
}

pair<Treap*, Treap*> split(Treap *t, int nleft) {
    if (t == nullptr) {return {nullptr, nullptr};}
    int total_available = treap_size(t->children[0]) + 1;

    if (total_available < nleft) {
        auto [rl, rr] = split(t->children[1], nleft - total_available);
        t->children[1] = rl;
        recalc(t);
        return make_pair(t, rr);
    } else if (total_available == nleft) {
        Treap* right = t->children[1];
        t->children[1] = nullptr;
        recalc(t);
        return make_pair(t, right);
    } else {
        auto [ll, lr] = split(t->children[0], nleft);
        t->children[0] = lr;
        recalc(t);
        return make_pair(ll, t);
    }
}

Treap* merge(Treap* tl, Treap* tr) {
    if (tl == nullptr) return tr;
    if (tr == nullptr) return tl;
    if (tl->priority < tr->priority) {
        tl->children[1] = merge(tl->children[1], tr);
        recalc(tl);
        return tl;
    } else {
        tr->children[0] = merge(tl, tr->children[0]);
        recalc(tr);
        return tr;
    }
}

Hasher<1000000007, 2> hr1;
Hasher<998244353, 3> hr2;
Hasher<998244357, 2> hr3;

Treap* treap_from_character(char c) {
    return new Treap(HashesAndReverse(Hashes(hr1.compute(c), hr2.compute(c), hr3.compute(c)), Hashes(hr1.compute(c), hr2.compute(c), hr3.compute(c))));
}

Treap* init(string s) {
    Treap* t = nullptr;
    for (char c : s) {
        Treap* t2 = treap_from_character(c);
        t = merge(t, t2);
    }
    return t;
}

bool is_palindrome(Treap *t) {
    return t->subtreesum.hs == t->subtreesum.hs_reversed;
}

Treap* type1query(Treap* t, int l, int r) {
    auto [i, r1] = split(t, l - 1);
    auto [j, k] = split(r1, r - l + 1);
    delete j;
    return merge(i, k);
}

Treap* type2query(Treap* t, char c, int p) {
    auto [i, k] = split(t, p - 1);
    Treap* j = treap_from_character(c);
    return merge(merge(i, j), k);
}

bool type3query(Treap* t, int l, int r) {
    auto [i, r1] = split(t, l - 1);
    auto [j, k] = split(r1, r - l + 1);
    bool result = is_palindrome(j);
    merge(i, merge(j, k));
    return result; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    string s; cin >> s;
    Treap *treap = init(s);

    for (int q = 0; q < Q; ++q) {
        int t, a, b; char c; cin >> t;
        if (t == 1) {
            cin >> a >> b;
            treap = type1query(treap, a, b);
        } else if (t == 2) {
            cin >> c >> a;
            treap = type2query(treap, c, a);
        } else {
            cin >> a >> b;
            cout << ((type3query(treap, a, b)) ? "yes" : "no") << endl;
        }
    }
    delete treap;
    return 0;
}
