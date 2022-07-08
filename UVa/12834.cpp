#include <bits/stdc++.h>
using namespace std;
int main() {
  int T; cin >> T;
  int caseNo = 1; 
  while (T--) {
    int N,K; scanf("%d %d",&N,&K);
    vector<long long> X(N);
    vector<long long> Y(N);
    for (int n=0;n<N;++n) {
      cin >> X[n];
    }
    for (int n=0;n<N;++n) {
      cin >> Y[n];
    }
    
    vector<long long> profit(N);
    for (int n=0;n<N;++n) {
      profit[n] = Y[n]-X[n];
    }

    sort(profit.begin(),profit.end());

    long long total = 0;
    for (int i=0;i<N;++i) {
      if (profit[i] < 0 && K > 0)
        K--;
      else
        total += profit[i];
    }

    printf("Case %d: ",caseNo);
    if (total > 0) {
      cout << total;
    } else {
      cout << "No Profit";
    }
    cout << endl;
    caseNo++;
  }
}