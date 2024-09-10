#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ver = int;

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

/* This hashing scheme works nicely because it allows us to easily "add and subtract" subtrees
   but it seems odd to me that it works because it's not true in general that
   b = c (mod m) => a^b = a^c (mod m) and that's the usual way to argue for 
   correctness of hashes involving mod.

   But I think you can argue this makes sense by induction. What we are trying to convince
   ourselves of is the idea that for a given tree structure, no matter how you build it
   using the allowed operations, you always get the same hash. Equally 'if 2 trees are of the same composition,
   they have the same hash'. This is trivially true for a single node, 
   then for a tree of the form:
   O----
   | | |
   X Y Z
   you can assume the result for trees X, Y, and Z, and so assume you have some h(X), h(Y), h(Z) 
   and then claim that the only operations allowed in building tree O are add X (i.e. * a^(h(X))),
   add Y, add Z, subtract X, subtract Y, subtract Z, or add + subtract some other random
   tree. No matter how many times you do this you will get the right result for O because it's clear that
   a ^ p * (a_inv)^p = 1 (mod m) is always true, and you have commutativity of * etc.

  The only other thing to prove then is that you don't get systematic hash collisions regardless 
  of the a that you use (because if that's true you can just combine as many hashes as it takes to avoid
  hash collisions - you can work out how many are needed if necessary). I think you can convince yourself
  of this by looking at the structure of the hash terms and how they relate to the tree structure.
  You would need two hash terms of different structures to have the same value which isn't going to be
  true for arbitrary a.

  Previously I was constructing 
   O----
   | | |
   X Y Z
   by doing (h(X) + h(Y) + h(Z)) % m and then raising to the h(O). In combination with adding and subtracting this
   is no longer correct because by the current adding and subtracting you can generate

   a^(hX + hY + hZ) % m whereas this method generates a^((hx + hY + hZ) % m) % m and these are not the same in general. 
*/
template<ll a, ll mod>
struct TreeHash {
    public:
        static TreeHash singleton() {return TreeHash(a);}
        
        friend bool operator <(const TreeHash& t, const TreeHash& b) { return t.value < b.value; }
        friend bool operator ==(const TreeHash& t, const TreeHash& b) { return t.value == b.value; }
        friend ostream& operator << (ostream &o, const TreeHash& t) { o << t.value; return o; }

        TreeHash addSubtree(const TreeHash& h) { return TreeHash((value * modpow(a, h.value, mod)) % mod); }
        TreeHash removeSubtree(const TreeHash& h) {
            ll a_inv = modpow(a, mod - 2, mod); // Fermat's Little Theorem; prime number mod
            return TreeHash((value * modpow(a_inv, h.value, mod)) % mod);
        }
        TreeHash():value(0) {};
    private:
        TreeHash(ll v):value(v) {}
        ll value;
};

struct TreeHashCollection {
    public:
        using TH1 = TreeHash<11, 1000000007>;
        using TH2 = TreeHash<61, 16431563>;
        using TH3 = TreeHash<97, 999999937>;

        TH1 h1;
        TH2 h2;
        TH3 h3;

        static TreeHashCollection singleton() {return TreeHashCollection(TH1::singleton(), TH2::singleton(), TH3::singleton());}
        friend ostream& operator << (ostream& o, const TreeHashCollection& t) {o << "TreeHashCollection(" << t.h1 << ", " << t.h2 << ", " << t.h3 << ")"; return o; }
        friend bool operator <(const TreeHashCollection& t, const TreeHashCollection& t2) { return (t.h1 < t2.h1) || (t.h1 == t2.h1 && t.h2 < t2.h2) || (t.h1 == t2.h1 && t.h2 == t2.h2 && t.h3 < t2.h3); }
  
        TreeHashCollection addSubtree(const TreeHashCollection& h) { return TreeHashCollection(h1.addSubtree(h.h1), h2.addSubtree(h.h2), h3.addSubtree(h.h3)); }
        TreeHashCollection removeSubtree(const TreeHashCollection& h) { return TreeHashCollection(h1.removeSubtree(h.h1), h2.removeSubtree(h.h2), h3.removeSubtree(h.h3)); }
        TreeHashCollection():h1(TH1::singleton()), h2(TH2::singleton()), h3(TH3::singleton()) {}
    private:
        TreeHashCollection(TH1 h1, TH2 h2, TH3 h3):h1(h1), h2(h2), h3(h3) {}
};

unordered_map<ll, TreeHashCollection> hash_cache_u_exc_v; // hashed_pair(tree rooted at u, excluding subtree rooted at vf) to tree hash
unordered_map<ver, TreeHashCollection> hash_cache; // tree hash of tree when rooted at u
vector<vector<ver>> AL;

/* Our own hash to allow us to use unordered_map of pairs, optimisation */
ll hash_pair(ver u, ver n) {
    return (ll) u * (1000000LL) + (ll) n;
}

/* Compute hash for the subtree rooted at node u
   excluding the subtree rooted at node n. This
   has the side effect of causing all of the hash_cache_u_exc_v
   when the tree is traveresed from node x to be computed,
   if x is the u value from the original call. */
TreeHashCollection doPartialHash(ver u, ver n) {
    auto pair = hash_pair(u, n);
    if (hash_cache_u_exc_v.count(pair)) return hash_cache_u_exc_v[pair];
    else {
        TreeHashCollection h = TreeHashCollection::singleton();
        for (ver v : AL[u]) {
            if (v != n) {
                h = h.addSubtree(doPartialHash(v, u));
            }
        }
        hash_cache_u_exc_v[pair] = h;
        return hash_cache_u_exc_v[pair];
    }
}

/* Compute tree hash for rooting the tree at node u */
TreeHashCollection hashTree(ver u) {
    if (hash_cache.count(u)) return hash_cache[u];
    if (AL[u].size() == 0) return TreeHashCollection::singleton();
    ver v = AL[u][0];
    TreeHashCollection h = doPartialHash(u, v).addSubtree(doPartialHash(v, u));
    hash_cache[u] = h;
    return h;
}

/* Precondition: Assume that we already calculated all hashes when 
   we root the tree at node p, i.e. hash_cache[p] and all
   hash_cache_u_exc_v[u, p] for some u.
   
   Result: hash_cache[u] gets computed*/
void allHashesDfs(ver u, ver p) {
    assert (hash_cache_u_exc_v.count(hash_pair(u, p)));
    TreeHashCollection new_child = hash_cache[p].removeSubtree(hash_cache_u_exc_v[hash_pair(u, p)]);
    hash_cache[u] = hash_cache_u_exc_v[hash_pair(u, p)].addSubtree(new_child);

    for (ver v : AL[u]) {
        if (v == p) continue;
        allHashesDfs(v, u);
    }
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

    hashTree(0);
    for (ver v : AL[0]) {
        allHashesDfs(v, 0);
    }

    for (int n = 0; n < N; ++n) {
        signs.insert(hashTree(n));
    }

    cout << signs.size() << endl;
    return 0;
}
