//This version is optimised to be faster on the theoretical maximum input size, but is actually slower on the judge because it is slower on smaller input sizes, so slower on average.(for 20 test cases at maximum I get around 10.5 secs with this method vs 15 secs with the dynamic vectors version). Use dynamic vectors to get an overall speed improvement on average.

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
int costs[50][50];
int maxCoin;
int coins[50];
int dp[51][100001];

pair<int,int> dfs(int u, int t,int costSoFar,int p,int numEdges) {
  if (u == t) return make_pair(costSoFar,numEdges);
  for (int v : AL[u]) {
    if (p != v) {
      pair<int,int> res = dfs(v,t,costSoFar + costs[u][v],u,numEdges+1);
      if (res.first != -1) {
        if (p != -1) {
          coins[maxCoin] = (2*costs[p][u]);
          maxCoin++;
        }
        return res;
      }
    }
  }
  return make_pair(-1,-1);
}

//-2 = unset
//-1 = impossible
// other numbers = the number of coins.
int coinChange(int i, int remC) {
  if (remC == 0) return 0;
  if (remC < 0) return -1;
  if (i >= maxCoin) return -1;
  if (dp[i][remC] != -2) return dp[i][remC];
  int without = coinChange(i+1,remC);
  int with = coinChange(i,remC-coins[i]);
  if (with == -1)
    dp[i][remC] = without;
  else if (without == -1)
    dp[i][remC] = 1+with;
  else
    dp[i][remC] = min(without,1+with);
  return dp[i][remC]; 
}


int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N; scanf("%d",&N);  
  while (N--) {
    int n,m;
    scanf("%d %d",&n,&m);
    AL.assign(n,vector<int>(0));
    for (int i=0;i<m;++i) {
      int u,v,c; scanf("%d %d %d",&u,&v,&c);
      u--; v--; 
      costs[u][v] = c;
      costs[v][u] = c;
      AL[u].push_back(v);
      AL[v].push_back(u);
    }

    int k; scanf("%d",&k);
    for (int i=0;i<k;++i) {
      int u,v,c;
      scanf("%d %d %d",&u,&v,&c);
      u--;
      v--;
      maxCoin = 0;
      auto [cost,numEdges] = dfs(u,v,0,-1,0);
      int target = c - cost;
      
      for (int i=0;i<51;++i) {
        for (int j=0;j<100001;++j) {
          dp[i][j] = -2;
        } 
      }
      
      int res = coinChange(0,target);
      if (res == -1)
        printf("No\n");
      else
        printf("Yes %d\n",(2*res+numEdges));
    }
    if (N != 0) printf("\n");
  }
}