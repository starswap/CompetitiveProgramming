#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int MAX_N = 200000;
ll dp[MAX_N + 5];
ll costs[MAX_N + 5];
vector<pair<int, int>> exhibitions;

int main() {
    int N, M; cin >> N >> M;
    exhibitions.resize(M);
    for (int n = 0; n < N; ++n) {
        cin >> costs[n + 1];
    }

    for (int m = 0; m < M; ++m) {
        cin >> exhibitions[m].first >> exhibitions[m].second;
    }

    exhibitions.emplace_back(0, 0);

    sort(exhibitions.begin(), exhibitions.end(), [](const pair<int, int>& a, const pair<int, int>& b){return a.second < b.second;});
    int k = 0;

    int start_point = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> window;

    for (int i = 0; i < N + 2; ++i) {
        ll dp_score = 0, idx = 0;
        if (!window.empty()) {
            tie(dp_score, idx) = window.top();
            while (idx < start_point) {
                window.pop();
                tie(dp_score, idx) = window.top();
            }
        }

        dp[i] = costs[i] + dp_score;
    
        while (exhibitions[k].second == i) {
            start_point = max(start_point, exhibitions[k].first);
            k++;
        }
        window.emplace(dp[i], i);
    }

    cout << dp[N + 1] << endl;

    return 0;
}

