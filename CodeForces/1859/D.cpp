#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct interval {
    int a, b;
    int l, r;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<interval> is(N);

        for (int n = 0; n < N; ++n) {
            cin >> is[n].l;
            cin >> is[n].r;
            cin >> is[n].a;
            cin >> is[n].b;
        }

        // Lambda syntax to produce normal ascending sort order.
        sort(is.begin(), is.end(), [](interval i, interval j) {
            return i.b < j.b;
        });
        map<int, int> l_to_b;
        int L = is[N - 1].l;
        int B = is[N - 1].b;
        for (int i = N - 1; i >= 0; --i) {
            if (is[i].b >= L) {
                L = min(L, is[i].l);
            } else {
                l_to_b[L] = B;
                L = is[i].l;
                B = is[i].b;
            }
        }
        l_to_b[L] = B;
        int Q;
        cin >> Q;
        for (int q = 0; q < Q; ++q) {
            int x;
            cin >> x;
            auto it = l_to_b.upper_bound(x);
            if (it == l_to_b.begin()) { // all are greater
                cout << x << " ";
            } else {
                it--;
                cout << max(x, it->second) << " ";
            }
        }
        cout << endl;
    }
    return 0;
}
