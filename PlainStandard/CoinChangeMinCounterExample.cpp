//Original Paper: https://ecommons.cornell.edu/bitstream/handle/1813/6219/94-1433.pdf?sequence=1&isAllowed=y
//Algorithm Explanation: https://math.stackexchange.com/questions/4139845/change-making-problem-pearson-algorithm-to-check-the-optimality-of-greedy-solu

//Of course you could just test all values from 1 onwards to find the lowest counterexample but this would be much slower with larger size coins - this method is always O(n^3) where n is the number of coins in the set.

#include <bits/stdc++.h>
using namespace std;

template <typename T> 
ostream& operator << (ostream&o, vector<T> v) {
  o << '[';
  for (T u : v)
    o << u << ",";
  o << ']';
  return o;
}

vector<int> coins;
int N;

void greedyRepRecursive(int X, vector<int> &rep) {
  if (X == 0)  return;
  
  int i = 0;
  while (1) {
    if (coins[i] <= X) {
      rep[i] += 1;
      greedyRepRecursive(X-coins[i],rep);
      break;
    }
    ++i;
  }
}

vector<int> greedyRep(int X) {
  vector<int> output(N,0);
  greedyRepRecursive(X,output);
  return output;
}

int main() {
  cout << "How many coins? ";
  cin >> N;
  cout << "Enter space separated coins: "; 
  //Always include one 1-value coin so all representable.
  
  coins.resize(N);
  for (int n=0;n<N;n++)
    cin >> coins[n];
  
  sort(coins.rbegin(),coins.rend());
  cout << "coins " << coins << endl;

  vector<int> counters;
  for (int i=1;i<N;++i) {
    vector<int> G_iminus1 = greedyRep(coins[i-1]-1);
    int j;
    for (j=i;j<N;++j) {
      cout << "i = " << i << endl;
      cout << "j = " << j << endl;
      cout << "G(C_i-1 - 1) " << G_iminus1 << endl;
      
      vector<int> M(N,0);
      int k;
      for (int k=0;k<j;++k) {
        M[k] = G_iminus1[k];
      }
      M[j] = G_iminus1[j]+1;
      
      int w = 0;
      int minCoinUsage = 0;
      
      
      for (int l=0;l<N;++l) {
        w += coins[l]*M[l];
        minCoinUsage += M[l];
      }
    
      vector<int> G = greedyRep(w);
      int greedyCoinUsage = 0;
      for (int k=0;k<N;++k) {
        greedyCoinUsage += G[k];
      }
      cout << "w = " << w << endl;
      cout << "M = " << M << endl;
      cout << "G = " << G << endl;
      cout << "GreedyCoinUsage = " << greedyCoinUsage << endl;
      cout << "MinCoinUSage = " << minCoinUsage << endl << endl;
    
      if (greedyCoinUsage > minCoinUsage)
        counters.push_back(w);
    
    }            
  }
  if (counters.size() == 0)
    cout << "Greedy is Optimal." << endl;
  else
    cout << "Greedy is not optimal: the smallest counter example is: " << *min_element(counters.begin(),counters.end()) << endl;
}