//Using the expected solution with Dilworth's Theorem:
//The size of the minimal partition into chains is the length of the longest anti chain.
//I.e. the minimum number of stacks of dolls is the length of the longest non-increasing subsequence.

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T,M; scanf("%d",&T);
  while (T--) {
    scanf("%d",&M);
    vector<pair<int,int>> dolls;
    for (int i=0;i<M;++i) {
      int w,h; scanf("%d %d",&w,&h);
      dolls.emplace_back(w,h);
    }

     auto comp = []( pair<int,int> a, pair<int,int> b) {
      if (a.first == b.first)
        return a.second > b.second;
      else
        return a.first < b.first;
    }; //sort by width increasing and then by height decreasing, so that later ones with the same width overwrite. 
    
    sort(dolls.begin(),dolls.end(),comp);

    vector<int> L(M);
    int k = 0;
    for (int i=0;i<M;++i) {
      int ind = lower_bound(L.begin(),L.begin()+k,dolls[i].second,greater_equal<int>()) - L.begin();
      L[ind] = dolls[i].second;
      if (ind == k)
        k++;
    }
    
    
    cout << k << endl;
  }
}
