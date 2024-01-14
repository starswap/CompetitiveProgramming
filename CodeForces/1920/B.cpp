#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N, K, X; cin >> N >> K >> X;
        vector<int> A(N);
        for (int k = 0; k < N; ++k) {
            cin >> A[k];
        }

        sort(A.begin(), A.end());
        reverse(A.begin(), A.end());
        int score = 0;
        for (int i = 0; i < N ; ++i) {
            if (i < X) {score -= A[i];}
            else {score += A[i];}
        }
        int best_score = score;

        for (int k = 0; k < K; ++k) {
            int delta = A[k];
            if (k + X < N) {
                delta -= 2 * A[k + X];
            }
            score += delta;
            best_score = max(score, best_score);
        }
        cout << best_score << endl;

    }
    return 0;
}