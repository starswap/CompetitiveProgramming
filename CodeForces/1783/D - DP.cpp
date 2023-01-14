#include <bits/stdc++.h>
using namespace std;
// dp[i][value of i + 2]
// according to editorial

const int n = 300;
const int A = 300;
const int MOD = 998244353;
int N;

int dp[n+1][2*A*A+1];

vector<int> a;

int f(int x) {
    return x + A*A;
}

int doDP(int i, int y) {
    if (i >= N-2)
        return 1;
    else if (dp[i][f(y)] != -1)
        return dp[i][f(y)];
    else if (y == 0)
        return dp[i][f(y)] = doDP(i+1,a[i+2] + y) % MOD;
    else
        return dp[i][f(y)] = (doDP(i+1,a[i+2] + y) + doDP(i+1,a[i+2] - y)) % MOD;
}

int main() {
    cin >> N;
    a.assign(N,0);

    for (int n=0;n<N;++n) {
        cin >> a[n];
    }
 
    // initialise
    for (int i=0;i<n+1;++i) {
        for (int j=0;j<2*A*A+1;++j) {
            dp[i][j] = -1;
        }
    }
    cout << doDP(0,a[1]) << endl; 
}
