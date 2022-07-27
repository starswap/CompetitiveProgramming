//Note: LONG LONG!
//Note 2: As we are only interested in the largest values in the BST at any point to remove them, we could in fact just use a PQ. 

//Method:
  //Linear iteration over the weeks from left to right
    //Add each week's estimate to a (b)BST
    //For all recycling estimates in the BST that are greater than the current estimate (i.e. for all recycling estimates whose runs are ended by this current one), remove them from the BST, and set rightWard[index] = deltaIndex where index is the week number of the removed week, and deltaIndex is the difference between the removed week's index and the current week's index.
    //The result is that rightWard[idx] gives the size of the largest run starting at idx, with values >= nums[idx].
  //Repeat, iterating backwards over the array to produce leftWard[idx], the size of the largest run /ending/ at idx, with values >= nums[idx]. (for all idx)
  //The answer will be max over all idx of (leftWard[idx]+rightWard[idx]-1) as we double count the item itself. Remember to deal with tiebreaks. 
//Complexity (O(nlogn))

//Alternative method / Extra notes after looking at the suggested solutions:
  //Better O(n) solution:
    //Iterate over the expected amounts of rubbish from left to right:
      //Maintain a stack which will contain the values (height, startIndex) for each expectation we encounter
      //Remove items from the stack while the current expectation is less than the top item on the stack, so the stack must always contain values in decreasing order of height and decreasing order of being added to the stack (naturally)
      //Once the top item is less than the new height, we have removed all runs which have been terminated by the current height (and as they are removed they can be assessed relative to the previous best)
      //Add the new height to the stack. If we just removed an item from the stack, we can treat this new item as extending the most recently removed item's run, and so the newly added start is the previously removed start. Otherwise the start is just the current index. 
    //Don't forget to then successively pop all items off the stack at the end to check if any runs ending with the end of the calendar will be optimal (this can also be done with a sentinel value).
  //Note: We are effectively looking for the largest area rectangle that can be placed under the function recycling(week);
//How do we come up with this better solution when looking at the problem?
  //Think about what happens when you encounter a new value - two cases:
    //Larger than the current run and so we can extend the current run or start again from here.
    //Smaller than the current run and so the current run ends here, but we can continue it at a lower height value, the value of the new height.
    //Current runs can be increased by default by storing their start point and then computing the length once they have to stop.
    //A run is defined by its height, start value (and end point which can be inferred from when it must stop)
  //Brand new runs are always created with a larger height and start value than previously. 
  //When runs are continued at a lower height they are still the maximum continuable height
  //Therefore the order of heights and when added seems to match up
  //But we have several runs to manage at any point, so we need a data structure.
  //The order of when added is reflective of the order in a stack/queue
  //So we could feasibly realise we need to use a stack to store the continuable runs. 
  //Then, having seen something similar before, you can probably jump to the solution, using the relations above for what to do when a new expectation is encountered.
//Maybe this thought process would get us there? I don't know.

#include <bits/stdc++.h>

using namespace std;


int main() {
  int N; scanf("%d",&N);
  vector<long long> nums(N+1,-1); // -1s are sentinels
  vector<long long> nums2(N+1,-1);

  
  for (int n=0;n<N;++n) {
    long long a; scanf("%lld",&a);
    nums[n] = a;
    nums2[n+1] = a;
  }

  set<pair<long long,int>> BST; // (value,index) 
  vector<int> rightWard(N,0);
  
  for (int i=0;i<=N;++i) { //iterate left to right
    auto [it,succ] = BST.emplace(nums[i],i);
    it = next(it);
    while (it != BST.end()) { 
      auto [value,index] = *it;
      rightWard[index] = i-index;
      it = next(it);
      BST.erase(prev(it));
    }
  }

  vector<int> leftWard(N,0);
  auto comp = [] (pair<long long,int> lhs,pair<long long,int> rhs) {
    if (lhs.first == rhs.first)
      return lhs.second > rhs.second;
    else
      return lhs < rhs;
  };

  set<pair<long long,int>,decltype(comp)> BST2(comp); //value, index;
  
  for (int i=N;i>=0;--i) { //iterat\e right to left
    auto [it,succ] = BST2.emplace(nums2[i],i);
    it = next(it);
    while (it != BST2.end()) { 
      auto [value,index] = *it;
      leftWard[index-1] = index-i;
      it = next(it);
      BST2.erase(prev(it));
    }
  }

  long long best = 0;
  int bestStart = 10000000;
  int bestEnd = 100000000;
  for (int i=0;i<N;++i) {
    long long score = nums[i]*(leftWard[i]+rightWard[i]-1);
    int start = i+1-leftWard[i]+1;
    int end = i-1+rightWard[i]+1;
    if (score > best) {
      best = score;
      bestStart = start;
      bestEnd = end;
    }
    else if (score == best) {
      if (start < bestStart) { //break ties.
        best = score;
        bestStart = start;
        bestEnd = end;
      }
    }
  }

  printf("%d %d %lld\n",bestStart,bestEnd,best);
  return 0;
}
