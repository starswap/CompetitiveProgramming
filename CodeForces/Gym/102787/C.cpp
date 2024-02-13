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
    int num_ones;
    int num_zeros;

    subtree_runs(bool lm, int lrl, bool rm, int rrl, 
    int l, int br, int num_ones, int num_zeros):left_most(lm), left_run_length(lrl), right_most(rm), 
    right_run_length(rrl), length(l), best_run(br), num_ones(num_ones), num_zeros(num_zeros) {}
    
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
        return subtree_runs(v1.left_most, new_lrl, v2.right_most, new_rrl, v1.length + v2.length, new_br, v1.num_ones + v2.num_ones, v1.num_zeros + v2.num_zeros);
    }
};
const subtree_runs subtree_runs::empty = subtree_runs(false, 0, false, 0, 0, 0, 0, 0);

struct Treap {
    int priority;
    bool value;
    int totalnodes;
    bool lazy_toggle;
    bool lazy_reverse;
    bool lazy_sort;
    subtree_runs s;
    Treap* par;

    vector<Treap *> children;
    Treap(bool v):value(v), s(value, 1, value, 1, 1, 1, value == 1, value == 0) {
        totalnodes = 1;
        children.assign(2, nullptr);
        lazy_toggle = false;
        lazy_reverse = false;
        lazy_sort = false;
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

void propagate(Treap* t) {
    if (t == nullptr) return;
    if (t->lazy_sort) {
        t->lazy_sort = false;
        for (Treap* c : t->children) {
            if (c != nullptr) {
                c->lazy_sort = true; 
                if (c->lazy_reverse) {
                    c->lazy_reverse = false;
                }
                if (c->lazy_toggle) {
                    c->lazy_toggle = false;
                }
                     
                if (t->children[0] == c) { // we are first child
                    c->s.num_zeros = min(t->s.num_zeros, c->totalnodes); //
                    c->s.num_ones = c->totalnodes - c->s.num_zeros;
                } else if (t->children[1] == c) {
                    c->s.num_ones = min(t->s.num_ones, c->totalnodes);
                    c->s.num_zeros = c->totalnodes - c->s.num_ones;
                } else {assert(0 == 1);}

                c->s.left_most = (c->s.num_zeros > 0) ? false : true;
                c->s.right_most = (c->s.num_ones > 0) ? true : false;
                c->s.left_run_length = (c->s.num_zeros > 0) ? c->s.num_zeros : c->s.num_ones;
                c->s.right_run_length = (c->s.num_ones > 0) ? c->s.num_ones : c->s.num_zeros;
                c->value = (c->s.num_zeros > treap_size(c->children[0])) ? false : true;
                c->s.best_run = max(c->s.left_run_length, c->s.right_run_length);
            }
        }
    }
    if (t->lazy_toggle) {
        t->value = !t->value;
        t->s.left_most = !t->s.left_most; 
        t->s.right_most = !t->s.right_most;
        t->lazy_toggle = false;
        swap(t->s.num_ones, t->s.num_zeros);
        for (Treap* c : t->children) {if (c != nullptr) {c->lazy_toggle = !c->lazy_toggle;}}
    }
    if (t->lazy_reverse) {
        swap(t->s.left_most, t->s.right_most);
        swap(t->s.right_run_length, t->s.left_run_length);
        t->lazy_reverse = false;
        for (Treap* c : t->children) {if (c != nullptr) {c->lazy_reverse = !c->lazy_reverse;}}
        swap(t->children[0], t->children[1]);
    }
}

subtree_runs get_subtree_run(Treap* t) {
    return (t == nullptr) ? (subtree_runs::empty) : t->s;
}

void recalc(Treap* t) {
    if (t == nullptr) return;
    t->totalnodes = 1;
    for (Treap* c : t->children) t->totalnodes += treap_size(c);
    propagate(t);
    propagate(t->children[0]);
    propagate(t->children[1]);
    t->s = ((get_subtree_run(t->children[0]) + subtree_runs(t->value, 1, t->value, 1, 1, 1, t->value == true, t->value == false)) + get_subtree_run(t->children[1]));
}

pair<Treap*, Treap*> split(Treap *t, int nleft) {
    if (t == nullptr) {return {nullptr, nullptr};}
    propagate(t);
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
        propagate(tl);
        propagate(tr);
        tl->children[1] = merge(tl->children[1], tr);
        if (tl->children[1] != nullptr) tl->children[1]->par = tl;
        recalc(tl);
        return tl;
    } else {
        propagate(tr);
        propagate(tl);
        tr->children[0] = merge(tl, tr->children[0]);
        if (tr->children[0] != nullptr) tr->children[0]->par = tr;
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
    propagate(t);
    t->lazy_toggle = !t->lazy_toggle;
}

void reverse(Treap *t) {
    propagate(t);
    t->lazy_reverse = !t->lazy_reverse;
}

void sort_treap(Treap *t) {
    propagate(t);
    t->s.left_most = (t->s.num_zeros > 0) ? false : true;
    t->s.right_most = (t->s.num_ones > 0) ? true : false;
    t->s.left_run_length = (t->s.num_zeros > 0) ? t->s.num_zeros : t->s.num_ones;
    t->s.right_run_length = (t->s.num_ones > 0) ? t->s.num_ones : t->s.num_zeros;
    t->s.best_run = max(t->s.left_run_length, t->s.right_run_length);
    t->value = (t->s.num_zeros > treap_size(t->children[0])) ? false : true;
    t->lazy_sort = true;
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

Treap* type2query(Treap* t, int l, int r) {
    auto [i, r1] = split(t, l - 1);
    auto [j, k] = split(r1, r - l + 1);
    reverse(j); 
    Treap* m1 = merge(i, j);
    return merge(m1, k);
}

Treap* type3query(Treap* t, int l, int r) {
    auto [i, r1] = split(t, l - 1);
    auto [j, k] = split(r1, r - l + 1);
    sort_treap(j); 
    Treap* m1 = merge(i, j);
    return merge(m1, k);
}

void in_order_traversal(Treap* t, vector<int>& target) {
    if (t != nullptr) {
        propagate(t);
        in_order_traversal(t->children[0], target);
        target.push_back(t->value);
        in_order_traversal(t->children[1], target);
    }
}

int main() {
    srand(10);
    cin.tie(0)->sync_with_stdio(0);
    int N, Q; cin >> N >> Q;
    string s; cin >> s;
    
    Treap *t = init(s);
    for (int q = 0; q < Q; ++q) {
        int qt, a, b;
        cin >> qt >> a >> b;
        if (qt == 1) {
            t = type1query(t, a, b);
        } else if (qt == 2) {
            t = type2query(t, a, b);
        } else if (qt == 3) {
            t = type3query(t, a, b);
        }
        cout << get(t) << endl;
    }
    delete t;
    return 0;
}
