#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct Treap {
    int priority;
    int value;
    int totalnodes;
    ll subtree_sum;
    Treap* par;

    vector<Treap *> children;
    Treap(ll v):value(v) {
        totalnodes = 1;
        children.assign(2, nullptr);
        priority = rand();
        par = nullptr;
        subtree_sum = value;
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

ll subtree_sum(Treap* t) {
    return (t == nullptr) ? 0 : t->subtree_sum;
}

void recalc(Treap* t) {
    if (t == nullptr) return;
    t->totalnodes = 1;
    t->subtree_sum = t->value;
    for (Treap* c : t->children) t->totalnodes += treap_size(c);
    for (Treap* c : t->children) t->subtree_sum += subtree_sum(c);
}

pair<Treap*, Treap*> split(Treap *t, int nleft) {
    if (t == nullptr) {return {nullptr, nullptr};}
    int total_available = treap_size(t->children[0]) + 1;

    if (total_available < nleft) {
        auto [rl, rr] = split(t->children[1], nleft - total_available);
        t->children[1] = rl;
        if (rl != nullptr) rl->par = t;
        t->par = nullptr;
        recalc(t);
        return make_pair(t, rr);
    } else if (total_available == nleft) {
        Treap* right = t->children[1];
        if (right != nullptr) right->par = nullptr;
        t->par = nullptr;
        t->children[1] = nullptr;
        recalc(t);
        return make_pair(t, right);
    } else {
        auto [ll, lr] = split(t->children[0], nleft);
        t->children[0] = lr;
        if (lr != nullptr) lr->par = t;
        t->par = nullptr;
        recalc(t);
        return make_pair(ll, t);
    }
}

Treap* merge(Treap* tl, Treap* tr) {
    if (tl == nullptr) return tr;
    if (tr == nullptr) return tl;
    if (tl->priority < tr->priority) {
        tl->children[1] = merge(tl->children[1], tr);
        if (tl->children[1] != nullptr) tl->children[1]->par = tl;
        recalc(tl);
        return tl;
    } else {
        tr->children[0] = merge(tl, tr->children[0]);
        if (tr->children[0] != nullptr) tr->children[0]->par = tr;
        recalc(tr);
        return tr;
    }
}

Treap *t = nullptr;
vector<Treap*> mapping;

Treap* root(Treap* t) {
    while (t->par != nullptr) {
        t = t->par;
    }
    return t;
}

void type1query(int i, int y) {
    mapping[i] = new Treap(y);
}

void type2query(int y, int z) {
    Treap* r1 = root(mapping[y]);
    Treap* r2 = root(mapping[z]);
    if (r1 != r2) {
        merge(r1, r2);
    }
}

void type3query(int y, int z) {
    Treap* r = root(mapping[y]);
    if (treap_size(r) > z) {
        split(r, z);
    }
}

ll type4query(int y) {
    Treap* r = root(mapping[y]);
    return subtree_sum(r);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int Q; cin >> Q;
    mapping.assign(Q, nullptr);

    for (int q = 0; q < Q; ++q) {
        int t;
        int y, z;
        cin >> t;
        switch (t) {
            case 1: {
                cin >> y;
                type1query(q, y);
                break;
            }
            case 2: {
                cin >> y >> z; y--; z--;
                type2query(y, z);
                break;
            }
            case 3: {
                cin >> y >> z; y--;
                type3query(y, z);
                break;
            }
            case 4: {
                cin >> y; y--;
                cout << type4query(y) << endl;
                break;
            }
        }
    }
    return 0;
}
