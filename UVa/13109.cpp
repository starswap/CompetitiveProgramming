#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    int M,W; scanf("%d %d",&M,&W);
    vector<int> elephants(M);
    for (int n=0;n<M;n++) {
      cin >> elephants[n];
    }
    sort(elephants.begin(),elephants.end());

    int total = 0;
    int amt = 0;
    for (int n=0;n<M;++n) {
      if (total + elephants[n] <= W) {
        total += elephants[n];
        amt++;
      }
    }
    cout << amt << endl;
  }
  
  
}