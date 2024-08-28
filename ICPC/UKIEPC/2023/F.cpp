#include <bits/stdc++.h>
using namespace std;
int N, C;

int B_MAX = 20;

int main() {
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> C;
    
    vector<int> songs(2*N);
    for (int n = 0; n < N; ++n) {
        cin >> songs[n];
        songs[N + n] = songs[n];
    }

    vector<vector<int>> next(B_MAX, vector<int>(2 * N + 1, 2 * N)); // "just before"
    int l = 0;
    int r = -1;
    int total = 0;
    while (l < 2 * N) {
        if (total < C) {
            r++;
            if (r >= 2 * N) break; // next add will be off the end
            total += songs[r];
        }
        else if (total >= C) {
            next[0][l] = r + 1;
            total -= songs[l];
            l++;
        }
    }
    
    for (int b = 1; b < B_MAX; ++b) {
        for (int n = 0; n < 2 * N; ++n) {
            next[b][n] = next[b - 1][next[b - 1][n]];
        }
    }
    
    for (int n = 0; n < N; ++n) {
        int ans = 0;
        int m = n;
        for (int b = B_MAX - 1; b >= 0; b--) {
            if (next[b][m] <= n + N - 1) {
                ans += (1 << b);
                m = next[b][m];
            }
        }
        cout << ans;
        if (n != N - 1) cout << " "; 
    }

    cout << endl;

    return 0;
}