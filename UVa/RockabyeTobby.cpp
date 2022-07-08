#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  cin >> T;
  for (int t=0; t<T;t++) {
    int n,k;
    cin >> n;
    cin >> k;
    priority_queue<tuple<int,int,int,string>> pq;
    for (int i=0;i<n;i++) {
      //get name and how often.
      string name;
      int howOften;
      cin >> name;
      cin >> howOften;
      pq.push(tuple<int,int,int,string>(-howOften,-i,howOften,name));
    }
    for (int i=0;i<k;i++) {
      auto [thisTime,priority,howOften,name] = pq.top() ; pq.pop();
      cout << -thisTime << " " << name << endl;
      pq.push(tuple<int,int,int,string>(thisTime-howOften,priority,howOften,name));
    }
  }
}
