//A freebie given you have read the algorithm in the book.

#include <bits/stdc++.h>
using namespace std;

vector<int> p;
int endPoint;
vector<int> nums;


void printLis(int endPointL) {
  if (endPointL == -1) return;
  printLis(p[endPointL]);
  cout << nums[endPointL];
  if (endPoint == endPointL)
    cout << endl;
  else
    cout << " ";
}


int main() {
  int n;
  while (scanf("%d",&n), n != 0) {
    nums.assign(n,0);
    
    for (int i=0;i<n;++i) {
      cin >> nums[i];
    }

    int k = 0;
    p.assign(n,0);
    vector<int> endValLengthL(n,0);
    vector<int> endILengthL(n,0);

    for (int i=0;i<n;++i) {
      int ind = lower_bound(endValLengthL.begin(),endValLengthL.begin()+k,nums[i]) - endValLengthL.begin(); //first index in array where the value is greater than this one, or we need to place a new one.
      endValLengthL[ind] = nums[i];
      endILengthL[ind] = i;
      if (ind == k) {
        k++; //new longest so we had to extend the array.
        endPoint = i;
      }
      if (ind == k-1) 
        endPoint = i;
      p[i] = (ind == 0) ? -1 : endILengthL[ind-1];      
    }

    cout << k << " ";
    printLis(endPoint);
    
  }
  return 0;
}