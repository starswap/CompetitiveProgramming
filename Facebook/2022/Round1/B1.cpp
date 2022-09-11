//Must compile with -Ofast

#include <bits/stdc++.h>

using namespace std;
const int MAX_N = 3002;
const long long MOD = 1e9+7;

int numRowX[MAX_N];
int numColX[MAX_N];

int main() {
    int T; scanf("%d",&T);

    for (int t=0;t<T;t++) {
        memset(numRowX,0,sizeof numRowX);
        memset(numColX,0,sizeof numColX);

        int N; scanf("%d",&N);
         
        for (int n=0;n<N;++n) {
            int r,c;
            scanf("%d %d",&r,&c);
            numRowX[r]++;
            numColX[c]++;
        }

        int Q; scanf("%d",&Q);
        long long ans = 0;
        for (int q=0;q<Q;++q) {
            long long total = 0;
            int r1, c1;
            scanf("%d %d",&r1,&c1);
            for (int r2=0;r2<MAX_N;r2++) {
                total += static_cast<long long>(pow(static_cast<long long>(r1-r2),static_cast<long long>(2))*static_cast<long long>(numRowX[r2]));
                total += static_cast<long long>(pow(static_cast<long long>(c1-r2),static_cast<long long>(2))*static_cast<long long>(numColX[r2]));
            }
            // cout << (total) << endl; 
            ans += total;
            ans %= MOD;
        }

        printf("Case #%d: %lld",t+1,ans);
        cout << endl;
    }

    return 0;
}
