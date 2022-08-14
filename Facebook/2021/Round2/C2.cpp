#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace __gnu_pbds;
using namespace std;



template <class T>
class SegmentTree {
  public:
    SegmentTree(const vector<T> &A) {
      n = A.size();
      st.assign(4*n,10000000);
      lazy.assign(4*n,false);
      lazyDelta.assign(4*n,0);
      build(A,0,n-1,1);
    }

    void rangeUpdate(int L, int R, int deltaV) {
      rangeUpdate(L,R,deltaV,1,0,n-1);
    }

    T allQuery() {
      return st[1];
    }

  private:
    int n;
    vector<T> st;
    vector<bool> lazy;
    vector<T> lazyDelta;

    int l(int idx) {return idx*2;}
    int r(int idx) {return idx*2+1;}

    void build(const vector<T> &A,int L, int R, int S) {
      if (L == R)
        st[S] = A[L];
      else {
        build(A,L,(L+R)/2,l(S));
        build(A,(L+R)/2+1,R,r(S));
        st[S] = min(st[l(S)],st[r(S)]);
      }
    }

    void propagateLazy(int S, int detlaV, int aL, int aR) {
      if (lazy[S]) {
        lazy[S] = false;
        if (aL != aR)  { //not the same, not a leaf, has children. 
          lazy[l(S)] = true;
          lazy[r(S)] = true;
          lazyDelta[l(S)] += lazyDelta[S];
          lazyDelta[r(S)] += lazyDelta[S];
          st[l(S)] += lazyDelta[S];
          st[r(S)] += lazyDelta[S];
        }
        lazyDelta[S] = 0;
      } 
    }
  
    void rangeUpdate(int L, int R, int deltaV, int S, int aL, int aR) {  
      if (R < L)
        return;
      propagateLazy(S,deltaV,aL,aR);
      if (aL >= L && aR <= R) {//current range inside updated range
        st[S] += deltaV;
        lazy[S] = true;
        lazyDelta[S] = deltaV;
      }  
      else {
        int leftMax = (aL+aR)/2;

        if (L > leftMax) {
          rangeUpdate(L,R,deltaV,r(S),leftMax+1,aR); //MUST REMEMBER TO UPDATE RANGE TO SET
        }
        else if (R <= leftMax) { //Desired range fully enclosed by left child of this node.
          rangeUpdate(L,R,deltaV,l(S),aL,leftMax); //MUST REMEMBER TO UPDATE RANGE TO SET
        }
        else {
          rangeUpdate(L,leftMax,deltaV,l(S),aL,leftMax); //MUST REMEMBER TO UPDATE RANGE TO SET
          rangeUpdate(leftMax+1,R,deltaV,r(S),leftMax+1,aR); //MUST REMEMBER TO UPDATE RANGE TO SET
        }
        st[S] = min(st[l(S)],st[r(S)]);
      }
    }
};

template <class T>
class SegmentTreeF {
  public:
    SegmentTreeF(const vector<T> &Arr) {
      n = A.size();
      build(Arr,0,A.size()-1,1);
    }

    void rangeUpdate(int L, int R, int deltaV) {
      for (int i=L;i<=R;++i)
        A[i] += deltaV;
    }

    T allQuery() {
      return *min_element(A.begin(),A.end());
    }

  private:
    int n;
    vector<T> A;
   
    void build(const vector<T> &Arr,int L, int R, int S) {
      A = Arr;
    }
};



// Order Statistics Tree
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    OST;

int main() {
  int T; scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int R,C,K,S; scanf("%d %d %d %d",&R,&C,&K,&S); K--;
    vector<vector<bool>> garage(R,vector<bool>(C));   //Is there a car here?
    vector<int> spacesAbove(C,0);
    vector<int> spacesBelow(C,0);
    
    for (int r=0;r<R;++r) {
      string str;
      cin >> str;
      for (int c=0;c<C;++c) {
        garage[r][c] = (str[c] == 'X');
        if (r < K) {
          spacesAbove[c] += (str[c] == '.');
        }
        if (r > K) {
          spacesBelow[c] += (str[c] == '.');
        }        
      }
    }

    vector<pair<int,int>> spells;
    for (int s=0;s<S;++s) {
      int r,c;
      scanf("%d %d",&r,&c);
      r--; c--;
      spells.emplace_back(r,c);
    }
    
    vector<bool> rowK = garage[K];
    int total = 0;
    vector<int> shiftCosts(R+2); // Will become a segment tree.
    vector<OST> cars(C);

    //Downward shifts    
    for (int shift=1;shift<=K+1;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesBelow[c] > 0 || rowK[c] == false) { //Can we push into this space?
          //...Only if no gridlock or gridlock below and this space is empty.
          
          if (rowK[c]) --spacesBelow[c]; //pushed down a car
          if (K-shift < 0) 
            rowK[c] = 0;
          else
            rowK[c] = garage[K-shift][c];
        }
        total += rowK[c];
        
        if (K-shift >= 0 && garage[K-shift][c]) {
          cars[c].insert(K+1-shift);
        }
        
      }
      shiftCosts[K+1-shift] = shift+total;
    }

    rowK = garage[K];
    total = 0;
    //No shifts, total Xs.
    for (int c=0;c<C;++c) {
      total += rowK[c];
      if (garage[K][c]) {
        cars[c].insert(K+1);
      }
    }    
    shiftCosts[K+1] = (total);
    
    //For all upward shifts:
    rowK = garage[K];
    for (int shift=1;shift<=R-K;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesAbove[c] != 0 || rowK[c] == false) { //Can we push into this space? (NOTE: TCs a little weak; don't require rowK[c] == false here.)
          //...  Only if no gridlock or gridlock above and this space is empty. 
          
          if (rowK[c]) --spacesAbove[c]; //pushed up a car so one fewer empty space. 
          if (K+shift >= R) //Create new empty spaces from the bottom
            rowK[c] = 0;
          else
            rowK[c] = garage[K+shift][c];
        }
        total += rowK[c]; //Total number of one car at a time moves needed.
        if (K+shift < R && garage[K+shift][c]) {
          cars[c].insert(K+1+shift);
        }
      }
      shiftCosts[K+1+shift] = (shift+total);
    }

    long long M_sum = 0;
    int prevGridlock, currGridlock, prevGridlock2, currGridlock2;

    SegmentTree<int> shiftCostsSegTree(shiftCosts);
    
    for (auto [r,c] : spells) {
      int shift = r+1;
      
      if (garage[r][c] == true) { //Wong is removing a car
        //shiftCostsSegTree.rangeUpdate(shift,shift,-1);  
        
        if (cars[c].find_by_order(K) != cars[c].end()) { //gridlock occurs one later now than it did before
          prevGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...
        }
        else {
          prevGridlock = shiftCosts.size();
        }
        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //doesn't occur now.
          prevGridlock2 = -1;
        }
        else {
          prevGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K));
        }
        
	      if (shift <= prevGridlock && shift >= prevGridlock2)
          shiftCostsSegTree.rangeUpdate(shift,shift,-1);  
        
        cars[c].erase(shift);
        if (cars[c].find_by_order(K) == cars[c].end()) { //doesn't occur now.
          currGridlock = shiftCosts.size();
        }
        else {currGridlock = *cars[c].find_by_order(K);}

        //otherwise would have been gridlocked already just groikvkj it.
        //still has a car so don't change it.

        shiftCostsSegTree.rangeUpdate(prevGridlock+1,currGridlock-1,-1);
        // for (int g=prevGridlock+1;g<currGridlock;++g) {
        //   shiftCosts[g] -= 1;
        // }
        
        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //doesn't occur now.
          currGridlock2 = -1;
        }
        else {currGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K));}

        //Inclusion - exlcusion
        shiftCostsSegTree.rangeUpdate(currGridlock2+1, min(prevGridlock-1,prevGridlock2-1),-1);
        shiftCostsSegTree.rangeUpdate(max(currGridlock,currGridlock2+1),prevGridlock2-1,-1);
        shiftCostsSegTree.rangeUpdate(max(currGridlock,currGridlock2+1),min(prevGridlock-1,prevGridlock2-1),1);

	          //if (!(prevGridlock <= g && g < currGridlock))     //provided we haven't already dealt with it.      
        
        //still has a car so don't change it.
        // for (int g=currGridlock+1;g<prevGridlock2;++g) {
        //   shiftCosts[g] -= 1;
        // }
        
      }
      else { //Wong is adding a car
   //     shiftCostsSegTree.rangeUpdate(shift,shift,1);  
        
        // shiftCosts[shift] += 1;  
        if (cars[c].find_by_order(K) == cars[c].end()) { //gridlock occurs one earlier now than it did before
          prevGridlock = shiftCosts.size();
        }
        else
          prevGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...

        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //gridlock occurs one earlier now than it did before
          prevGridlock2 = -1;
        }
        else
          prevGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K)); //shift at which gridlock currently occurs or end...
        
        
        cars[c].insert(shift);
        
        if (cars[c].find_by_order(K) == cars[c].end()) { //gridlock occurs one earlier now than it did before
          currGridlock = shiftCosts.size();
        }
        else
          currGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...

    //    shiftCostsSegTree.rangeUpdate(currGridlock+1,prevGridlock-1,1);

        // for (int g=currGridlock+1;g<prevGridlock;++g) {
        //   shiftCosts[g] += 1;
        // }

        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //gridlock occurs one later now than it did before
          currGridlock2 = -1;
        }
        else
          currGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K)); //shift at which gridlock currently occurs or end...

//        shiftCostsSegTree.rangeUpdate(prevGridlock2+1,currGridlock-1,1);

        	
        if (shift <= currGridlock && shift >= currGridlock2)
          shiftCostsSegTree.rangeUpdate(shift,shift,1);

        shiftCostsSegTree.rangeUpdate(currGridlock+1,prevGridlock-1,1);
        shiftCostsSegTree.rangeUpdate(prevGridlock2+1,min(currGridlock2-1,currGridlock-1),1);
        shiftCostsSegTree.rangeUpdate(max(prevGridlock,prevGridlock2+1),currGridlock2-1,1);
        shiftCostsSegTree.rangeUpdate(max(prevGridlock,prevGridlock2+1),min(currGridlock2-1,currGridlock-1),-1);


        // for (int g=prevGridlock2+1;g<currGridlock2;++g) {
        //   if (!(currGridlock <= g && g < prevGridlock))
        //     shiftCosts[g] += 1;
        // }
      
        

        // for (int g=prevGridlock2+1;g<currGridlock;++g) {
        //   shiftCosts[g] += 1;
        // }

      }
      garage[r][c] = !garage[r][c];
      int minn = shiftCostsSegTree.allQuery();
      M_sum += minn;
      
    }
    
    printf("Case #%d: %lld\n",t,M_sum);
  }
  
  return 0;
}
