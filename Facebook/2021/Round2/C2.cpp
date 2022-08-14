//Define "gridlock" as the situation where from a given row to the end there are no blank spaces.
// To solve this problem quickly enough we need to be able to compute all of the costs for all possible different shifts, as in chapter 1, and then make the incremental changes to the grid and know the resulting minimum score in logN or better, without recomputing all possible shifts.
// Again remember that we can do the shifting first and then the one-by-one removals.
// This gives rise to the following method:
//    1. For all possible shifts, get inital cost (total of shift + amount of cars you have to remove at the end)
//    2. Maintain a segment tree of these possible shifts' costs, so we can update each shift's cost when it changes, and then get the minimum cost in logarithmic time.
//    3. For each spell there are 2 sets of shifts whose costs change:
//      a) The shift corresponding to the toggled car itself, which now takes one more or one fewer move to clear the row.
//      b) Any gridlocks which are affected by the presence of this car (which is what makes this problem interesting). Gridlock occurs once there are no free spaces in row K or above, or alternatively in row K or below.
//    4. We can deal with these in the following way:
//      a) Trivial; O(1) update to a single array index; ends up being logn using segment tree because we have to find the right place and update all parents but that's fine.
//      b) We can also say that gridlock occurs when there are K cars above and in row K, or R-K+1 cars below and in row K.
//           Therefore we can determine that gridlock occurs at the shift which causes the Kth or R-K+1th car to move into row K.
//           If we store an ordered set of the cars we can find out in log n which car is the Kth (order statistics tree).
//           Adding or removing a car will cause all shifts between the shifts where gridlock previously occurred and now occurs to either have one more car, or have one fewer car, and this can be dealt with using the segment tree range update operation, also in log n.
//    5. So we iterate over the spells and maintain the segment tree (over all shifts), and C OSTs (one for each column, with all cars in the column), of which we only need to update one OST and the ST each time. We then get the minimum cost over all possible shifts from the segment tree in log n, and add this to the M sum to progressively compute the final answer.
// This has complexity: O(RC + S(log R)) though this has a non-negligible constant. 


//Possible changes:
//    - C shifts - it's min(R,C) effectively - no worries if C is much greater as you only need to shift R+2 times in this method here, so just do best of both worlds. x
//    - Treat all cars initially in the garage as queries - this would worsen the complexity to O( (RC + S) logR) but it still owrks.
//    - Can avoid the off by one errors by removing all cars that are in the right column, then readding with new contributions perhaps.
//    - Skip the OST  - Maintain column by column iterators so no need to find before and after eacht time - no need to use OST either because each change is by one car to an adjacent car only
//    - Recognise the "valid range".
//    - Definitely use more subroutines to reduce confusion levels.


//TtoR
// - SegTree remember to combine + contributions parent to child.
// - Big problems - double counting (or counting when we don't want to - still a car there)
// - Look for double counting from the beginning
// - OST may be able to be replaced by set::iterators.
// - You can store C++ stuff like iterators in C style arrays.

#include <bits/stdc++.h>
#include <bits/extc++.h> //For order statistics tree

using namespace __gnu_pbds; //For order statistics tree
using namespace std;

// Order Statistics Tree from GNU PBDS.
// We use an OST because we want to know how many cars there are above row K, or another way of putting it is "when are there more than K cars above row K", and similarly for below. An ordered set wouldn't give us this information.
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> OST;


template <class T> //Allow any integral type in case we decide we need long long later.
class SegmentTree {
  //Segment tree over an array A, supporting RMinQ over the whole array (O(1)), and range update (O(log n)) which adds a provided delta to all elements in a given range, as these are the operations needed for this problem.
  public:
    SegmentTree(const vector<T> &A) { //construct from an array
      n = A.size(); //Need to know the highest index in the array
      st.assign(4*n,10000000); //won't need all of these cells; 4n is enough
      lazy.assign(4*n,false); //holds the lazy flags (do we need to lazily propagate from this node?)
      lazyDelta.assign(4*n,0);  //the amount
      build(A,0,n-1,1);
    }

    void rangeUpdate(int L, int R, T deltaV) {
      if (R < L) //empty range; skip.
        return;
      rangeUpdate(L,R,deltaV,1,0,n-1);
    }

    T allQuery() { //RMQ over the whole array; we skip index zero to facilitate easy representation of the complete binary tree as an array; left child of index n is 2*n; right child is 2*n+1.
      return st[1];
    }

  private:
    int n; //number of elements in the segment tree
    vector<T> st; //the vertices on the tree
    vector<bool> lazy; //lazy flags
    vector<T> lazyDelta; //amount we need to add that the lazy flag corresponds to.

    int l(int idx) {return idx<<1;} //left child of a given node is at index 2*n.
    int r(int idx) {return (idx<<1)+1;} //right child of a given node is at index 2*n+1.

    void build(const vector<T> &A,int L, int R, int S) {
      //O(n) operation to build the tree from array A.
      //Build the current part of the segment tree responsible for the range L to R in array A.
      //S is the index in the st array reponsible for the range L to R.
      
      if (L == R) //Only one element left; base case.
        st[S] = A[L];
      else {
        build(A,L,(L+R)/2,l(S)); //build the left half
        build(A,(L+R)/2+1,R,r(S)); //build the right half
        st[S] = min(st[l(S)],st[r(S)]); //this vertex holds the min across the whole range, left and right halves.
      }
    }

    void propagateLazy(int S, int aL, int aR) { //Lazy propagation for range updates. 
      //lazy[S] is true if we have made an update to node S which has not been propagated to its children.
      
      if (lazy[S]) {
        lazy[S] = false;
        if (aL != aR)  { //not the same so not a leaf, has children to propagate the lazy flag to. 
          lazy[l(S)] = true; //will need to propagate down from the children at some point.
          lazy[r(S)] = true;
          lazyDelta[l(S)] += lazyDelta[S]; // Use += since there may be a lazy amount to add already sitting below in the child; we can combine the amount we are pushing down with that amount sitting there and later do the propagation in one go. Remember the range update operation here is to add a value to a range.
          lazyDelta[r(S)] += lazyDelta[S];
          st[l(S)] += lazyDelta[S]; //Actually do the update that we had postponed
          st[r(S)] += lazyDelta[S];
        }
        lazyDelta[S] = 0; //we have now propagated and so there is nothing pending to add at S. 
      } 
      
    }
  
    void rangeUpdate(int L, int R, int deltaV, int S, int aL, int aR) {  
      //L to R is target range to update
      //The update should consist of adding deltaV to all values in this range
      //S is the index of the current node we are considering in st array; i.e. this is a recursive procedure
      //aL to aR is the region of the array that node S is responsible for.
      
      propagateLazy(S,aL,aR);
      if (L <= aL && aR <= R) {//current range is inside updated range
        st[S] += deltaV; //all of the current range needs to be updated
        lazy[S] = true; //and this can be done lazily.
        lazyDelta[S] = deltaV;
      }  
      else {
        int leftMax = (aL+aR)/2; //boundary

        if (R <= leftMax) { //Desired range fully enclosed by left child of this node.
          rangeUpdate(L,R,deltaV,l(S),aL,leftMax); 
        }
        else if (L > leftMax) { //Desired range fully enclosed by right child of this node.
          rangeUpdate(L,R,deltaV,r(S),leftMax+1,aR); 
        }
        else { //Desired range split; some in left and some in right child of this node 
          rangeUpdate(L,leftMax,deltaV,l(S),aL,leftMax);  //update everything the left child can
          rangeUpdate(leftMax+1,R,deltaV,r(S),leftMax+1,aR); //update everything the right child can
        }
        st[S] = min(st[l(S)],st[r(S)]); //after updating children, the overall minimum may have changed.
      }
    }
};

int main() {
  int T; scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int R,C,K,S; scanf("%d %d %d %d",&R,&C,&K,&S); K--; //K from 1 in input, rebase to be from 0. 
    vector<vector<bool>> garage(R,vector<bool>(C));  //Is there a car here?
    vector<int> spacesAbove(C,0); //number of spaces above row K in column c.
    vector<int> spacesBelow(C,0); //number of spaces below row K in column c.
    
    for (int r=0;r<R;++r) { //get input of the whole garage
      string str;
      cin >> str;
      for (int c=0;c<C;++c) {
        garage[r][c] = (str[c] == 'X'); 
        if (r < K) { //is this row below or above
          spacesAbove[c] += (str[c] == '.'); //only add if it's a free space
        }
        else if (r > K) {
          spacesBelow[c] += (str[c] == '.');
        }        
      }
    }

    //Get input of all of the spells
    vector<pair<int,int>> spells;
    for (int s=0;s<S;++s) {
      int r,c;
      scanf("%d %d",&r,&c);
      r--; c--; //rebase so our grid starts at (0,0)
      spells.emplace_back(r,c);
    }
    
    vector<bool> rowK = garage[K];
    int total = 0; //total number of cars in row K at the current shift.
    vector<int> shiftCosts(R+2); // Initial shift costs: [Down5,Down4,Down3,Down2,Down1,None,Up1,Up2,Up3 etc]
                                 // Prior to all spells, if we make these shifts what will the total number of moves be?
                                 // We will build the segment tree from this prior to running the spells.
    vector<OST> cars(C);  // cars[c] contains all of the cars in column c, sorted by row from top to bottom. 

    //This initialisation code is all from part 1.
    
    //Downward shifts (i.e. row K gains a car that starts above it)
    //O(RC)
    for (int shift=1;shift<=K+1;shift++) { //we need enough shifts so that the top row can go through row K and once out to the other side; however in fact, we can see when we look at the recommended solution that we only need a maximum of C upward shifts and C downward shifts.
      total = 0; //number of cars in row K at current shift.
      for (int c=0;c<C;++c) {
        if (spacesBelow[c] > 0 || (spacesBelow[c] == 0 && rowK[c] == false)) { //Can we push into this space?
          //...Only if no gridlock or gridlock below and this space is empty.
          
          if (rowK[c]) --spacesBelow[c]; //pushed down a car so there is one fewer free space below
          if (K-shift < 0) //we have shifted down more times than there are rows above, so just invent a blank space to fill the gap created.
            rowK[c] = 0;
          else //otherwise as there's no gridlock it's just the item in the target row.
            rowK[c] = garage[K-shift][c];
        }
        total += rowK[c];
        
        if (K-shift >= 0 && garage[K-shift][c]) { //provided we haven't just invented a blank space (which would lead to out of bounds error in the second check), and there is a car here, we need to save the car to the list of cars in the current column.
          cars[c].insert(K+1-shift);
        }
        
      }
      shiftCosts[K+1-shift] = shift+total; //make "shift" shifts and remove "total" cars for a total cost of shift+total.
    }

    //Now do no shifts at all
    total = 0;
    //No shifts, simply count total Xs i.e. cars.
    for (int c=0;c<C;++c) {
      total += garage[K][c];
      if (garage[K][c]) {
        cars[c].insert(K+1); // We also need to insert all of the cars in the right OST.
      }
    }    
    shiftCosts[K+1] = (total); //K+1 downward shifts before; now the no shift. 
    
    //For all upward shifts:
    rowK = garage[K]; //simulate
    for (int shift=1;shift<=R-K;shift++) { //for each possible upward shift until we have shifted the bottom row to be one above row K (although as mentioned we could do this with a maximum of C shifts which may be better)
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesAbove[c] > 0 || (spacesAbove[c] == 0 && rowK[c] == false)) { //Can we push into this space?
          //...  Only if no gridlock or gridlock above and this space is empty. 
          
          if (rowK[c]) --spacesAbove[c]; //pushed up a car so one fewer empty space. 
          if (K+shift >= R) //Create new empty spaces from the bottom
            rowK[c] = 0;
          else
            rowK[c] = garage[K+shift][c];
        }
        total += rowK[c]; //Total number of "one car at a time" removals needed.
        if (K+shift < R && garage[K+shift][c]) { //again update the OSTs for this column
          cars[c].insert(K+1+shift);
        }
      }
      shiftCosts[K+1+shift] = (shift+total);
    }

    SegmentTree<int> shiftCostsSegTree(shiftCosts);

    // We now have:
      // SegmentTree of the costs for all possible shifts
      // Vector of OSTs each defining all of the cars in a given column c. 
        
    
    long long M_sum = 0; //The answer; total M value over all spells.

    int priorGridlockAbove, // store the index into shiftCosts at which gridlock occurs (before/after) the current spell, (below/above row K)
        newGridlockAbove,
        priorGridlockBelow,
        newGridlockBelow;

    
    for (auto [r,c] : spells) { //for every spell, take the coordinates
      int shift = r+1;  //index into shiftCosts corresponding to the shift 
      
      if (garage[r][c] == true) { //Wong is removing a car so gridlock occurs with more shifts now than it did before, or it may no longer occur at all. 

        //First check out the previous situation before the spell, in this column.

        //Above
        if (cars[c].find_by_order(K) != cars[c].end()) {  //If gridlock could occur above because there were at least K cars in the column (so gridlock would occur above once all K cars move up) 
          priorGridlockAbove = *cars[c].find_by_order(K); //shift at which gridlock currently occurs
        }
        else {
          priorGridlockAbove = shiftCosts.size(); //Gridlock doesn't yet occur, so we use sentinel of 1 above the highest upward shift, so that when it does occur we can iterate up to this point, causing it to be tracked at all higher shifts.
        }

        //Below
        if (cars[c].find_by_order(cars[c].size()-(R-K)) != cars[c].end()) { //Gridlock already occurs below. Find the car which causes it (R-Kth car from the bottom approximately); end is returned in case a fail occurs and there is no gridlock yet.
          priorGridlockBelow = *cars[c].find_by_order(cars[c].size()-(R-K));  
        }
        else { //gridlock doesn't occur below yet, so set sentinel of one below the maximum negative shift which is -1 since 0 is max downward shift.  
          priorGridlockBelow = -1;          
        }

        //Don't count the removal of the car unless it occurs somewhere with no gridlock yet, since if there is gridlock we will deal with it separately.         
	      if (priorGridlockBelow <= shift && shift <= priorGridlockAbove)  //Gridlock below occurs at downward shifts; gridlock above occurs at upward shifts. Only update shift if it is between the current thresholds for gridlocks, meaning no gridlock occurs in this column at that shift yet, and so adding this car makes a difference.
          shiftCostsSegTree.rangeUpdate(shift,shift,-1);  //Use range update over a 1 element range; degenerates into point update.
        
        cars[c].erase(shift); //Apply the spell

        //Now consider gridlocks in this column after the spell. 
        
        if (cars[c].find_by_order(K) == cars[c].end()) { //gridlock no longer occurs above
          newGridlockAbove = shiftCosts.size(); //so we use this sentinel value because we will need to reset gridlocks all the way along.
        }
        else {
          newGridlockAbove = *cars[c].find_by_order(K);
        }

        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //gridlock no longer occurs below
          newGridlockBelow = -1;
        }
        else {
          newGridlockBelow = *cars[c].find_by_order(cars[c].size()-(R-K));
        }


        //There can be no cars between the current and previous gridlock because otherwise they would have been there previously and so prevGridlock would be there.
        //Therefore any shifts between previous and current gridlock no longer have a car at that shift because gridlock does not force there to be one there.
        // (the ones with gridlock still have cars as they weren't removed - or if they were we dealt with that above - so we don't change those.)

        //Remove 1 car from all rows where there is no gridlock from above now 
        shiftCostsSegTree.rangeUpdate(priorGridlockAbove+1,newGridlockAbove-1,-1);
        
        //We want to do the same for girdlock from below, but with two differences:
        //BEcause max downward shift is before min downward shift in the shifts array, not the other way round like for upward we have to go from new to prior not the other way round.
        //We don't want to update any that we already updated in the previous update, so we only want to update those values in the followingf ranges: (no double counting)
        // [newGridlockBelow+1,priorGridlockAbove-1] AND
        // (at least newGridlockAbove OR less than priorGridlockAbove)
        // Inclusion - exlcusion to achieve this (may be two separate ranges for above and below gridlocks, so can't combine them into one call.)
        shiftCostsSegTree.rangeUpdate(newGridlockBelow+1, min(priorGridlockAbove-1,priorGridlockBelow-1),-1);
        shiftCostsSegTree.rangeUpdate(max(newGridlockAbove,newGridlockBelow+1),priorGridlockBelow-1,-1);
        shiftCostsSegTree.rangeUpdate(max(newGridlockAbove,newGridlockBelow+1),min(priorGridlockAbove-1,priorGridlockBelow-1),1);

      }
      else { //Wong is adding a car so gridlock can occur at a lower shift than before, or when it didn't occur before.
 

        //Check for gridlock above row K, before the current spell.
        if (cars[c].find_by_order(K) == cars[c].end())
          priorGridlockAbove = shiftCosts.size();
        else
          priorGridlockAbove = *cars[c].find_by_order(K); 

        //Check for gridlock below row K, prior to the current spell.
        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end())
          priorGridlockBelow = -1;
        else
          priorGridlockBelow = *cars[c].find_by_order(cars[c].size()-(R-K));
        
        //Enact the spell; adding a new car.
        cars[c].insert(shift);

        //Now check for gridlock after the spell
        
        if (cars[c].find_by_order(K) == cars[c].end())
          newGridlockAbove = shiftCosts.size();
        else
          newGridlockAbove = *cars[c].find_by_order(K);

        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end())
          newGridlockBelow = -1;

        else
          newGridlockBelow = *cars[c].find_by_order(cars[c].size()-(R-K)); 

        if (newGridlockBelow <= shift && shift <= newGridlockAbove) //As long as this doesn't interfere with gridlock.
          shiftCostsSegTree.rangeUpdate(shift,shift,1);

        //Update the gridlock-affected ranges.
        shiftCostsSegTree.rangeUpdate(newGridlockAbove+1,priorGridlockAbove-1,1); //between the two, as above
        //Again apply inclusion-exclusion to ensure we don't double count
        shiftCostsSegTree.rangeUpdate(priorGridlockBelow+1,min(newGridlockBelow-1,newGridlockAbove-1),1);
        shiftCostsSegTree.rangeUpdate(max(priorGridlockAbove,priorGridlockBelow+1),newGridlockBelow-1,1);
        shiftCostsSegTree.rangeUpdate(max(priorGridlockAbove,priorGridlockBelow+1),min(newGridlockBelow-1,newGridlockAbove-1),-1);

      }
      garage[r][c] = !garage[r][c]; //Actually update the garage!
      int M = shiftCostsSegTree.allQuery(); //get cheapest way to solve the current problem.
      M_sum += M;
      
    } 
    
    printf("Case #%d: %lld\n",t,M_sum);
  }
  
  return 0;
}
