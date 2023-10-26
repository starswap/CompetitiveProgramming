#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N;
        cin >> N;
        vector<int> ns(N);
        for (int n = 0; n < N; ++n) {
            cin >> ns[n];
        }


        vector<int> first;
        set<int> seen;
        for (int i = 0 ; i < N; ++i) {
            if (!seen.count(ns[i])) {
                seen.insert(ns[i]);
                first.push_back(i);
            }
        }

        vector<int> last;
        seen.clear();
        for (int i = N - 1 ; i >= 0; --i) {
            if (!seen.count(ns[i])) {
                seen.insert(ns[i]);
                last.push_back(i);
            }
        }

        reverse(last.begin(), last.end());

        long long ans = 0;
        for (int s : first) {
            long long start_idx = lower_bound(last.begin(), last.end(), s) - last.begin(); // 0 1 2 3
            ans += (long long) last.size() - start_idx;
        }

        cout << ans << endl;
    }
    return 0;
}

 // first occurrence of the first one
 // last occurence of the last one