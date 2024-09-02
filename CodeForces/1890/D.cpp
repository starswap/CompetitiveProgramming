#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, C; cin >> N >> C;
        vector<long long> a(N);
        for (int n = 0; n < N; ++n) {
            cin >> a[n];
        }
        priority_queue<tuple<double, int, int>> pq;
        for (int n = 0; n < N; ++n) {
            pq.emplace(static_cast<double>(a[n]) / static_cast<double>(n + 1), a[n], n + 1);
        }
        bool impossible = false;
        while (pq.size() > 1) {
            auto [score, popn, i] = pq.top(); pq.pop();    
            auto [score2, popn2, j] = pq.top(); pq.pop();    
            if (popn + popn2 >= i * j * C) {
                long long new_popn = popn + popn2;
                int k = min(i, j);
                pq.emplace((double) new_popn / (double) k, new_popn, k);
            } else {
                impossible = true;
                break;
            }
        }
        if (impossible) {
            cout << "No" << endl;
        } else {
            cout << "Yes" << endl;
        }
        

    }
    return 0;
}