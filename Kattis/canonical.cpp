#include <bits/stdc++.h>
using namespace std;
vector<int> coins;
int dpDP[2000001];
int dpGreedy[2000001];

int dp(int amt) {
  if (amt == 0) return 0;
  if (amt < 0) return 10000000;
  if (dpDP[amt] != -1) return dpDP[amt];
  int mini = 10000000;
  for (int coin : coins) {
    mini = min(mini,1+dp(amt-coin)); //use this coin
  }
  dpDP[amt] = mini;
  return dpDP[amt];
}

int greedy(int amt) {
  if (amt == 0) return 0;
  if (dpGreedy[amt] != -1) return dpGreedy[amt];
  for (auto it = coins.rbegin();it != coins.rend();it++) {
    if (*it <= amt) {
      dpGreedy[amt] = 1+greedy(amt-*it);
      break;
    }
  }
  return dpGreedy[amt];
}


int main() {
  int N; scanf("%d",&N);
  coins.assign(N,0);
  for (int n=0;n<N;++n) {
    scanf("%d",&coins[n]);
  }
  sort(coins.begin(),coins.end());

  int highest = *coins.rbegin() + *next(coins.rbegin());
  memset(dpDP,-1,sizeof dpDP);
  memset(dpGreedy,-1,sizeof dpGreedy);

  int canonical = true;
  for (int c=1;c<highest;c++) {
    int greedyNum = greedy(c);
    int dpNum = dp(c);
    if (greedyNum != dpNum){
      canonical = false;
      break;
    }
  }
  printf("%s\n",(canonical) ? "canonical" : "non-canonical");
  
}