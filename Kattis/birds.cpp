#include <bits/stdc++.h>
using namespace std;

int main() {
  int l,d,n,total; scanf("%d %d %d",&l,&d,&n);
  vector<int> birds(n);
  for (int i=0;i<n;++i) {
    cin >> birds[i];
  }

  if (n == 0) {
    total = floor((l-12)/d)+1;
  }
  else {
    sort(birds.begin(),birds.end());
    
    total = max(0.0,floor(static_cast<double>(birds[0]-6)/static_cast<double>(d)));
    for (int i=1;i<n;++i) {
      total += max(floor(static_cast<double>(birds[i]-birds[i-1])/static_cast<double>(d))-1,0.0);
    }
  
    total += max(0.0,static_cast<double>((l-6)-(birds[n-1]))/static_cast<double>(d));
    }
  cout << total << endl;
  
  return 0;
}