#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int N; cin >> N;
    vector<int> coins(N);
    for (int n=0;n<N;++n) {
      cin >> coins[n];
    }

    int total = 0;
    int amt = 0;
    for (int n=0;n<N-1;++n) {
      if (total + coins[n] < coins[n+1]) {
        total += coins[n];
        amt += 1;
      }
    }
    amt += 1;

    cout << amt << endl;
    
  }
  
}