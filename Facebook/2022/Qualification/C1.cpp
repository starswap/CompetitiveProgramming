#include <bits/stdc++.h>
using namespace std;

vector<char> notMorse(string a) {
  vector<char> res(a.size(),'.');
  for (int i=0;i<a.size();++i)
    res[i] = (a[i] == '.') ? '-' : '.';
  return res;
}

vector<char> fromBinary(int a) {
  int mask = 1;
  int count = 0;
  vector<char> res(100,'.');
  while (mask <= a) {
    if (a & mask) {
      res[count] = '-';
    }
    mask = mask << 1;
    count += 1;
  }
  return res;
}

ostream& operator << (ostream& o, vector<char> v) {
  for (char c : v)
    o << c;
  return o;
}

int main() {
  int T;
  scanf("%d",&T);
  for (int t=0;t<T;++t) {
    int N;
    scanf("%d",&N);
    string code1;
    cin >> code1;

    printf("Case #%d:\n",t+1);    
    for (int n=1;n<N;++n) {
      cout << notMorse(code1) << fromBinary(n) << endl; 
    }
    
  }
  return 0;
}