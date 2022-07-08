#include <bits/stdc++.h>
using namespace std;

int main() { 
  int c = 1;
  int p,e,i,d;
  cin >> p; cin >> e; cin >> i; cin >> d;
  while (!(p==-1 && e == -1 && i == -1 && d == -1)) {
    p %= 23;
    e %= 28;
    i %= 33;

    
    int q = 28*33*p*6 + 23*33*e*19 + 23*28*i*2;
    q %= (23*28*33);

    int ans;
    if (q > d)
      ans = q-d;
    else
      ans = q+(23*28*33)-d;

    printf("Case %d: the next triple peak occurs in %d days.\n",c,ans);
    cin >> p; cin >> e; cin >> i; cin >> d; ++c;
  }
}
