//Knapsack variant:
  //Not 0-1 (actually 0+) however we don't have to max the value
  //So really it's more subset sum.
  //DP solution fine as there is no value optimisation component to it.

#include <bits/stdc++.h>
using namespace std;
vector<int> W;
int dp[101][30001];
int n; 

int knapsack(int i,int remW) { //returns number of ways or 2 if it is bigger than 1 way.
  if (remW == 0) {
    return 1;
  }
  else if (remW < 0 || i >= n) return 0;
  if (dp[i][remW] != -1) return dp[i][remW];

  int summ = 0;
  //(we don't care about the actual number of ways - only if it is bigger than 1. So if it is bigger than 1 just call it 2. That way no integer overflow.)
  summ += min(2,knapsack(i,remW-W[i])); //take this one
  summ += min(2,knapsack(i+1,remW)); //skip this one

  dp[i][remW] = summ;
  return summ;
}


vector<int> path;
void printDP(int i,int remW) { //mutates global path
  if (remW <= 0 || i >= n) {
    return;
  }
  if (knapsack(i,remW-W[i])){
      path.push_back(i+1);
      printDP(i,remW-W[i]);
  }
  else {
    printDP(i+1,remW); //skip this one
  }
}

int main() {
  scanf("%d",&n);
  W.assign(n,0);
  for (int i=0;i<n;++i) {
    cin >> W[i];
  }
  int m; scanf("%d",&m);
  memset(dp,-1,sizeof dp);
  
  for (int j=0;j<m;++j) { //up to 1000
    int amt; cin >> amt;
    int ways = knapsack(0,amt); //DP : total states is 30000*100=3M; shared across all iters of this loop.
    //first two are O(1)
    if (ways == 0) 
      cout << "Impossible" << endl;
    else if (ways > 1)
      cout << "Ambiguous" << endl;
    else {
      path.clear();//O(path size) - up to 30000
      printDP(0,amt); //O(path size) - up to 30000
  //    sort(path.begin(),path.end()); // don't need this as in order already due to generation in increasing order of index i.
      for (int i=0;i<path.size()-1;i++) { // again O(path size)
        cout << path[i] << " ";
      }
      cout << path[path.size()-1] << endl;
    }
  }

  //overall 30000*1000 = 30M which should pass
  return 0;
  
}