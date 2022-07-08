#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  int caseNo = 1;
  while (T--) {
    int N,H,T_a,T_d; scanf("%d %d %d %d",&N,&H,&T_a,&T_d);
    int time;
    vector<int> hippoHeights(N);
    for (int i=0;i<N;++i) {
      cin >> hippoHeights[i];
    }
    if (T_d >= 2*T_a) {
      time = N*T_a;
    } else {
      sort(hippoHeights.begin(),hippoHeights.end());
      time = 0;
      int s=0;
      int e=N-1;
      while (s < e) {
        if (hippoHeights[s]+hippoHeights[e] < H) {
          time += T_d;
          s++; e--;
        } else {
          time += T_a;
          e--;
        }
      }
      if (s == e) //last one couldn't be paired and must travel alone
        time += T_a;
      // otherwise we paired the last two and therefore there's none left.
    
    }
    printf("Case %d: %d\n",caseNo,time);
    caseNo++;
  }
  
}