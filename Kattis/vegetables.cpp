#include <bits/stdc++.h>
using namespace std;

typedef map<double,int> sd;
const int EPS = 1e-4;
int main() {
  double T;
  int N;
  scanf("%lf %d",&T,&N);
  sd pq;
  for (int n=0;n<N;++n) {
    double a; cin >> a;
    pq.emplace(a,1);
  }

  int c = 0;
  while (T <= static_cast<double>(((pq.begin())->first)/(prev(pq.end())->first)) <= T+EPS) {//check epssssss method
    
    double largest = (prev(pq.end()))->first; 
    double smallest = (pq.begin())->first; 

    double largestAmt = (prev(pq.end()))->second;
    
    double ratioGivenHalf = min(smallest,largest/2)/( (pq.size()<2) ? (largest/2) : max(largest/2,prev(pq.end(),2)->first)); //new ratio



    
    if ((T <= ratioGivenHalf && ratioGivenHalf <= T+EPS) || largest/2 > smallest) {
      pq.erase(prev(pq.end()));
      auto loc = pq.find(largest/2);
      if (loc == pq.end())
        pq.emplace(largest/2,largestAmt*2);
      else {
        int amtToAdd = largestAmt*2+loc->second;
        pq.erase(largest/2);
        pq.emplace(largest/2,amtToAdd);   
      }
      c += largestAmt;
    } else {
      pq.erase(prev(pq.end()));
      auto loc = pq.find(largest-smallest);
      
      if (loc == pq.end())
        pq.emplace(largest-smallest,largestAmt);
      else  {
        int amtToAdd = largestAmt+loc->second;
        pq.erase(largest-smallest);
        pq.emplace(largest-smallest,amtToAdd);
      }
      
      loc = pq.find(smallest);
      if (loc == pq.end())
        pq.emplace(smallest,largestAmt);
      else {
        int amtToAdd = largestAmt+loc->second;
        pq.erase(smallest);
        pq.emplace(smallest,amtToAdd);  
      }
      c += largestAmt;      
    }
  }

  cout << c << endl;
  
}