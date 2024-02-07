#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

struct subtree_runs {
    static const subtree_runs empty;
    bool left_most;
    int left_run_length;
    bool right_most;
    int right_run_length;
    int length;
    int best_run;

    subtree_runs(bool lm, int lrl, bool rm, int rrl, int l, int br):left_most(lm), left_run_length(lrl), right_most(rm), right_run_length(rrl), length(l), best_run(br) {}
    
    friend subtree_runs operator + (subtree_runs v1, subtree_runs v2) {
        if (v1.length == 0) return v2;
        if (v2.length == 0) return v1;

        int new_lrl = v1.left_run_length;
        int new_rrl = v2.right_run_length;
        if (v1.left_run_length == v1.length && v1.left_most == v2.left_most) {
            new_lrl += v2.left_run_length;
        }
        if (v2.right_run_length == v2.length && v1.right_most == v2.right_most) {
            new_rrl += v1.right_run_length;
        }
        int new_br = max(max(max(v1.best_run, v2.best_run), new_lrl), new_rrl);
        if (v1.right_most == v2.left_most) {
            new_br = max(new_br, v1.right_run_length + v2.left_run_length);
        }
        return subtree_runs(v1.left_most, new_lrl, v2.right_most, new_rrl, v1.length + v2.length, new_br);
    }
};
const subtree_runs subtree_runs::empty = subtree_runs(false, 0, false, 0, 0, 0);

struct Treap {
    int priority;
    bool value;
    int totalnodes;
    bool lazy_toggle;
    subtree_runs s;

    vector<Treap *> children;
    Treap(bool v):value(v), s(value, 1, value, 1, 1, 1) {
        totalnodes = 1;
        children.assign(2, nullptr);
        lazy_toggle = false;
        priority = rand();
    }
    ~Treap() {
        for (Treap* c : children) {
            if (c != nullptr) delete c;
        }
    }
};

void propagate(Treap* t) {
    if (t == nullptr) return;
    if (t->lazy_toggle) {
        t->value = !t->value;
        t->s.left_most = !t->s.left_most; 
        t->s.right_most = !t->s.right_most;
        t->lazy_toggle = false;
        for (Treap* c : t->children) {if (c != nullptr) {c->lazy_toggle = !c->lazy_toggle;}}
    }
}

int treap_size(Treap* t) {
    return (t == nullptr) ? 0 : t->totalnodes;
}

subtree_runs get_subtree_run(Treap* t) {
    return (t == nullptr) ? (subtree_runs::empty) : t->s;
}

void recalc(Treap* t) {
    if (t == nullptr) return;
    propagate(t);
    propagate(t->children[0]);
    propagate(t->children[1]);
    t->totalnodes = 1;
    t->s = ((get_subtree_run(t->children[0]) + subtree_runs(t->value, 1, t->value, 1, 1, 1)) + get_subtree_run(t->children[1]));
    for (Treap* c : t->children) t->totalnodes += treap_size(c);
}

pair<Treap*, Treap*> split(Treap *t, int nleft) {
    if (t == nullptr) {return {nullptr, nullptr};}
    int total_available = treap_size(t->children[0]) + 1;
    propagate(t);
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
        propagate(tl);
        tl->children[1] = merge(tl->children[1], tr);
        recalc(tl);
        return tl;
    } else {
        propagate(tr);
        tr->children[0] = merge(tl, tr->children[0]);
        recalc(tr);
        return tr;
    }
}

Treap* init(string s) {
    Treap* t = nullptr;
    for (char c : s) {
        t = merge(t, new Treap(c == '1'));
    }
    return t;
}

void toggle(Treap *t) {
    t->lazy_toggle = !t->lazy_toggle;
}

int get(Treap* t) {
    propagate(t);
    return t->s.best_run;
}

Treap* type1query(Treap*t, int l, int r) {
    auto [i, r1] = split(t, l - 1);
    auto [j, k] = split(r1, r - l + 1);
    toggle(j);
    Treap* m1 = merge(i, j);
    return merge(m1, k);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N >> Q;
    string s; cin >> s;
    
    Treap *t = init(s);
    for (int q = 0; q < Q; ++q) {
        int qt, a, b;
        cin >> qt >> a >> b;
        if (qt == 1) {
            t = type1query(t, a, b);
        } 
        cout << get(t) << endl;
    }
    delete t;
    return 0;
}

// Generator:

// import random
// N = 10
// Q = 10
// a = "".join(map(str, [random.randint(0, 1) for i in range(N)]))
// print(N, Q)
// print(a)
// for i in range(Q):
//     L = random.randint(1, N)
//     R = random.randint(L, N)
//     print(1, L, R)

// Brute force checker:

// N, Q = map(int, input().split())
// A = [*map(lambda x : bool(int(x)), input())]
// for i in range(Q):
//     T, L, R = map(int, input().split())
//     L -= 1; R -= 1
//     for i in range(L, R + 1):
//         A[i] = not(A[i])
//     best = 0
//     run = 1
//     # print(A)
//     for i in range(1, N):
//         if A[i] == A[i - 1]:
//             run += 1
//         else:
//             best = max(best, run)
//             run = 1
//     best = max(best, run)
//     print(best)