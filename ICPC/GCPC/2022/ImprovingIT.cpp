#include <bits/stdc++.h>
using namespace std;

// const int N_MAX = 500001;
// const int M_MAX = 500001;
// long long dp[N_MAX+1][M_MAX+1]; // dp[timeT][lastCPUBoughtNAgo]

int main() {
    int N,M;
    scanf("%d %d",&N,&M);
    vector<int> CPUCosts(N+1);
    vector<vector<int>> CPUSale(N+1,vector<int>(M+2));
    vector<vector<long long>> dp(N+2,vector<long long>(M+2));

    for (int n=1;n<N+1;++n) {
        scanf("%d",&CPUCosts[n]);
        for (int p=1;p<=min(M,N-n+1);p++) {
            scanf("%d",&CPUSale[n][p]);
        }
    }


    for (int nAgo=1;nAgo<=M;nAgo++) {
        if (N+1-nAgo>=1)
            dp[N+1][nAgo] = -CPUSale[N+1-nAgo][nAgo];
    }

    for (int t=N;t>0;--t) {
        for (int nAgo=1;nAgo<=M-1;nAgo++) {
            if (t-nAgo >= 1) {
                dp[t][nAgo] = min(dp[t+1][nAgo+1],dp[t+1][1]+CPUCosts[t]-CPUSale[t-nAgo][nAgo]);
            }
        }
        if (t-M >= 1)
            dp[t][M] = dp[t+1][1] + CPUCosts[t] - CPUSale[t-M][M];
    }
    cout << dp[2][1]+CPUCosts[1] << endl;

    return 0;
}