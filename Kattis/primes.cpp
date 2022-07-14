#include <bits/stdc++.h>
using namespace std;

int mini;
int maxi;
vector<int> nums;
vector<int> primes;

ostream & operator << (ostream&o, vector<int> v) {
  for (int i=0;i<v.size()-1;++i) {
    o << v[i] << ",";
  }
  o << v[v.size()-1];
  return o;
}

int opCount = 0;

void genValues(long long n,int i) {
  opCount++;
  if (n <= maxi && n > 0) {
    if (mini <= n)
      nums.push_back(n);
    
    for (int j=i;j<primes.size();++j) { //you can remove this loop and just say either take this one and then continue with the next prime up, or skip this one and continue with the next prime up. 
      genValues(n*primes[j],j);
    }
  }
}

int main() {
  int N;
  while (scanf("%d",&N),N != 0) {
    nums.clear();
    primes.assign(N,0);
    for (int i=0;i<N;++i) {
      cin >> primes[i];
    }
    scanf("%d %d",&mini,&maxi);
    genValues(1,0);
    sort(nums.begin(),nums.end());
    if (nums.size() == 0)
      cout << "none";
    else
      cout << nums;
    cout << endl;
//    cout << opCount << endl;
  }

}
