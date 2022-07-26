//NOTE: Tea charge T is PER PERSON (multiply by number of people)

#include <bits/stdc++.h>
using namespace std;

int dp[3][23][101][1001]; //dp[howManyAlready][totalDishesBought][indx][moneySpent]
//Reasonable chance that the majority of these states are not required, seeing as the max totalDishesBought is 23.
//An improvement would be to include each dish twice in the list of dishes and then you can eliminate the howManyAlready state variable which could save some time though this is already AC.

vector<int> W; //knapsack weights (i.e. cost of items in DimSum)
vector<int> V; //knapsack values i.e. happiness ratings
int N,x,K,T;
int totalMoney; //amount you can spend
double EPS = 1e-9;

int safeCeil(double l) {
  if (fabs(l-ceil(l)) < EPS) //Floating point error (0.99999999999997)
    return ceil(l);
  if (fabs(l-floor(l)) < EPS) //Floating point error (1.000000000000007)
    return floor(l);

  return ceil(l); //no significant FPE; just ceil. 
}

int getCost(int moneySpent) {
  return safeCeil(1.1*static_cast<double>(T*(N+1)+moneySpent));
}


int knapsack(int howManyAlready,int totalBought,int i,int moneySpent) {
  //Find maximum total happiness value under the given constraints with the given dimsum. 
  //Max sum <==> Max average
  
  if (getCost(moneySpent) == totalMoney || totalBought == 2*(N+1)) return 0; //can't spend more or can't buy more, prune
  if (i >= K) return 0; //Exceeded maximum index
  int &ans = dp[howManyAlready][totalBought][i][moneySpent]; //will mutate
  if (ans != -1) return ans; //Already computed; DO

  if (getCost(moneySpent+W[i]) > totalMoney || howManyAlready == 2)
    ans = knapsack(0,totalBought,i+1,moneySpent); // can only leave it
  else  //take it or leave it
    ans = max(V[i]+knapsack(howManyAlready+1,totalBought+1,i,moneySpent+W[i]),knapsack(0,totalBought,i+1,moneySpent));
  return ans;
}


int main() {
  while (scanf("%d %d %d %d",&N,&x,&T,&K), !(N == 0 && x == 0 && K == 0 && T == 0)) { //for each test case
    totalMoney = x*(N+1); //Everyone spends up to £x.

    W.assign(K,0); //clear
    V.assign(K,0); //clear
    for (int k=0;k<K;++k) { //get weights and values
      scanf("%d",&W[k]); //get weight (dim sum cost)

      //Get values
      int fav; 
      for (int i=0;i<=N;++i){ //for each person including you
        scanf("%d",&fav); //get their favour value
        V[k] += fav; //add it onto the total value for this dim sum
      }
    }
    
    memset(dp,-1,sizeof dp); //Clear DP array
    printf("%.2lf\n",static_cast<double>(knapsack(0,0,0,0))/static_cast<double>(N+1)); //Compute best total and find average, rounding to 2dp.
  }
}