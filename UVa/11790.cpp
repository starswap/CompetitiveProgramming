#include <bits/stdc++.h>
using namespace std;

int longSeq(vector<int> &widths, vector<int> &heights, int i,std::function<bool(int,int)> 
 comp,vector<int> &memo) {
  if (memo[i] != -1)
    return memo[i];
  
  if (i == 0)
     memo[i] = widths[i];
  
  else {
    int best = widths[i];
    for (int j=0;j<i;++j) {
      if (comp(heights[j],heights[i])) { //j before i in subsequence
        best = max(best,widths[i]+longSeq(widths,heights,j,comp,memo));
      }
    }
    memo[i] = best;
  }
  
  return memo[i];
}


int main() {
  int T; scanf("%d",&T);
  for (int i=1;i<=T;++i) {
    int n; scanf("%d",&n);
    vector<int> heights(n);
    vector<int> widths(n);
    for (int j=0;j<n;++j) {
      cin >> heights[j];
    }
    for (int j=0;j<n;++j) {
      cin >> widths[j];
    }

    vector<int> memo(n+1,-1);
    heights.push_back(1000000000);
    widths.push_back(0);
    int L_inc = longSeq(widths,heights,n,std::less<int>(),memo);
    
    heights[n] = -1;
    for (int &a : memo) //reset memo.
      a = -1;
    int L_dec = longSeq(widths,heights,n,std::greater<int>(),memo);

    
    if (L_inc >= L_dec) {
      printf("Case %d. Increasing (%d). Decreasing (%d).\n",i,L_inc,L_dec);
    }
    else {
      printf("Case %d. Decreasing (%d). Increasing (%d).\n",i,L_dec,L_inc);
    }
    
  }
}