#include <bits/stdc++.h>
using namespace std;


int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, G; cin >> N >> G;
        vector<int> E(N);
        for (int n = 0; n < N; ++n) {
            cin >> E[n];
        }

        sort(E.begin(), E.end());
        int best_dist = 1'000'000'000;
        int best_n = -1;
        for (int n = N - 1; n >= 0; --n) {
            if (abs(G - E[n]) < best_dist) {
                best_dist = abs(G - E[n]);
                best_n = N - n;
            }
        }

        cout << "Case #" << t << ": " << best_n << " " << best_dist << endl; 
    }
    return 0;
}
