#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

map<ll, int> new_size_to_value;
vector<ll> sizes;

int query(ll i) {
    if (new_size_to_value.count(i)) {
        return new_size_to_value[i];
    } else {
        auto it = lower_bound(sizes.begin(), sizes.end(), i);
        it--;
        ll old_size = *it;
        return query((i - 1LL) % old_size + 1LL);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, Q;
        cin >> N >> Q;
        ll size = 0;
        sizes.clear();
        new_size_to_value.clear();
        bool done = false;
        for (int i = 0; i < N; ++i) {
            int b, x;
            cin >> b >> x;
            if (!done) {
                if (b == 1) {
                    size++;
                    new_size_to_value[size] = x;
                } else {
                    if (size >= 2'000'000'000'000'000'000 / (x + 1)) {done = true; continue;}
                    size *= (x + 1); // adds x copies
                }
                if (size > 1000000000000000000 || size < 0) {done = true; }
                else {sizes.push_back(size); }
            }
        }

        
        for (int q = 0; q < Q; ++q) {
            ll targ; cin >> targ;
            cout << query(targ) << " ";
        }
        cout << endl;

    }
    return 0;
}