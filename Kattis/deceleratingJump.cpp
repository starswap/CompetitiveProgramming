#include <bits/stdc++.h>
using namespace std;
const long long INF = 100000000000;

long long dp[3001][3001][2]; //dp[jumpLength][posn][add]

int main() {
    int num;
    scanf("%d",&num);
    vector<int> squares(num);
    
    for (int i=0;i<=3000;i++) {
        for (int j=0;j<=3000;j++) {
            dp[i][j][0] = -INF;
            dp[i][j][1] = -INF;        
        }
    }

    for (int n=0;n<num;n++) {
        scanf("%d",&squares[n]);
    }

    for (int jumpLength=1;jumpLength<num;++jumpLength) {
        dp[jumpLength][num-1][0] = 0;
        dp[jumpLength][num-1][1] = squares[num-1];
    }

    for (int posn=num-2;posn>-1;posn--) {
        for (int jumpLength=1;jumpLength<num;++jumpLength) {
            dp[jumpLength][posn][0] = max(
                 ((jumpLength > 0) ? dp[jumpLength-1][posn][0] : -INF),
                 ((posn+jumpLength < num) ? dp[jumpLength][posn+jumpLength][1] : -INF)
            );
            
            dp[jumpLength][posn][1] = squares[posn] + max(
                ((jumpLength > 0) ? dp[jumpLength-1][posn][0] : -INF),
                ((posn+jumpLength < num) ? dp[jumpLength][posn+jumpLength][1] : -INF)
            );   
        }
    }

    printf("%lld\n",dp[num-1][0][1]);
    return 0;
}
