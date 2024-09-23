#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

int main() {
    srand(0);
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N; cin >> N;
        vector<pair<double, double>> ants(N);
        for (int n = 0; n < N; ++n) {
            cin >> ants[n].first;
            cin >> ants[n].second;
        }

        int maxi = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                const double m = (ants[i].second - ants[j].second) / (ants[i].first - ants[j].first);
                const double c = (ants[i].second) - m * ants[i].first;

                int on_line = 0;
                for (const auto &[x, y] : ants) {
                    on_line += (fabs(y - (m * x + c)) < EPS);
                }
                maxi = max(maxi, on_line);

            }
        }
        
        int ans = N - maxi;
        cout << "Case #" << t << ": " << ans << endl; 
    }
    return 0;
}
