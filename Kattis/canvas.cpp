#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  while (T--) {
    int N; cin >> N;
    priority_queue<long long,vector<long long>,greater<long long>> sizes;

    long long total = 0;
    for (int n=0;n<N;++n) {
      long long s;
      cin >> s;
      sizes.push(s);
    }
    while (sizes.size() != 1) {
      long long a = sizes.top(); sizes.pop();
      long long b = sizes.top(); sizes.pop();
      total += a+b;
      sizes.push(a+b);
    } 
    cout << total << endl;
  }
  return 0;
}
