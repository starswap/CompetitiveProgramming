#include <bits/stdc++.h>
using namespace std;

int N;
vector<int> p;
vector<long long> f;
vector<long long> l;
vector<bool> unknown;
set<int> leaves;
vector<vector<int>> children;

void bottom_up() {
    for (int n = N - 1; n >= 0; n--) if (leaves.count(n)) l[n] = max(1LL, f[n]);
    for (int n = N - 1; n >= 0; n--) {
        if (n >= 1) {
            l[p[n]] += max(f[n], l[n]); if (unknown[n]) f[n] = l[n];
        }
        bool all_known = true;
        for (int child : children[n]) {
            all_known &= !unknown[child];
        }
        if (all_known && !leaves.count(n)) unknown[n] = false;
    }
    if (f[0] == 0) f[0] = l[0];
}

bool top_down() {
    if (unknown[0]) return false;
    bool ok = true;
    for (int i = 0; i < N; ++i) {
        if (f[i] > l[i]) {
            int total_unk = 0;
            int last_unk;
            for (int child : children[i]) {
                total_unk += unknown[child];
                if (unknown[child]) last_unk = child;
            }
            if (total_unk > 1 || (total_unk == 0 && !leaves.count(i))) {
                ok = false;
                break;
            } else if (total_unk == 1) {
                f[last_unk] += f[i] - l[i];
            }
        } else if (f[i] < l[i]) {
            ok = false;
            break;
        }
    }
    return ok;
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N;
    p.assign(N, 0);
    f.assign(N, 0);
    l.assign(N, 0);
    children.assign(N, vector<int>());
    unknown.assign(N, false);

    for (int i = 1; i < N; ++i) {
        cin >> p[i];
        p[i]--;
        children[p[i]].push_back(i);
    }

    for (int i = 0; i < N; ++i) {
        leaves.insert(i);
    }

    for (int i = 0; i < N; ++i) {
        leaves.erase(p[i]);
    }

    for (int i = 0; i < N; ++i) {
        cin >> f[i];
        if (f[i] == 0) {unknown[i] = true;}
    }

    bottom_up();
    if (!top_down()) {
        cout << "impossible" << endl;
    } else {
        for (int i = 0; i < N; ++i) {
            cout << f[i] << endl;
        }
    }

    return 0;
}