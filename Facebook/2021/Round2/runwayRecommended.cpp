//Using the recommended method in "Solution"

//Facebook's suggested solution:
//Lower constant O(NM) - finishes in 0.7 secs
//Simple to code
//Considers all models the same at each step if they are wearing the same style.
//See runay for my solution.

#include <bits/stdc++.h>
using namespace std;

int style;

int main() {
  int T;
  scanf("%d",&T);
  
  for (int t=1;t<=T;++t) {
    int nRounds, mModels; //as detailled in problem description
    scanf("%d %d",&nRounds,&mModels);

    int ans = 0;
    unordered_map<int,int> W;
    unordered_map<int,int> U;
    
    for (int i=0;i<mModels;++i) {
      scanf("%d",&style);
      if (W.contains(style)) {
        W[style]++; U[style]++;
      }
      else {
        W[style] = 1; U[style] = 1;
      }
    }
    //Read input
    for (int j=0;j<nRounds;++j) {
      unordered_map<int,int> R;

      for (int i=0;i<mModels;++i) {
        scanf("%d",&style);
        if (R.contains(style)) {
          R[style]++;
        }
        else {
          R[style] = 1;
        }
      }

      for (auto [s,w] : W) {
        int r,u,selfChange;
        if (R.find(s) == R.end())
          r = 0;
        else
          r = R.find(s)->second;
        
        int C = w - min(w,r);
        if (U.find(s) == U.end()) {
          u = 0;
          selfChange = 0;
        }
        else {
          u = U.find(s)->second;
          selfChange = min(C,u);
          U[s] -= selfChange; 
        }
        int dorothyChange = C - selfChange;
        ans += dorothyChange;
      }
      W = R;   
    }

    printf("Case #%d: %d\n",t,ans);
  }
}
