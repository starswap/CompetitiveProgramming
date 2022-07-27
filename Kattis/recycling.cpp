//Note: LONG LONG!

//Method:
  //Linear iteration over the weeks from left to right
    //Add each week's estimate to a (b)BST
    //For all recycling estimates in the BST that are greater than the current estimate (i.e. for all recycling estimates whose runs are ended by this current one), remove them from the BST, and set rightWard[index] = deltaIndex where index is the week number of the removed week, and deltaIndex is the difference between the removed week's index and the current week's index.
    //The result is that rightWard[idx] gives the size of the largest run starting at idx, with values >= nums[idx].
  //Repeat, iterating backwards over the array to produce leftWard[idx], the size of the largest run /ending/ at idx, with values >= nums[idx]. (for all idx)
  //The answer will be max over all idx of (leftWard[idx]+rightWard[idx]-1) as we double count the item itself. Remember to deal with tiebreaks. 


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
