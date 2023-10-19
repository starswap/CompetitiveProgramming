#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1'000'000'000 + 7;
long long fact[1000001];

void prep_facts() {
    fact[0] = 1;
    for (int i = 1; i < 1000001; ++i) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
}

int main() {
    prep_facts();

    int N, H;
    cin >> N >> H;
    vector<int> k(H, 0);

    // Consider the no-house people as an extra "peaceful" house who won't riot
    int peaceful_no_house = N;
    for (int i = 0; i < H; ++i) {
        cin >> k[i];
        peaceful_no_house -= k[i];
    }
    k.push_back(peaceful_no_house);

    vector<long long> dp(H + 2, 0); // number of riots in the first h houses where the last house is peaceful
                                    // dp[0] is unused
                                    // dp[1] must be 0
    
    int num_knights = k[0] + k[1]; // knights in the first h houses
    for (int h = 2; h < H + 2; ++h) {
        long long k_0_to_i = 0;
        for (int i = 0; i < h - 1; ++i) {
            k_0_to_i += k[i];
            dp[h] += (fact[k_0_to_i] * fact[num_knights - k_0_to_i]) % MOD;
            dp[h] %= MOD;
            dp[h] -= (dp[i + 1] * fact[num_knights - k_0_to_i]) % MOD; // we double counted these
            dp[h] %= MOD;
        }
        num_knights += k[h];
    }
    cout << (fact[N] - dp[H + 1] + MOD) % MOD << endl; // ans = number of riots in the first H + 1 houses where the last house is peaceful
    return 0;
}