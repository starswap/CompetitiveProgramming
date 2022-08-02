#include <bits/stdc++.h>
using namespace std;

vector<int> costs;
int dp[1001][1001]; //dp[square][prevJump]
int N;

const int INF = 100000000;

int solve(int square, int prevJump) {
  if (square == N) return costs[N];
  if (dp[square][prevJump] != -1) return dp[square][prevJump];
  if (square > prevJump && square+prevJump+1 <=N)
    dp[square][prevJump] = costs[square] + min(solve(square+prevJump+1,prevJump+1),solve(square-prevJump,prevJump));
  else if (square+prevJump+1 <= N)
    dp[square][prevJump] = costs[square] + solve(square+prevJump+1,prevJump+1); //forwards only
  else if (square > prevJump) //backwards only
    dp[square][prevJump] = costs[square] + solve(square-prevJump,prevJump);
  else
    dp[square][prevJump] = INF; //can't get there
  return dp[square][prevJump]; 
}

int main() {
  scanf("%d",&N);
  costs.assign(N+1,0);
  for (int n=1;n<=N;++n)
    scanf("%d",&costs[n]);

  memset(dp,-1,sizeof dp);
  printf("%d\n",solve(2,1));
  
  
  return 0;
}
