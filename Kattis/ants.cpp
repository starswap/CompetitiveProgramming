#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  while (T--) {
    int l,n;
    scanf("%d %d",&l,&n);
    vector<int> ants(n);
    for (int i=0;i<n;++i) {
      cin >> ants[i];
    }
    sort(ants.begin(),ants.end());

    int mini = 0;
    int maxi = 0;    
    bool passedHalf = false;
    for (int i=0;i<n;++i) {
      if (ants[i] > static_cast<double>(l)/2.0) {
        passedHalf = true;
      }
      if (passedHalf) {
        mini = max(mini,l-ants[i]);
        maxi = max(maxi,ants[i]);        
      }
      else {
        mini = max(mini,ants[i]);
        maxi = max(maxi,l-ants[i]);        
      }
    }

    printf("%d %d\n",mini,maxi);
    
  }
  
}