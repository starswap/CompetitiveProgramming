#include <bits/stdc++.h>
using namespace std;

long long solve(long long L, long long R) {
    
    long long i = 1;
    long long total = 0;
    long long bsL, bsR, nextI, newL, oldL, newR, M;

    while (i < L) {

        bsL = i; // not included
        bsR = L; // included
        while (bsR - bsL > 1) {
            M = (bsL + bsR)/2;
            if ( ((L + M - 1) / M) == ( (L + i - 1) / i)) { // we want to go for a higher i
                bsL = M;
            }
            else { // this is ok and we want to consider it. 
                bsR = M;
            }
        }
        nextI = bsR;
        
        newL = ((L + nextI - 1)/ nextI);
        oldL = ((L + i - 1)/ i);
        newR = R / (nextI + 1);

        total += max(0LL, min(oldL - 1, newR) - newL + 1);

        i = nextI;
    }

    i = 1;
    newL = ((L + i - 1)/ i);
    newR = R / (i + 1);
    total += max(0LL, newR - newL + 1);

    return total;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    
    for (int t=0; t<T; t++) {
        long long L, R;
        cin >> L >> R;
        cout << solve(L, R) << endl;
    }
        
}