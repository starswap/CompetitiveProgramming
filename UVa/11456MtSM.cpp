//USing the method in "Methods to Solve"

#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> weights;
vector<int> memoLIS;
vector<int> memoLDS;

const int INF = 10001;

int LIS(int i) {
  if (i == 0) return 1;
  if (memoLIS[i] != -1) return memoLIS[i];

  int maxi = 1;
  for (int j=0;j<i;++j) {
    if (weights[j] < weights[i]) 
      maxi = max(maxi,1+LIS(j));
  }
  memoLIS[i] = maxi;
  return memoLIS[i];
}

int LDS(int i) {
  if (i == 0) return 1;
  if (memoLDS[i] != -1) return memoLDS[i];

  int maxi = 1;
  for (int j=0;j<i;++j) {
    if (weights[j] > weights[i]) 
      maxi = max(maxi,1+LDS(j));
  }
  memoLDS[i] = maxi;
  return memoLDS[i];
}


int main() {
  int T; cin >> T;
  while (T--) {
    scanf("%d",&n);
    weights.assign(n,0);
    for (int i=0;i<n;++i) {
      int w;
      cin >> w;
      weights[n-1-i] = w; //note: we need to reverse the input because it is the maximum of LDS starting at i + LIS starting at i, whereas in the book the algorithm is for ending at i. Since we need both LDS and LIS this is ok to do (technically it swaps them round though).
    }
    
    memoLIS.assign(n,-1);
    memoLDS.assign(n,-1);


    
    
    
    int best = 0;
    for (int i=0;i<n;++i) {
      best = max(best,LIS(i)+LDS(i)-1);
    }
    cout << best << endl;
  }
  
  return 0;
}