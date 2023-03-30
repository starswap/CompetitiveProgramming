#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = static_cast<ll>(1e9+7);

const int MAX_R = 100;
const int MAX_C = 100;
const int MAX_L = 200;
ll dp[MAX_R][MAX_C][MAX_L]; // dp[r][c][l]

int R, C, L;

int main() {
    cin >> R >> C >> L;

    ll prevSum, currSum;
    for (int l = 0; l < L; ++l) {
        currSum = 0;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (l == 0) dp[r][c][l] = 1;
                else {
                    ll forbidden = 0;
                    for (int dr = -1 ; dr <= 1; ++ dr) {
                        for (int dc = -1 ; dc <= 1; ++dc) {
                            if (r + dr < 0 || r + dr >= R || c + dc < 0 || c + dc >= C) continue;
                            forbidden += dp[r + dr][c + dc][l - 1];
                        }
                    }
                    dp[r][c][l] = prevSum - forbidden;
                    dp[r][c][l] %= MOD;
                }
                currSum += dp[r][c][l];
                currSum %= MOD;
            }
        }
        prevSum = currSum;
    }
    cout << (prevSum + MOD) % MOD << endl;


    return 0;
}