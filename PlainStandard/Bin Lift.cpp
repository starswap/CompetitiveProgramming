#include <bits/stdc++.h>
using namespace std;

int logn;

vector<vector<int>> dp; //dp[u][n]
vector<vector<int>> AL;
vector<vector<int>> cost;
vector<int> dist;
vector<int> costToRoot;

void prepBinLiftLCA(int u,int d,int totalC) {
  dist[u] = d;
  costToRoot[u] = totalC;
  
  for (int i=1;i<logn;i++) {
    if (dp[u][i-1] != -1)
      dp[u][i] = dp[dp[u][i-1]][i-1];
  }
  for (int v : AL[u]) {
    if (dp[u][0] != v) { //as long as u's parent is not v.
      dp[v][0] = u;
      prepBinLiftLCA(v,d+1,totalC+cost[u][v]);
    }
  }
}

int LCA(int u, int v) {
  if (dist[v] > dist[u]) swap(u,v);

  //Now u is always deeper than or equal to v.
  int deltaD = dist[u]-dist[v]; //amount we need to move u up by in order to match level with v.
  
  for (int i=logn;i>=0;i--) {
    if (deltaD & (1<<i))
      u = dp[u][i];
  }

  //now both are same level

  for (int i=logn;i>=0;i--) {
    if (dp[u][i] != dp[v][i]) {
      u = dp[u][i];
      v = dp[v][i];
    }
  }
  return dp[u][0];
  
}


int main() {
  int N; scanf("%d",&N);
  while (N--) {
    int n,m; scanf("%d %d",&n,&m);
    AL.assign(n,vector<int>(0));
    cost.assign(n,vector<int>(n,-1));
    for (int i=0;i<m;++i) {
      int u,v,c; scanf("%d %d %d",&u,&v,&c);
      u--; v--; 
      cost[u][v] = c;
      cost[v][u] = c;
      AL[u].push_back(v);
      AL[v].push_back(u);
    }

    logn = ceil(log(static_cast<double>(n))/(log(static_cast<double>(2))));
    dp.assign(n,vector<int>(logn,-1));
    dist.assign(n,0);
    costToRoot.assign(n,0);

    prepBinLiftLCA(0,0,0);

    int k; scanf("%d",&k);
    
    for (int i=0;i<k;++i) {
      int u,v,c;
      scanf("%d %d %d",&u,&v,&c);
      u--;
      v--;
      int l = LCA(u,v);
      int actualCost;
      actualCost = costToRoot[u]+costToRoot[v]-costToRoot[l]*2;
      int distance = dist[u]+dist[v]-dist[l]*2;
      if (actualCost == c)
        printf("Yes %d\n",distance);
      else
        printf("No\n");
    }
  }
}