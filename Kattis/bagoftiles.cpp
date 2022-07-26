//This is efficient enough even though computing all states for all 200 cases would be TLE at 1.8B. This is because only 1/3 of the states need to go univisted to make this pass - and clearly many are not visited. For instance in dp[i][j][1] only 30 can be visited which saves a lot. 
//Either that or the test cases do not test 200 maximums in one go. 

//Two possible ncr calculation methods are included, which both work.

#include <bits/stdc++.h>
using namespace std;

vector<int> coins;
int dp[31][10001][31]; //dp[idx][remainingAmt][numUsed]
int m, n, t;

//Compute without factorial to avoid overflow; O(r) but this is fine since it only occurs once per game. (200*30 ops)
long long ncr(int n, int r) {
  double total = 1;
  for (int i=r;i>=1;--i) {
    total = total/(i);
    total = total*(n-i+1);
  }
  return round(total);
}

//Alternative:  Compute ncr with dynamic programming since we will need several of them. (0.01 secs slower)
int ncrdp[31][31]; //ncrdp[n][r]
long long ncr2(int n, int r) {
  if (r == 0 || r == n) return 1;
  if (ncrdp[n][r] != -1) return ncrdp[n][r];
  ncrdp[n][r] = ncr2(n-1,r-1)+ncr2(n-1,r);
  return ncrdp[n][r];
}


int dpCalc(int i,int remAmt,int numUsed) {
  if (remAmt == 0 && numUsed == n) return 1;
  if (numUsed == n || i == m || remAmt < 0) return 0;
  int &ans = dp[i][remAmt][numUsed];
  if (ans != -1) return ans;

  ans = dpCalc(i+1,remAmt,numUsed) + dpCalc(i+1,remAmt-coins[i],numUsed+1);

  return ans;
}

int main() {
  int g; scanf("%d",&g);
  
  memset(ncrdp,-1,sizeof ncrdp); //If using the ncrdp method

  //For each test case
  for (int c=1;c<=g;++c) {
    //Get all coin values
    scanf("%d",&m);
    coins.assign(m,0);
    for (int i=0;i<m;++i)
      scanf("%d",&coins[i]);
    
    scanf("%d %d",&n,&t);
    int totalWays = ncr2(m,n); //Select ncr method here
     
    memset(dp,-1,sizeof dp);
    int winningWays = dpCalc(0,t,0);

    printf("Game %d -- %d : %d\n",c,winningWays,totalWays-winningWays);    
      
  }
  return 0;
}