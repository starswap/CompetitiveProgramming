#include <bits/stdc++.h>
using namespace std;


long long rangeAND(long long L, long long R) {
    long long answer = 0;
    for (long long bit=62; bit >= 0; bit--) {
        if ((L & (1LL << bit)) == (R & (1LL << bit))) {
            answer |= L & (1LL << bit);
        }
        else {
            break;
        }
    }
    return answer;
}

int main() {
    int T;
    cin >> T;
    for (int t=0;t<T;++t) {
        long long N, X;
        cin >> N >> X;

        long long L = N - 1;    // could not be equal to L
        long long R = (2e18);   // could be equal to R

        while (L + 1 < R) {
            long long M = (L + R) / 2;
            long long currAND = rangeAND(N,M);
            if ((currAND & X) >= X && (currAND != X)) { // has too many bits set
                L = M;
            }
            else {
                R = M;
            }
        }

        
        long long ans = L + 1;

        if (rangeAND(N,ans) == X)
            cout << ans << endl;
        else
            cout << -1 << endl;


    }

}