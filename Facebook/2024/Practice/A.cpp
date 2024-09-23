#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        ll N, K; cin >> N >> K;
        vector<int> S(N);
        for (int n = 0; n < N; ++n) {
            cin >> S[n];
        }
        ll mini = *min_element(S.begin(), S.end());
        ll time = mini * static_cast<ll>((N == 1) ? 1 : (2 * (N - 1) - 1));
        
        bool ans = (time <= K);
        cout << "Case #" << t << ": " << ((ans) ? "YES" : "NO") << endl; 
    }
    return 0;
}
