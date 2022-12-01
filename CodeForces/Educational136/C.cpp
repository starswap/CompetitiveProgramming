#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long choose(long long n, long long r) {
    //    n!            (n-1)! * n          n
    // -------  = ------------------- =  ----- * (n-1) C r
    // r!(n-r!) = r! (n-1-r)! * (n-r)    n - r
    // 
    if (n == r) {return 1;}
    else {
        return ((n * choose(n-1,r))/(n-r));
    }
}

long long chooseMod(long long n, long long r, long long mod) {
    return choose(n, r) % mod; // We can't mod as we go along when computing the Choose function as we require division
                               // which is not compatible with mod, but the largest input here is 60, and 60 C 30 fits inside a long long pre-mod
}

pair<long long,long long> alexDrawBoris(int n, bool alexHasHighest, bool alexFirst) {
    // returns (numAlexWins, numBorisWins). Draws can be computed at the end

    if (n == 2) {
        if (alexHasHighest && alexFirst) return make_pair(1,0);
        else if (!alexHasHighest && !alexFirst) return make_pair(0,1);
        else return make_pair(0,0);
    }

    long long alexWins, borisWins;
    if (alexFirst) { 
        if (alexHasHighest) {
            alexWins = chooseMod(n - 1, n/2 - 1,MOD); // number of ways to allocate the other cards to Alex
            borisWins = 0;
        }
        else {             // Either :  // alex has next highest so he plays it to force boris to use his highest
                                        // alex does not have next highest, so boris wins
            
            auto [alexSit1, borisSit1] = alexDrawBoris(n-2,true , !alexFirst);
            auto [alexSit2, borisSit2] = alexDrawBoris(n-2,false, !alexFirst);

            alexWins = 0 + (alexSit1 + alexSit2) % MOD;
            borisWins = chooseMod(n - 2, n/2 - 2,MOD) + (borisSit1 + borisSit2) % MOD;

        }
    }  
    else { // Boris first
        if (!alexHasHighest) {
            borisWins = chooseMod(n - 1, n/2 - 1,MOD); // number of ways to allocate the other cards to Alex
            alexWins = 0;
        }
        else { 
            auto [alexSit1, borisSit1] = alexDrawBoris(n-2,true , !alexFirst);
            auto [alexSit2, borisSit2] = alexDrawBoris(n-2,false, !alexFirst);

            alexWins = chooseMod(n-2,n/2-2,MOD)  + ((alexSit1 + alexSit2) % MOD);
            borisWins = 0 + (borisSit1 + borisSit2) % MOD;
        }
    }
    return make_pair(alexWins % MOD, borisWins % MOD);
}


int main() {
    int T;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
        int n;
        scanf("%d",&n);
        auto [alex1, boris1] = alexDrawBoris(n, true, true);
        auto [alex2, boris2] = alexDrawBoris(n, false, true);
        long long totalMod = chooseMod(n, n / 2, MOD);

        long long alex = (alex1 + alex2) % MOD;
        long long boris = (boris1 + boris2) % MOD;
        long long draw = (totalMod - alex - boris + MOD) % MOD;

        cout << alex << " " << boris << " " << draw << endl;

    }
}