//Principle: avoid using return values as that would necessitate std::pair which I find clunky.

#include <bits/stdc++.h>
using namespace std;

int minExceeding[101][10001]; //dp[idx][amtSpent]
int coinsUsed[101][10001]; //dp[idx][amtSpent]
int N,P;
vector<int> coins;

const int LARGE_VALUE = 1000000000;

//Access functions enable us to give a default base case value to non-storable states. 
int minExceedingF(int idx,int amtSpent) {
  if (amtSpent >= P)
    return amtSpent;
  else
    return minExceeding[idx][amtSpent];
}

int coinsUsedF(int idx,int amtSpent) {
  if (amtSpent >= P)
    return 0;
  else
    return coinsUsed[idx][amtSpent];
}

void dp(int idx,int amtSpent) {
  if (minExceedingF(idx,amtSpent) != -1) return; //already computed
  if (amtSpent >= P) return; //a base case; nothing to compute here (normally would return a base case value but this is held in the helper function)
  
  if (idx == N-1) { //last one, so no recursion to perform (a base case)
    if (amtSpent+coins[idx] >= P) { //reaches and it can't already be above P (base case above) so this is min.
      minExceeding[idx][amtSpent] = (amtSpent+coins[idx]); 
      coinsUsed[idx][amtSpent] = 1; //one coin below this one was needed (0+1).
    }
    else { //doesn't reach
      minExceeding[idx][amtSpent] = LARGE_VALUE;  //doesn't reach; the LARGE_VALUE will be beaten by a realistic value.
      coinsUsed[idx][amtSpent] = 1; //irrelevant
    }
  } 
  else { // (idx < N-1) Not on the last index
    //Recurse to prepare any values we will need
    
    dp(idx+1,amtSpent); //Leave this coin/bill out 
    dp(idx+1,amtSpent+coins[idx]); //Use this coin/bill to pay

    // The following will cover all cases
    if (minExceedingF(idx+1,amtSpent) < minExceedingF(idx+1,amtSpent+coins[idx])) { //cheaper to skip this bill
      minExceeding[idx][amtSpent] = minExceedingF(idx+1,amtSpent);
      coinsUsed[idx][amtSpent] = coinsUsedF(idx+1,amtSpent);
    } 
    else if (minExceedingF(idx+1,amtSpent) > minExceedingF(idx+1,amtSpent+coins[idx])) { //cheaper to use this bill
      minExceeding[idx][amtSpent] = minExceedingF(idx+1,amtSpent+coins[idx]);
      coinsUsed[idx][amtSpent] = 1+coinsUsedF(idx+1,amtSpent+coins[idx]);
    }
    else if (minExceedingF(idx+1,amtSpent) == minExceedingF(idx+1,amtSpent+coins[idx])) {  //no cost difference; choose fewest coins/bills
      minExceeding[idx][amtSpent] = minExceedingF(idx+1,amtSpent+coins[idx]);
      coinsUsed[idx][amtSpent] = min(1+coinsUsedF(idx+1,amtSpent+coins[idx]),coinsUsedF(idx+1,amtSpent));
    }
  }
}

int main() {
  int T; scanf("%d",&T);
  while (T--) {
    scanf("%d",&P);
    scanf("%d",&N);
    coins.assign(N,0);
    for (int n=0;n<N;++n)
      scanf("%d",&coins[n]);
    
    memset(minExceeding,-1,sizeof minExceeding);
    memset(coinsUsed,-1,sizeof coinsUsed);

    dp(0,0);
    printf("%d %d\n",minExceeding[0][0],coinsUsed[0][0]);
       
  }
}
