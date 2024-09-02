// Not done yet
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 2000000000;
const int UNDEF = -1;
const int MAX_N = 2000;
int DP[MAX_N + 5][MAX_N + 5];

int N, L;
vector<pair<int, int>> BA;

// cost to read n messages in subarray starting at i)
// where the array has been presorted by B value
int doDP(int i, int n) {
    if (n == 0) return 0;
    else if (i == N) return INF;
    else if (DP[i][n] != UNDEF) return DP[i][n];
    else {
        
        // read this message
        BA[i].second + BA[7]
        
        // don't read this message
        return DP[i][n]; 
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> L;
        BA.resize(N);

        for (int i = 0; i < N; ++i) {
            cin >> BA[i].first;
            cin >> BA[i].second;
        }

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                DP[i][j] = UNDEF;
            }
        }

        sort(BA.begin(), BA.end());
        for (int i = N; i >= 0; i--) {
            if (doDP(0, i) < L) {
                cout << i << endl;
            } 
        }
    }
    return 0;
}