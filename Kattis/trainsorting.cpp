#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> weights;
vector<int> memo;
const int INF = 10001;

int dp(int i) {
  if (i == 0) return 1;
  if (memo[i] != -1) return memo[i];

  int maxi = 1;
  for (int j=0;j<i;++j) {
    if (weights[j] < weights[i]) 
      maxi = max(maxi,1+dp(j));
  }
  memo[i] = maxi;
  return memo[i];
}


int main() {
  scanf("%d",&n);
  weights.assign(2*n+1,0);
  for (int i=0;i<n;++i) {
    int w;
    cin >> w;
    weights[n+i] = w;
    weights[n-1-i] = w;
  }
  weights[2*n] = INF;
  memo.assign(2*n+1,-1);

  cout << dp(2*n)-1 << endl;
  
  return 0;
}