#include <bits/stdc++.h>
using namespace std;

int main() {
  string s; cin >> s;
  vector<vector<int>> numberPresent(10,vector<int>(2,0));
    //[amount of times, digit]
  for (int i=0;i<10;++i) {
    numberPresent[i][1] = i;
  }
  for (char c : s) {
    numberPresent[c-48][0]++;
  }
  sort(numberPresent.begin(),numberPresent.end());

  int n = numberPresent[0][0]+1;
  int d = numberPresent[0][1];

  if (d == 0) {
    if (n == numberPresent[1][0]+1) { // next one same no of times
      for (int i=0;i<n;++i) {
        cout << numberPresent[1][1];
      }
    }
   else {
     cout << 1;
      for (int i=0;i<n;++i) {
        cout << d;
      }     
   }
    // check next one. 
  }
  else {
    for (int i=0;i<n;++i) {
      cout << d;
    }
  }
  cout << endl;  
  
}