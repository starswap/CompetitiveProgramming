// Using the method recommended in "Solution"
// Needs std=c++20


// Try optimising even just the basic one, then the better ones one at a time.
// Check video points to learn

#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

// Order Statistics Tree
// We use this to get O(logn) getKth() and remove() operations in solveFor200000
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    OST;

inline int LSOne(int a) { // Least Significant one bit
  if (a == 0)
    return 0;
  return (a & -a);
}

int N, K;
vector<int> stringLengths;
// We will build up these global variables, one for each thread; use hash tables
// for O(1) in-checking
unordered_set<int> thread1;
unordered_set<int> thread2;

bool solveFor25(const vector<int> &indices) {
  // Brute force solution for n up to 25
  //  indices = vector of indices into the stringLengths array, where each index
  //  points to a particular string
  // O(2^n) - We have to try all 2^n subsets of strings in the current set.
  //       - Each subset can be dealt with in O(1) as we keep a running total of
  //       the sum in that subset, and change exactly one item in the subset (in
  //       or out) at a time to enable this total to be updated in O(1).
  // Returns: true if two subsets with the same sum could be found; false otherwise.

  int total = 0; // Current running total of theva
  int bitString = 0; // Bit string representing current set; we can use this as 25 < 32.

  unordered_map<int, int> sumToBitString; // All of the sums we have seen so
                                          // far, mapped to their bitstrings.

  bool found = false; // Did we find two subsets that have the same sum?
  for (int i = 1; i < (1 << indices.size()); ++i) {
    // generate all subsets using the optimisation which means we
    // track the sum as we go along.
    // By always xoring the bitmask with the LSB in the current i value, we
    // generate all possible subsets once and once only, changing exactly one
    // item at a time so the sum can be tracked.

    if (bitString & LSOne(i)) { // The item is currently in the set,...
      total -= stringLengths[indices[__builtin_ctz(LSOne(i))] - 1]; // so remove it
      bitString ^= LSOne(i);                                   // Toggle bit
    }
    else {                                                   // not in, so add
      total += stringLengths[indices[__builtin_ctz(LSOne(i))] - 1];
      bitString ^= LSOne(i); // Toggle bit
    }

    if (sumToBitString.find(total) != sumToBitString.end()) { //Have we already seen this sum?
      found = true;
      break; // found two the same
    }
    else {
      sumToBitString[total] = bitString; //Save this sum for later
    }
  }

  if (found) { //Loop exited prematurely and found a match
    int BS1 = bitString - (bitString & sumToBitString[total]); //Remove any items are in both
    int BS2 = sumToBitString[total] - (bitString & sumToBitString[total]); //Remove any items are in both
    
    while (BS1 > 0) { //For each set bit in BS1
      int twoPowV = LSOne(BS1); //Get the lowest currently set bit
      int v = __builtin_ctz(twoPowV);
      thread1.insert(indices[v]); //add the corresponding item to thread1
      BS1 ^= twoPowV; //unset bit in bitset to advance the loop
    }
    while (BS2 > 0) {
      int twoPowV = LSOne(BS2);
      int v = __builtin_ctz(twoPowV);
      thread2.insert(indices[v]);
      BS2 ^= twoPowV;
    }
    return true;
  } else
    return false;
}

void solveFor100(const vector<int> &indicesOuter) {
  //Solve the problem for n up to 100 by repeatedly taking 25 elements and applying the solution for 25 to them.
  //  indicesOuter = a vector of indices into the global stringLengths array, representing the subset of up to 100 of those strings that we are currently considering. To find the lengths of each string we use stringLengths[indicesOuter[i]-1] since the values start from 1 not 0.
  // Returns void since we know that for 25 < N <= 100, when this procedure will be used, it must be possible to achieve the goal.

  // O(2^25*75/C)
  
  vector<int> indicesCurrentSetOf25; //The current subset of 25 elements (from our subset of 100) that we are building up to apply to solvefor25
  auto it = indicesOuter.begin(); //We will iterate over the setof 100 indicesOuter linearly once to build up our successive subsets, reconsidering strings discarded in solveFor25 but not reconsidering those we used up there. 

  while (it != indicesOuter.end()) { //Single linear iteration over indicesOuter
    while (indicesCurrentSetOf25.size() < 25 && it != indicesOuter.end()) { // Loop until we have built up a subset of 25 which we
                                                                           // know will contain two threads, or until there are no more strings to add.
      indicesCurrentSetOf25.push_back(*it); //Add the next string from the indicesOuter to the current subset.
      it++;
    }
    
    solveFor25(indicesCurrentSetOf25); // find two threads

    //Prepare for next itertation by keeping hold of any str5ings that solvefor25 threw away, and discarding any that have been added to the threads.
    vector<int> indicesTriedThisTime = indicesCurrentSetOf25; //copy the indices we sent over to solveFor25.
    indicesCurrentSetOf25.clear(); // We will re-add all the strings that didn't get used by solveFor25, so that they can be reused.
                                  // We remove and re-add rather than delete so the whole operation is o(n) not o(n^2) as delete from an array is itself O(n)

    for (int str : indicesTriedThisTime) { // remove all strings that got added to the threads
      if (!thread1.contains(str) && !thread2.contains(str)) //didn't get used; this is why we need a hash table for thread1 and thread2
        indicesCurrentSetOf25.push_back(str); // so we need it again
    } 
  }
  //Now we have reached the end. As we reuse strings that get thrown away, only the last solveFor25 can throw away strings.
  //There are thus at most 25 strings to be thrown away (which is always fine) as the last call to solveFor25 has 25 strings to begin with. 
}

void solveFor1000(const vector<int> &indicesOuter) {
  //Solve the problem for N up to 1000 by repeatedly generating random subsets of the current set of 1000 strings, and storing their lengths.
  //Birthday paradox - two will be found with the same length quickly. 
    //indices = vector of indices into global stringLengths array. 
  // Returns void since we know that for 100 < N <= 1000, when this procedure will be used, it must be possible to achieve the goal.
  
  //O(n*sqrt(2*10^8))
  
  vector<int> indices = indicesOuter; //Make a copy so we can mutate it. 
  
  while (indices.size() > 100) { //Until we can use the solution for 100.
    int total = -1; //Total length in the current subset
    unordered_set<int> subset; //Can't use a bitmask since it's up to 1000 items.
    
    //Lookup table for previous subsets to check if we've found this before or not.
    unordered_map<int, unordered_set<int>> prevSums; // uses a lot of memory unfortunately.
    
    while (!prevSums.contains(total)) { //While we haven't found two with the same total length.
      prevSums[total] = subset; //Store the current length for later lookup

      //Reset
      total = 0;
      subset.clear();

      for (int index : indices) { //Iterate over all possible items we could add to the current subset
        if (rand() % 2 == 1) { //With 50% chance add it, with 50% chance leave it out.
          subset.insert(index);
          total += stringLengths[index - 1]; //Update total as we build the thread
        }
      }
      
    }
    
    //Two subthreads with the same total length have been found
      //"subset", "subset2", both have length "total"
    //Now, we add subset to thread1 and subset2 to thread2, so thread1 and thread2 still have the same length.
    //We ignore any strings in both subthreads because a single string can only be in one thread.
    const unordered_set<int> &subset2 = prevSums[total]; //alias.

    //Use the same trick as before where we copy and re-add any strings that we didn't use up.
    vector<int> indicesPrevious = indices;
    indices.clear();

    for (int item : indicesPrevious) { //O(N) - For every string we haven't used yet. Some strings may be in neither, one, the other one or both sub threads.
      if (subset.contains(item) && !subset2.contains(item)) { //Used only in sub-thread1 so that's ok.
        thread1.insert(item);
      } else if (subset2.contains(item) && !subset.contains(item)) { //Used only in sub-thread2 so that's ok.
        thread2.insert(item);
      } else { // Used in both threads or neither; needs to be reconsidered.
        indices.push_back(item);
      }
    }
  }
  
  solveFor100(indices); //Problem size has been reduced!
}

void solveFor200000(const vector<int> &indices) {
  //Solves the problem for N up to the maximum bound of 200000
    // indices - vector of indices into stringLengths, as usual.
    // O(nlog^2 n) -> double loop with spacing is nlogn; harmonic - cost of logn for each removal from the OST.

  // First remove any strings with the same length.
  unordered_map<int, int> seen;
  for (int index : indices) { // for all of the strings
    if (!seen.contains(stringLengths[index - 1])) { //not yet seen any string with this length
      seen.emplace(stringLengths[index - 1], index); //record which string had this length
    } else { // seen already a string with this length
      thread1.insert(index); //add this one to thread1
      thread2.insert(seen[stringLengths[index - 1]]); //... and the previous one to thread2
      seen.erase(stringLengths[index - 1]); // It's as if we hadn't seen any of this length before now as we need 2 more for duplicate as we have to remove in pairs.
    }
  }

  //Now we remove all pairs of items where there are two pairs with the same total.
  //To ensure not O(n^2), we first consider all items at spacing of 1, then 2, then 3 and so on, but for that we need at least O(log n) index access and O(log n) removal.
  //So use order Statistics Tree.
  OST indicesNotYetRemoved;

  for (auto [value, unmatched] : seen) { //For all of the strings still left in after removing duplicated
    indicesNotYetRemoved.insert(unmatched); //add to the OST
  }

  //Again tracks the pair-sums we have seen before so we can remove any duplicates
  unordered_map<int, pair<int, int>> sumSeen;

  //spacing-based method; avoids O(n^2).
  for (int spacing = 1; spacing < N; spacing++) {
    for (int a = 0; a + spacing < indicesNotYetRemoved.size(); a++) {
      
      int pairSum = stringLengths[*indicesNotYetRemoved.find_by_order(a) - 1] +          // Index a
                    stringLengths[*indicesNotYetRemoved.find_by_order(a + spacing) - 1]; // plus index (a+spacing)
      
      if (!sumSeen.contains(pairSum)) { //We haven't yet found a pair with this sum
        // so track for later comparison
        sumSeen.emplace(
            pairSum, //we will want to lookup this pair by sum.
            make_pair( *indicesNotYetRemoved.find_by_order(a),
                       *indicesNotYetRemoved.find_by_order(a + spacing))
        );
      }
      else { //We have already found a pair with this sum.
        
        auto [c, d] = sumSeen[pairSum]; //c and d are the indices into stringLengths for this pair.
        
        if (indicesNotYetRemoved.find(c) == indicesNotYetRemoved.end() ||
            indicesNotYetRemoved.find(d) == indicesNotYetRemoved.end()) { // At least one of c or d has been deleted in the OST since we first found this pair.
          //So update the sumSeen hash table so that the current pair which we just found matches with (c,d) is the new current pair for the current sum so later pairs can match with it.
          sumSeen[pairSum] = make_pair(
                                        *indicesNotYetRemoved.find_by_order(a),
                                        *indicesNotYetRemoved.find_by_order(a + spacing));

        }
        else { //both pairs (a,b) and (c,d) still exist and have the same sum so we need to remove their elements.

          int a1 = *indicesNotYetRemoved.find_by_order(a);//the index into stringLengths for the first item in the first pair, a1 to avoid name conflict with a.
          int b = *indicesNotYetRemoved.find_by_order(a + spacing); //the index into stringLengths for the second item in the first pair

          //Remove these items
          indicesNotYetRemoved.erase(a1);
          indicesNotYetRemoved.erase(b);
          indicesNotYetRemoved.erase(c);
          indicesNotYetRemoved.erase(d);

          //Add pair 1 to thread1, pair2 to thread2, so the threads still have the same length.
          thread1.insert(a1);
          thread1.insert(b);
          thread2.insert(c);
          thread2.insert(d);

          // Correct for removal to avoid skipping values. 
          // a is an index into the OST, but if we remove items the indices shift.

          // removed a so current index now points to next value. When we do a++ at the end of the next loop we will be skipping one, so correct for this.
          a--; 
          if (c < a1) // c comes before a in the OST which is sorted by value increasing.
            a--;      // indices are shifted by one as we removed c.
          if (d < a1) // d comes before a in the OST which is sorted by value increasing.
            a--;      // indices are shifted by one as we removed d.

          sumSeen.erase(pairSum); // Already found two pairs; will need two more to remove again, not just one more for three total, so it's as if we never had found any.
        }
      }
    }
  }
  
  vector<int> fewerThan1000 = vector<int>(indicesNotYetRemoved.begin(), indicesNotYetRemoved.end()); //Final set of fewer than 1000 strings converted from OST to array,
  solveFor1000(fewerThan1000); //... and passed into the next solution down
}


void printUnorderedSet(const unordered_set<int> &us) {
  //Prints one unordered set, with spaces in between and a newline at the end; used to print threads.

  auto it = us.begin();
  for (int iterNo = 0; iterNo < us.size() - 1; ++it, ++iterNo) { //output all but the last element; terminating condition based on number of iterations as you can't reverse iterate on an unordered-set
    printf("%d ", *it);
  }
  printf("%d\n", *it); //output last element with a newline.

}

int main() {
  srand(1); // Ensure same random numbers every time for debugging; it doesn't actually matter if you leave this in.

  //IO Speed; this problem is IO heavy. 
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int T; // Num of TCs
  scanf("%d", &T);
  
  for (int t = 1; t <= T; ++t) { 
    scanf("%d %d", &N, &K);

    // Get all string lengths
    stringLengths.assign(N, 0);
    for (int n = 0; n < N; ++n) {
      scanf("%d", &stringLengths[n]);
    }

    // reset threads and boolean var which tells us whether it is possible or not.
    thread1.clear();
    thread2.clear();
    bool possible = false;

    // initially we want to consider every string in the collection, so indices needs to contain all integers \in [1,N]. 
    vector<int> indices;
    for (int i = 1; i <= N; ++i)
      indices.push_back(i);

    //Call correct solution based on size of input; larger ones cascade down to smaller ones when called though.
    if (N <= 25) {
      possible = solveFor25(indices); //Will find out if possible upon brute forcing
    } else if (N <= 100) {
      possible = true; //when n > 25 it's always possible
      solveFor100(indices);
    } else if (N <= 1000) {
      possible = true;
      solveFor1000(indices);
    } else {
      possible = true;
      solveFor200000(indices);
    }

    if (possible) { //Can do so we need to output possible and the two threads
      printf("Case #%d: Possible\n", t);
      printUnorderedSet(thread1);
      printUnorderedSet(thread2);
    } else { //can't/don't need to output the threads
      printf("Case #%d: Impossible\n", t);
    }
  } //Repeat for future TCs.
  
  return 0;
}
