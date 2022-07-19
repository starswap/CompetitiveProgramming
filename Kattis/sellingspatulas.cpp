#include <bits/stdc++.h>
using namespace std;

int MAX_T = 1439;

int main() {
  int n;
  while (scanf("%d",&n),n!=0) {
    vector<int> c(MAX_T+1,-8);
    for (int i=0;i<n;++i) {
      int t; float p;
      scanf("%d %f",&t,&p);
      c[t] = round(p*100)-8;
      //cout << c[t] << endl;
    }
    int bestLength,bestStart = 0,bestProfit = 0;

    //Kadane's
    int continueScore = 0; int continueStart = 0;
    for (int i=0;i<MAX_T+1;i++) {
      if (continueScore == 0)
        continueStart = i;
      continueScore += c[i];
      if (continueScore > bestProfit) {
        bestProfit = continueScore;
        bestStart = continueStart;
        bestLength = i-continueStart+1;
      } else if (continueScore == bestProfit && bestProfit != 0) {
        if (bestLength > i-continueStart+1) {
          bestProfit = continueScore;
          bestStart = continueStart;
          bestLength = i-continueStart+1;
        } else if (bestLength == i-continueStart+1) {
          if (continueStart < bestStart) {
            bestProfit = continueScore;
            bestStart = continueStart;
            bestLength = i-continueStart+1;
          }
        }
      }
      if (continueScore < 0) {
        continueScore = 0;
      }
    }
 //   cout << bestProfit << endl;
    if (bestProfit == 0)
      cout << "no profit" << endl;
    else 
      printf("%.2f %d %d\n",static_cast<float>(bestProfit)/100.0,bestStart,bestStart+bestLength-1);
  
  } 
  
}