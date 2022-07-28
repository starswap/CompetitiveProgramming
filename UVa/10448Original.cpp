//ORiginal which is faster on the judge but slower (by 5 seconds) on max input. Still AC.

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> AL;
vector<vector<int>> costs;
vector<int> coins;
vector<vector<int>> dp;

pair<int,int> dfs(int u, int t,int costSoFar,int p,int numEdges) {
  int res;
  if (u == t) return make_pair(costSoFar,numEdges);
  for (int v : AL[u]) {
    if (p != v) {
       auto [cost,edges] = dfs(v,t,costSoFar + costs[u][v],u,numEdges+1);
       if (cost != -1) {
         if (p != -1)
           coins.push_back(2*costs[p][u]);
         return make_pair(cost,edges);
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
  if (i >= coins.size()) return -1;
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
  
  int N; scanf("%d",&N);  
  while (N--) {
    int n,m;
    scanf("%d %d",&n,&m);
    AL.assign(n,vector<int>(0));
    costs.assign(n,vector<int>(n,-1));
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
      coins.clear();
      auto [cost,numEdges] = dfs(u,v,0,-1,0);
      int target = c - cost;
      
      dp.assign(n,vector<int>(100000,-2));
      
      int res = coinChange(0,target);
      if (res == -1)
        printf("No\n");
      else
        printf("Yes %d\n",(2*res+numEdges));
    }
    if (N != 0) printf("\n");
  }
}