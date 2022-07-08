#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  while (T--) {
    int N; cin >> N;
    vector<int> scores(3*N);
    for (int i=0;i<3*N;++i) {
      cin >> scores[i];
    }
    sort(scores.begin(),scores.end());
    int total = 0;

    for (int i=3*N-2;i>=N;i = i-2) {
      total += scores[i];
    }
    cout << total << endl;
    
  }
}