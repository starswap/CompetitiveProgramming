#include <bits/stdc++.h>
using namespace std;
const long long M = 1e9+7;


int main() {
  int N;
  cin >> N;
  vector<long long> avail(N);
  vector<long long> partial(N); //using previous coins, how many of this coin can I add up to?

  vector<long long> modPowers(N);
  int i = 1;
  for (int j=0;j<N;++j) {
    modPowers[j] = i;
    i = (i*2)%M;
  }
  
  //can remove some loops
  for (int n=0;n<N;++n) {
    cin >> avail[n];
    if (n == 0)
      partial[n] = 0;
    else
      partial[n] = (partial[n-1]+avail[n-1])/2;
  }

  int total = 0;

  long long needToAccountFor = 0;
  for (int n=N-1;n>=0;--n) {
    long long oldAvail = avail[n];
    avail[n] = max(avail[n]-needToAccountFor,static_cast<long long>(0));
    needToAccountFor -= (oldAvail - avail[n]);
    needToAccountFor *= 2; //twice as many of the next coin down.

    if (avail[n] % 2 == 1) {
      if (partial[n] < 1) {
        total = (total % M) + modPowers[n];
      } else {
        needToAccountFor += 2;
      }
    } // else {no need to chuck anything away}
  }
  cout << total << endl;

  // for (int n=0;n<N-1;++n) {
  //   avail[n+1] += avail[n]/2;
  //   avail[n] %= 2;
  // }
  // long long total = 0;
  // for (int n=0;n<N;++n) {
  //  if (avail[n] % 2 == 1) {
  //    total = (total % M) + (powM(2,n,M)*(avail[n]%M));
  //  }
  // }

  // cout << total << endl;
  return 0;
  
}