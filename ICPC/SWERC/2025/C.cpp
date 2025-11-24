#include <bits/stdc++.h>


#define int long long
#define MULTITEST true

using namespace std;

void solve() {
    int N, M; cin >> N >> M;
    vector<vector<int>> tiles(N, vector<int>(M));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> tiles[i][j];
        }
    }

    vector<int> perm;
    set<int> seen;

    if (N == 1) {
        for (int i = 0; i < M / 2; ++i) {
            perm.push_back(tiles[0][i]);
        }
    } else if (N % 2 == 0 || M == 1) {
        for (int i = 0; i < N; ++i) {
            if (!seen.count(tiles[i][0])) {
                for (int j = 0; j < M; ++j) {
                    perm.push_back(tiles[i][j]);
                    seen.insert(tiles[i][j]);
                }
            }
        }
    } else {
        int intvl = 0;
        for (int i = M - 1; i >= 0; --i) {
            perm.push_back(tiles[intvl][i]);
        } 

        for (int i = 0; i < N - 1; ++i) {
            for (int j = 0; j < N; ++j) {
                if (tiles[j][M - 1] == tiles[intvl][M / 2 - 1]) {
                    intvl = j;
                    if (i != N - 2) {
                        for (int k = M / 2 - 1; k >= 0; --k) {
                            perm.push_back(tiles[intvl][k]);
                        }
                    }
                    break;
                }
            } 
        }
        reverse(perm.begin(), perm.end());
    }
    for (int x = 0; x < perm.size() - 1; ++x) {
        cout << perm[x] << " ";
    }
    cout << *perm.rbegin() << endl;
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int T = 1; if (MULTITEST) cin >> T;
    while(T--) {
        solve();
    }
}
