#include <bits/stdc++.h>
using namespace std;

const int MAX_K = 2501;

int dp[MAX_K][MAX_K]; // dp[S_pos][keyNo]
int prevr[MAX_K][MAX_K]; //prevr[keyNo][keyValue]
int post[MAX_K][MAX_K]; //post[keyNo][keyValue]

vector<int> K;
vector<int> prevAux;
vector<int> S;
int n;

int doDP(int s_pos, int keyNo) {
    if (s_pos >= n-1) return 0;
    if (dp[s_pos][keyNo] == -1) {
        
        int keyToFind = S[s_pos+1];

        if (prevr[keyNo][keyToFind] == -1) {
            dp[s_pos][keyNo] = keyNo - prevr[keyNo][keyToFind] + doDP(s_pos+1,prevr[keyNo][keyToFind]);//   post only
        } 
        else if (post[s_pos]) {
            dp[s_pos][keyNo] = post[keyNo][keyToFind] - keyNo + doDP(s_pos+1,post[keyNo][keyToFind]); // prev only
        }
        else {
            // prev and post
             dp[s_pos][keyNo] = min(keyNo - prevr[keyNo][keyToFind] + doDP(s_pos+1,prevr[keyNo][keyToFind]),
                                    post[keyNo][keyToFind] - keyNo + doDP(s_pos+1,post[keyNo][keyToFind])); // prev only
        }
    }
    return dp[s_pos][keyNo];
}

int main() {
    int T;
    scanf("%d",&T);
    for (int t=0; t < T;++t) {
        scanf("%d",&n);

        S.assign(n,0);
        for (int i=0;i<n;++i) {
            scanf("%d",&S[i]);
        }               


        int m;
        scanf("%d",&m);
        K.assign(m,0);

        for (int i=0;i<MAX_K;++i) {
            for (int j=0;j<MAX_K;++j) {
                dp[i][j] = -1;
                prevr[i][j] = -1;
                post[i][j] = -1;
            }
        }

        prevAux.assign(MAX_K,-1);
        for (int i=0;i<n;++i) {
            scanf("%d",&K[i]);
            for (int k=0;k<MAX_K;++k) {
                prevr[i][k] = prevAux[K[i]];
            }
            prevAux[K[i]] = i;
        }        

        prevAux.assign(MAX_K,-1);
        for (int i=n;i>=0;--i) {
            for (int k=0;k<MAX_K;++k) {
                post[i][k] = prevAux[K[i]];
            }
            prevAux[K[i]] = i;
        }       


    }
    return 0;
}