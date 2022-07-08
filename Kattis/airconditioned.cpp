#include <bits/stdc++.h>
using namespace std;

int main() {
  int N; cin >> N;

  vector<pair<int,int>> tempBounds;
  for (int i=0;i<N;++i) {
    int U,L; scanf("%d %d",&L,&U);
    tempBounds.emplace_back(L,U);
  }
  sort(tempBounds.begin(),tempBounds.end());

  int currentLower = -1;
  int currentUpper = -1;
  int i = 0;
  int amt = 0;
  while (i < N) {
    auto &[start,end] = tempBounds[i];
    if (currentLower <= start && start <= currentUpper) {
      currentLower = start;
      currentUpper = min(currentUpper,end);
      ++i;
    } // no need to create a new room.
    else { // need to create a new room.
      amt++;
      currentLower = start;
      currentUpper = end;
      ++i;
    }
    
  }
  cout << amt << endl;
  
}