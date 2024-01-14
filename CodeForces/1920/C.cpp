#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int A[200005];
int D[200];

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }

        int divs = 0;
        for (int i = 1; i * i <= N; ++i) {
            if (N % i == 0) {
                D[divs] = i; divs++;
                if (N / i != i) {D[divs] = N / i; divs++;}
            }
        }

        int score = 0;
        for (int d = 0; d < divs; ++d) {
            int gcd = -1;
            for (int s = 0 ; s < N - D[d]; ++s) {
                if (gcd == -1) {gcd = abs(A[s + D[d]] - A[s]);}
                else {gcd = __gcd(gcd, abs(A[s + D[d]] - A[s]));}
            }
            if (gcd != 1) {score += 1;}
        }

        cout << score << endl;
    }
    return 0;
}