#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct Treap {
    int priority;
    int value;
    int totalnodes;
    vector<Treap *> children;
    Treap(int v):value(v) {
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

void recalc(Treap* t) {
    if (t == nullptr) return;
    t->totalnodes = 1;
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

Treap* shuffle(Treap* t, int a, int b, int N) {
    if (a < b) {
        auto [i, r1] = split(t, a - 1);
        int a_size = b - a;
        int b_size = N - b + 1;
        int size = min(a_size, b_size);

        auto [j, r2] = split(r1, size);
        auto [k, r3] = split(r2, b - a - size);
        auto [l, m] = split(r3, size);
        return merge(merge(merge(i, l), merge(k, j)), m);
    } else {
        return t;
    }
}

void in_order_traversal(Treap* t, vector<int>& target) {
    if (t != nullptr) {
        in_order_traversal(t->children[0], target);
        target.push_back(t->value);
        in_order_traversal(t->children[1], target);
    }
}

Treap* init(int N) {
    Treap* t = nullptr;
    for (int i = 1; i <= N; ++i) {
        t = merge(t, new Treap(i));
    }
    return t;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;
    Treap *t = init(N);
    for (int n = 0; n < N; ++n) {
        int a, b; cin >> a >> b;
        t = shuffle(t, a, b, N);
    }
    vector<int> results;
    in_order_traversal(t, results);
    for (int i : results) {
        cout << i << " ";
    }
    cout << endl;
    delete t;
    return 0;
}
