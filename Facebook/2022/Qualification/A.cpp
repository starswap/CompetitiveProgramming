#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d",&T);
  for (int t=0;t<T;++t) {
    int N,K;
    scanf("%d %d",&N,&K);
    bool possible = true;
    unordered_map<int,int> counts;
    if (N > 2*K) possible = false;
    for (int i=0;i<N;++i) {
      int curr;
      scanf("%d",&curr);
      if (counts.contains(curr)) {
        counts[curr] += 1;  
        if (counts[curr] >= 3) possible = false;          
      }
      else {
        counts[curr] = 1;
      }
    }
    printf("Case #%d: ",t+1);
    cout << ((possible) ? "YES" : "NO") << endl;
  }
}