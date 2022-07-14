//Kadane's Algorithm : Max 1D range sum. 

#include <bits/stdc++.h>
using namespace std;
int main() {
  int N,P; scanf("%d %d",&N,&P); //input number of array items; cost per item.
  
  int currentSum = 0; //score we can get by continuing the current range
  int maxi = 0; //best score overall

  for (int n=0;n<N;++n) {
    int gain; //Revenue
    cin >> gain;
    gain -= P; //minus costs gives profit
    
    currentSum += gain; //continue the current range
    maxi = max(currentSum,maxi); //if this is better then update the running maximum
    currentSum = max(currentSum,0); //if it goes below zero we should start again the next time and not carry on
  }

  cout << maxi << endl;
}