#include <bits/stdc++.h>


#define int long long
#define MULTITEST true

using namespace std;

const int MAX_V = 1e6;
int cnt[MAX_V];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < (2 * n) + 7; i++) {
        cnt[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    vector<pair<int, int> > comp = {};

    for (int i = 0; i <= (2 * n) + 7; i++) {
        if (cnt[i] != 0) {
            comp.push_back({i, cnt[i]});
        }
    }

    // {val, where_ended, how_much_left}
    stack <tuple<int, int, int>> unconnected;
    unconnected.push({1e9, 1e9, 0});

    int global_ans = 0;

    for (int i = comp.size() - 1; i >= 0; i--) {
        auto[val, amount] = comp[i];

        int no_of_1s_to_leave = 0;
        int inc_for_the_next = amount;

        if (amount > k) {
            no_of_1s_to_leave = amount - k;
            inc_for_the_next = k;
        }

        int local_ans = 0;
        int curr_val = val;

        while(no_of_1s_to_leave > 0) {
            auto [first_1, first_0, rest_amount] = unconnected.top();

            int no_of_1s_to_reach = first_1 - curr_val;

            if (no_of_1s_to_leave < no_of_1s_to_reach) {
                local_ans += no_of_1s_to_leave;
                curr_val += no_of_1s_to_leave;
                no_of_1s_to_leave = 0;

                continue;
            }

            unconnected.pop();
            
            local_ans += first_0 - curr_val;
            no_of_1s_to_leave -= no_of_1s_to_reach; 
            curr_val = first_0;

            no_of_1s_to_leave += rest_amount;
        }

        unconnected.push({val, curr_val, inc_for_the_next});
        global_ans = max(global_ans, local_ans);
    }

    cout << global_ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1; if (MULTITEST) cin >> T;
    while(T--) {
        solve();
    }
}
