#include <bits/stdc++.h>
using namespace std;

int N, P;
const double INF = 10000000;
const int MAX_P = 101;
vector<double> posts;
double dp[MAX_P][MAX_P][MAX_P];


double doDP(int pi1, int p, int p_curr) {
    if (p_curr == N) {
        return 0.5 * abs(sin(posts[pi1] - posts[0]));
    } else if (dp[pi1][p][p_curr] != -1) {
        return dp[pi1][p][p_curr];
    } else {
        // Option 1: take this one - if pi1 undefined - make it pi1, else make it pi2.
        // Option 2: don't take this one - i.e. preserve pi1, pi2

        double take;
        if (p == 0) take = -INF;
        else {
            double this_tri = 0.5 * sin(posts[p_curr] - posts[pi1]);
            take = this_tri + doDP(p_curr, p - 1, p_curr + 1);
        }
        double leave = doDP(pi1, p, p_curr + 1);
        dp[pi1][p][p_curr] = max(take, leave);
        return dp[pi1][p][p_curr];
    }
}

int main() {
    cin >> N >> P;
    posts.assign(N, 0);
    for (int n  = 0; n < N; ++n) {
        cin >> posts[n];
        posts[n] /= 180;
        posts[n] *= M_PI;
    }

    for (int i = 0; i < MAX_P; ++i) {
        for (int j = 0; j < MAX_P; ++j) {
            for (int k = 0; k < MAX_P; ++k) {
                dp[i][j][k] = -1;
            }
        }
    }

    double best = 0;
    for (int i = 0; i < N; ++i) {
        rotate(posts.begin(), posts.begin() + 1, posts.end());
        for (int i = 0; i < MAX_P; ++i) {
           for (int j = 0; j < MAX_P; ++j) {
                for (int k = 0; k < MAX_P; ++k) {
                    dp[i][j][k] = -1;
                }
            }
        }
        best = max(doDP(0, P - 1, 0), best);
    }

    cout << fixed << setprecision(10) << best * 1000000 << endl;
    return 0;
}
