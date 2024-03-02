#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int UNDEF = -1;
const int INF = 100000;
const int MAX_N = 100;
int DP[MAX_N + 5][MAX_N + 5][MAX_N + 5];
int A[MAX_N];
int N;

int doDP(int i, int j, int k) {
  if (i == N) {
    return ((j == N && k == N) ? 0 : INF);
  } else if (DP[i][j][k] != UNDEF) {
    return DP[i][j][k];
  } else {
    DP[i][j][k] = doDP(i + 1, j, k);
    if (i - j + 1 <= A[i]) { // backwards covers
      DP[i][j][k] = min(DP[i][j][k], 1 + doDP(i + 1, max(i + 1, k), (k <= i) ? i + 1 : k));
    }
    if (k - i + 1 <= A[i]) { // forwards covers
      int newK = min(N, i + A[i]);
      DP[i][j][k] = min(DP[i][j][k], 1 + doDP(i + 1, (j >= i ? newK : j), newK));
    }
    return DP[i][j][k];
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int T;
  cin >> T;
  while (T--) {
    cin >> N;
    for (int n = 0 ; n < N; ++n) {
      cin >> A[n];
    }
    for (int i = 0; i <= N; ++i) {
      for (int j = 0; j <= N; ++j) {
        for (int k = 0; k <= N; ++k) {
          DP[i][j][k] = UNDEF;
        }
      }
    }
    cout << doDP(0, 0, 0) << endl;
  }
  return 0;
}
