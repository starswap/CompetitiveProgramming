#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int nearest_b(int a, const multiset<int> &Bs) {
    auto after = Bs.lower_bound(a);
    if (after == Bs.begin()) {
        return *after;
    } else if (after == Bs.end()) {
        return *prev(after);
    }
    else {
        int afterVal = *after;
        int beforeVal = *prev(after);
        if (abs(a - afterVal) < abs(a - beforeVal)) return afterVal;
        else return beforeVal;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<pair<int, int>> AB(N);
        multiset<int> Bs;
        for (int n = 0; n < N; ++n) {
            cin >> AB[n].first;
            cin >> AB[n].second;
            Bs.insert(AB[n].second);
        }
        sort(AB.begin(), AB.end());

        int max_b = -1000000000;
        int ans = 1000000005;
        for (int n = N - 1; n >= 0; --n) {
            // cout << ans << endl;
            auto [a, b] = AB[n];
            Bs.erase(Bs.find(b));
            // buy A
            int chosen_b = max_b;
            if (Bs.size() > 0) chosen_b = max(chosen_b, nearest_b(a, Bs));
            ans = min(ans, abs(a - chosen_b));
            ans = min(ans, abs(a - max_b));

            // bought that b
            max_b = max(max_b, b);
        }
        cout << ans << endl;
    }
    return 0;
}