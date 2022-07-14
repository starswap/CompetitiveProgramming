// As preferred by CPBook's Methods To Solve, calculate the total of the subsets that don't attain 200g or more and then subtract it from the overall total. This is more efficient than the other solution presented in fruitbaskets.py as the "total of all subsets" calculation is only performed once, not every time we exceed 200.
//Test with:
//40
//1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000 1000
//This implementation is 0.07 seconds faster than the Python implementation (100% faster using times rounded to 3sf).

#include <bits/stdc++.h>
using namespace std;

long long N;
vector<int> fruitWeights;

long long smallBasketTotal(int current,long long total) {
  if (current >= N) {
    return total;
  }
  else {
    long long allTotal = 0;
    if (total + fruitWeights[current] < 200)
      allTotal += smallBasketTotal(current+1,total + fruitWeights[current]); //take this piece

    allTotal += smallBasketTotal(current+1,total); //don't take this piece
    return allTotal;
  }
}


int main() {
  cin >> N;
  fruitWeights.assign(N,0);
  long long total = 0;
  for (int n=0;n<N;++n) {
    cin >> fruitWeights[n];
    total += fruitWeights[n];
  }

  //NOTE: Need to ensure all inputs to the expression are long longs to avoid an overflow on the output, including by static_casting the 1.
  long long totalOfAll = (static_cast<long long>(1)<<(N-1))*total;
  
  cout << totalOfAll - smallBasketTotal(0,0) << endl;
  
}