//Pre-optimisation - should work but is a portion of a second too slow to pass. The main optimisation required to get it to pass must happen in the knapsack subroutine. The easiest improvement is to not fill up a take array but rather to generate the set afterwards from a different trace_path routine which can be seen in knapsack.cpp. This on its own is enough to pass the time limit but a few other optimisations such as replacing vectors with ints can get the time taken down even more. 
#include <bits/stdc++.h>
using namespace std;
typedef vector<vector<int>> vvi;
typedef vector<vector<bool>> vvb;
typedef vector<int> vi;

int C,n;
vector<int> V;
vector<int> W;

int knapsack(int i, int remW, vvi &dp, vvb &take) {
  if (i == n || remW == 0) {return 0;} //can't do anything further
  if (dp[i][remW] != -1) return dp[i][remW];
  if (W[i] > remW) { // have to leave
    dp[i][remW] = knapsack(i+1,remW,dp,take);
    take[i][remW] = false;
  }
  else { //can leave or take
    int with = V[i]+knapsack(i+1,remW-W[i],dp,take);
    int without = knapsack(i+1,remW,dp,take);
    if (with > without) { //what if they are both the same?
      take[i][remW] = true;
      dp[i][remW] = with;
    }
    else {
      take[i][remW] = false;
      dp[i][remW] = without;
    }
  }
  return dp[i][remW];
}

void trace_path(vvb &take,int i,int remW,vi &path) {
  if (i == n || remW == 0) return;
  if (take[i][remW]) {
    path.push_back(i);
    trace_path(take,i+1,remW-W[i],path);
  }
  else {
    trace_path(take,i+1,remW,path);  
  }
}

int main() {
  while (scanf("%d %d",&C,&n) != EOF) {
    
    vector<vector<int>> dp(n,vector<int>(C+1,-1)); //dp(i,remW)
    vector<vector<bool>> take(n,vector<bool>(C+1,0)); //dp(i,remW)

    V.assign(n,0);
    W.assign(n,0);
    for (int i=0;i<n;++i) {
      cin >> V[i];
      cin >> W[i];
    }

    

    knapsack(0,C,dp,take);
    vector<int> path;
    trace_path(take,0,C,path);
    cout << path.size() << endl;
    for (int i=0;i<path.size();++i) {
      cout << path[i];
      if (i == path.size()-1)
        cout << endl;
      else
        cout << " ";
    }
  }
  return 0;
}
