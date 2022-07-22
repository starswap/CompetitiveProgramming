#include <bits/stdc++.h>
using namespace std;

vector<int> W;
vector<int> V;
vector<vector<int>> dp;

int knapsack(int i, int remW) {
  if (remW <= 0) return 0;
  if (i == W.size()) return 1000000000;
  if (dp[i][remW] != -1) return dp[i][remW];
  dp[i][remW] = min(V[i]+knapsack(i+1,remW-W[i]),knapsack(i+1,remW));
  return dp[i][remW];
}


int main() {
  int S; 

  while (scanf("%d",&S) != EOF) {
    int alreadyWon = 0;
    int totalDelegates = 0;
    int pointsAvailable = 0;
    V.clear();
    W.clear();
    for (int s=0;s<S;++s) {
      int d,c,f,u; scanf("%d %d %d %d",&d,&c,&f,&u);
      int mustConvince = (c+f+u)/2+1 - c;
      totalDelegates += d;
      if (mustConvince <= 0)
        alreadyWon += d;
      else if (mustConvince <= u && f < round(static_cast<double>(c+f+u)/2.0)) { // skip if feds already won.
        W.push_back(d);
        V.push_back(mustConvince);
        pointsAvailable += d;
      }
    }
  
    int pointsNeeded = totalDelegates/2+1 - alreadyWon;
    
    
    if (pointsNeeded <= 0)
      cout << 0 << endl;
    else if (pointsNeeded <= pointsAvailable) {
      dp.assign(W.size()+1,vector<int>(pointsNeeded+1,-1));      
      cout << knapsack(0,pointsNeeded) << endl;
    }
    else
      cout << "impossible" << endl;
  }
}