#include <bits/stdc++.h>
using namespace std;

int main() {
  string before; string after;
  cin >> before; cin >> after;
  int bO = 0,bI = before.size()-1,aO = 0,aI = after.size()-1;

  while (aO < after.size() && bO < before.size() && before[bO] == after[aO]) {
    bO++; aO++;
  }
  while (aI >= aO && bI >= bO && before[bI] == after[aI]) {
    bI--; aI--;
  }

//  printf("%d %d %d %d\n",aO,aI,bO,bI);

  if (aI < aO)
    cout << 0 << endl;
  else 
    cout << aI - aO + 1 << endl;
  
}