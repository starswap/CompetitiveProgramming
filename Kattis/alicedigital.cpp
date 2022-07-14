//Max 1D Range sum with only positive integers, but a certain value m must be the minimum of the range and it can only be in the range once. Kadane's variant.
//There are a number of ways to do this problem, and this is possibly not the best.

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; scanf("%d",&T);
  while (T--) { //for each test case
    int n,m; scanf("%d %d",&n,&m);
    
    vector<int> nums(n);
    for (int i=0;i<n;++i) {
      cin >> nums[i];
    }

    int bestContinue = 0; //highest weight of a range ending with the current number, with no values < m, may or may not contain m.
    int bestContinueNoM = 0; //highest weight of a range ending with the current number not including m, with no values < m.
    int bestOverall = 0; //Max weight of a range of the required form, over all i so far. 
    
    bool seen = false; //does the value for bestContinue include an m or not?
    
    for (int i=0;i<n;++i) {
      
      if (nums[i] < m) { //current number cannot be included.
        bestContinue = 0; //impossible to continue from this number; must reset.
        bestContinueNoM = 0; //ditto
        seen = false; //bestContinue does not contain an m
      }
      else if (nums[i] == m) { //we found an m
        bestContinue = bestContinueNoM + m; //the best we can get to continue from here is everything from just after the previous m, to and including this one.
        bestContinueNoM = 0; //can't continue from here with no m.
        seen = true; //bestContinue now includes an m, so future values should be taken into account there directly, not through BCNM as we won't be adding BCNM again. Without the seen flag, we would score subarrays that don't contain any m value as bestContinue would be nonzero prior to an m being found. This leads to a WA when we have for example 74 84 and the target is 74.
      }
      else { // nums[i] > m
        if (seen) //we have found an m and so adding nums[i] to the current sequence results in a possible answer which could be considered to be the best overall.
          bestContinue += nums[i];
        // else: we have not found an m yet and so bestContinue is not valid. When, on line 40, we compare it to bestOverall this would be wrong.
        
        //we always update this total which represents the total since the last m was discovered. 
        bestContinueNoM += nums[i];
      }
      bestOverall = max(bestOverall,bestContinue); //best overall score is the best over all i of the best sequence ending at index i.
    }
    
    printf("%d\n",bestOverall);  //output answer
  }
}