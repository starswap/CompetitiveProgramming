#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 100;
const int MAX_X = 100;
const int INF = 10000;
const int UNDEF = -1;
int DP[MAX_N][MAX_N][MAX_X + 1];
int DP_BAR[MAX_N][MAX_N][MAX_X + 1];
int A[MAX_N];
int N, X;

static int doDP(int l, int r, int x);
static int doDP_BAR(int l, int r, int x);

int doDP_BAR(int l, int r, int x) {
    while (l < N && A[l] != x) l++;
    while (r >= 0 && A[r] != x) r--;

    if (l > r) return 0;
    else if (l == r) return A[l] == x; 
    else if (DP_BAR[l][r][x] != UNDEF) return DP_BAR[l][r][x];
    else {
        int ans = INF;
        for (int i = 1; i <= X; ++i) {
            if (i == x) continue;
            ans = min(ans, doDP(l, r, i));
        }
        for (int s = l; s < r; ++s) {
            ans = min(ans, doDP_BAR(l, s, x) + doDP_BAR(s + 1, r, x));
        }
        DP_BAR[l][r][x] = ans;
        return ans;
    }
}

int doDP(int l, int r, int x) {
    while (l < N && A[l] == x) l++;
    while (r >= 0 && A[r] == x) r--;

    if (l > r) return 0;
    else if (l == r) return A[l] != x; 
    else if (DP[l][r][x] != UNDEF) return DP[l][r][x];
    else {
        int ans = 1 + doDP_BAR(l, r, x);
        for (int s = l; s < r; ++s) {
            ans = min(ans, doDP(l, s, x) + doDP(s + 1, r, x));
        }
        DP[l][r][x] = ans;
        return ans;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        fill(&DP[0][0][0], &DP[0][0][0] + sizeof(DP) / sizeof(DP[0][0][0]), UNDEF);
        fill(&DP_BAR[0][0][0], &DP_BAR[0][0][0] + sizeof(DP_BAR) / sizeof(DP_BAR[0][0][0]), UNDEF);

        cin >> N >> X;
        for (int n = 0 ; n < N ; ++n) {
            cin >> A[n];
        }

        int ans = INF;
        for (int y = 1; y <= X; ++y) {
            ans = min(ans, doDP(0, N - 1, y));
        }
        cout << ans << endl;
    }
    return 0;
}

// Bad case explaining why we need the cyclic DP
// 1
// 30 3
// 2 2 3 1 3 1 2 1 2 1 2 1 2 3 1 1 2 3 1 2 2 1 3 3 3 2 2 1 3 2
//           ---------------
// 2 2 3 1 3 3 3 3 3 3 3 3 3 3 1 1 2 3 1 2 2 1 3 3 3 2 2 1 3 2
//                                     -------
// 2 2 3 1 3 3 3 3 3 3 3 3 3 3 1 1 2 3 3 3 3 3 3 3 3 2 2 1 3 2
//                                 ---------------------
// 2 2 3 1 3 3 3 3 3 3 3 3 3 3 1 1 1 1 1 1 1 1 1 1 1 1 1 1 3 2
//     -----------------------------------------------------
// 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2

// Generator:
// import random
// N = 30
// X = 3
// T = 500 // N

// print(T)
// for i in range(T):
//     print(N, X)
//     print(*[random.randint(1, X) for i in range(N)])