#include <bits/stdc++.h>


#define int long long
#define MULTITEST true

using namespace std;

void solve() {
    int n, l, r;
    cin >> n >> l >> r;
    
    vector<int> guess(n);
    
    for (int i = 0; i < n; i++) {
        cin >> guess[i];
    }

    sort(guess.begin(), guess.end());

    int cnt_x = 0;
    int cnt_coef = 0;

    for (int i = 0; i <= n - 1 - i; i++) {
        if (guess[i] >= r) {
            int last = n - 1 - i;
            while (i <= last) {
                cnt_x--;
                cnt_coef += guess[i];
                i++;
            }

            break;
        }

        if (guess[n - 1- i] <= l) {
            int last = n - 1 - i;
            while (i <= last) {
                cnt_x++;
                cnt_coef -= guess[i];
                i++;
            }

            break;
        }

        cnt_coef += (guess[n - 1 - i] - guess[i]);
    }

    int ans = min(cnt_x * l, cnt_x * r) + cnt_coef;
    cout << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1; if (MULTITEST) cin >> T;
    while(T--) {
        solve();
    }
}
