//Must compile with -Ofast

#include <bits/stdc++.h>

using namespace std;
const int MAX_N = 3002;
const long long MOD = 1e9+7;

int numRowX[MAX_N];
int numColX[MAX_N];

int numWellRow[MAX_N];
int numWellCol[MAX_N];

int main() {
    int T; scanf("%d",&T);

    for (int t=0;t<T;t++) {
        memset(numRowX,0,sizeof numRowX);
        memset(numColX,0,sizeof numColX);
        memset(numWellRow,0,sizeof numWellRow);
        memset(numWellCol,0,sizeof numWellCol);

        int N; scanf("%d",&N);
         
        for (int n=0;n<N;++n) {
            int r,c;
            scanf("%d %d",&r,&c);
            numRowX[r]++;
            numColX[c]++;
        }

        int Q; scanf("%d",&Q);
        for (int q=0;q<Q;++q) {
            int r, c;
            scanf("%d %d",&r,&c);
            numWellRow[r]++;
            numWellCol[c]++;
        }

        long long ans = 0;
        
        for (int r1=0;r1<MAX_N;r1++) {
            for (int r2=0;r2<MAX_N;r2++) {
                ans = (ans % MOD) + (static_cast<long long>(pow(static_cast<long long>(r1-r2),static_cast<long long>(2))*static_cast<long long>(numRowX[r2]))% MOD)*static_cast<long long>(numWellRow[r1]);
                ans = (ans % MOD) + (static_cast<long long>(pow(static_cast<long long>(r1-r2),static_cast<long long>(2))*static_cast<long long>(numColX[r2]))% MOD)*static_cast<long long>(numWellCol[r1]);
            }
        }
    

        printf("Case #%d: %lld",t+1,ans);
        cout << endl;
    }

    return 0;
}
