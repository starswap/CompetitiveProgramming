#include <bits/stdc++.h>
using namespace std;

const int INF = 100000000;

inline int LSOne(int v) {
  return (v&-v);
}

vector<vector<int>> costs(20,vector<int>(20,INF));

int dp1[262144][20]; //dp1[bitmask][u]
int dp2[262144][20]; //dp2[bitmask][u], up to 18 and 2^18.

int tsp(int remainingBM, int u, int target, int dp[262144][20]) {
  if (remainingBM == 0)
    dp[remainingBM][u] = costs[u][target];
  if (dp[remainingBM][u] != -1)
    return dp[remainingBM][u];
  int prevRemaining = remainingBM;
  int best = INF;
  while (remainingBM > 0) {
    int twoPowV = LSOne(remainingBM);
    int v = __builtin_ctz(twoPowV)+1;
    best = min(best, costs[u][v] + tsp(prevRemaining ^ twoPowV,v,target,dp));
    remainingBM ^= twoPowV;
  }
  dp[prevRemaining][u] = best;
  return best;
}

int n, m;
int nHotels;

inline int safeNot(int v) {
  return ~v & ((1<<nHotels)-1);
}

int recursiveSolve(int BM, int numSet,int current) {
  //BM is your first 9.
  
  if (numSet >= nHotels/2 && numSet != 0) { //Done so try this set
    int best = INF;
    for (int u=1;u<=nHotels;++u) {
      for (int v=1;v<=nHotels;++v) {
        if ((BM & (1<<(u-1))) && (BM & (1<<(v-1)))) {
          
          int newScore = tsp(BM^(1<<(u-1)),u,0,dp2) + tsp(safeNot(BM),u,n-1,dp1) + tsp(BM^(1<<(v-1)),v,n-1,dp1) + tsp(safeNot(BM),v,0,dp2);
 //            + //S->E; 1st 9
     //        + //S->E; 2nd 9
   //          + //E->S; 1st 9
             //E->S; 2nd 9
          best = min(best,newScore);
        }
      }
    }
    return best;
  }
  else if (current > nHotels)
    return INF;
  else {
    return min(
      recursiveSolve(BM | (1<<(current-1)),numSet+1,current+1),
      recursiveSolve(BM,numSet,current+1)
    );
  }
  
}




int main() {
  int caseNo = 1;
  while (scanf("%d %d",&n,&m) != EOF) {
    costs.assign(n,vector<int>(n,INF));
    for (int i=0;i<m;++i) {
      int u,v,c;
      scanf("%d %d %d",&u,&v,&c);
      costs[u][v] = c;
      costs[v][u] = c;
    }

    for (int k=0;k<n;++k)
      for (int i=0;i<n;++i)
        for (int j=0;j<n;++j)
          costs[i][j] = min(costs[i][j],costs[i][k]+costs[k][j]);
    
    nHotels = n-2;
    memset(dp1,-1,sizeof dp1);
    memset(dp2,-1,sizeof dp2);
    
    tsp((1<<nHotels)-1,0,n-1,dp1);
    tsp((1<<nHotels)-1,n-1,0,dp2);
    
    int ans = recursiveSolve(0,0,1);
    
    printf("Case %d: %d\n",caseNo,ans);
    ++caseNo;
  }
  return 0;
}