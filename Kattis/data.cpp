#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 14;
const int MAX_V = 1000;
const int MAX_PFs = MAX_N * MAX_V + 10;

// Note that global arrays are filled with 0 by default
int S[MAX_N];                     // Specialness of data
int dp[(1 << MAX_N)];             // Best score if we partition this subset
int ss[(1 << MAX_N)] ;            // Subset Sum of S
int distinctPFs[MAX_PFs];         // # distinct prime factors of x

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // Input
    int N; cin >> N;
    for (int i = 0; i < N; ++i)
        cin >> S[i];

    // Subset Sums
    for (int s = 0; s < (1 << N); ++s)
        for (int t = 1, i = 0; i < N; t <<= 1, i++)
            if (s & t) // if ith element is in s
                ss[s] += S[i];

    // Modified Sieve
    for (int i = 2; i < MAX_PFs; ++i)
        if (distinctPFs[i] == 0) // it's prime
            for (int j = i; j < MAX_PFs; j += i) // Count distinct prime factors of multiples
                distinctPFs[j]++;
     
    // Bottom Up DP
    dp[0] = 0;
    for (int s = 1; s < (1 << N); ++s)
        for (int t = 1; t <= s; ++t)
            if ((s | t) == s)  // t is a subset of s
                dp[s] = max(dp[s], dp[s ^ t] + distinctPFs[ss[t]]);

    // Output Answer
    cout << dp[(1 << N) - 1] << endl;
    return 0;
}