/*
Not yet..
#include <bits/stdc++.h>
using namespace std;

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
}*/