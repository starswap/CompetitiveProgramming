//Optimised to 0.74 secs

//offers a 0.04 sec optimisation
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<vector<bool>> vvb;
typedef vector<int> vi;

int C,n;
int V[2000];
int W[2000];
int dp[2001][2001]; //dp(i,remW) //C array gains 0.24
int path[2001];
int k;

inline int knapsack(int i, int remW) {
  int &ans = dp[i][remW];
  if (i == n || remW == 0) return 0; //can't do anything further
  if (ans != -1) return ans;
  if (W[i] > remW) ans = knapsack(i+1,remW);        // have to leave
  else ans = max(V[i]+knapsack(i+1,remW-W[i]),knapsack(i+1,remW)); //can leave or take
  return ans;
}

int with,without;
inline void trace_path(int i, int remW) {
  if (i == n || remW == 0) return; //can't do anything further
  if (W[i] > remW) trace_path(i+1,remW);   // have to leave
  else { //can leave or take
    with = V[i]+knapsack(i+1,remW-W[i]);
    without = knapsack(i+1,remW);
    if (with > without) {
      path[k] = i; k++;
      trace_path(i+1,remW-W[i]);
    }
    else trace_path(i+1,remW);
  }
}


int main() {
  //gains 0.08
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  while (scanf("%d %d",&C,&n) != EOF) {
    
      memset(dp,-1,sizeof(dp));
      memset(V,0,sizeof(V));
      memset(W,-1,sizeof(W));

      memset(path,-1,sizeof(path));
      k = 0;
    
    for (int i=0;i<n;++i) {
      scanf("%d",&V[i]);
      scanf("%d",&W[i]);
    }

    knapsack(0,C);
    trace_path(0,C);
    printf("%d\n",k);
    for (int i=0;i<k;++i) {
      printf("%d",path[i]);
      if (i == k-1)
        printf("\n");
      else
        printf(" ");
    }
  }
  return 0;
}
