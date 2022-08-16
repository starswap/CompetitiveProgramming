// Initially there are directed edges between each node and all nodes with a lower value than it (n(n-1)/2) of these overall.
// Adding a pairing means that all nodes between those two nodes can now receive orders from each all of the others in that group, so there are backwards edges between every one in that group. This adds an additional 0 edges to the most senior, 1 to the next most, then 2, 3 and so on.
// Now anyone in that group can receive orders from anyone else 
// If you connect two employees, at least one of which is already part of a cycle, you simply get a bigger cycle with everyone that could already be reached by the two paired employees
// A given employee can only be part of 1 cycle, because if they are part of 2 then in reality this is actually just one bigger cycle.
// We just need to count the number of back edges allowing a less senior person to give orders to a more senior person and then add on N(N-1)/2 for the original front edges.
// One way of doing this is to:

  // Maintain 3 segment trees: Start, End, Delta, indexed by employee number.
  // Start holds the number of the most senior employee in the reporting group that this employee is a member of
  // End holds the number of the least senior employee in the reporting group that this employee is a member of
  // Delta holds the number of back edges that have this employee as the least senior employee who is getting reports from a more senior employee
  // For each pairing operation where A is the lower numbered employee and B is the higher numbered employee
    // A = min(A,S[A]) // A is in a reporting group with employees as senior as Start[A], so these will join the new bigger group after this merge.
    // B = max(B,E[B]) // B is in a reporting group with employees as low as End[B] (this must be lower than End[A] as there are no overlaps)
    // The reporting group now goes from A to B
    // D.setRangeIncremental(A,B,0)  //overwrite existing deltas in such a way that we say that the number of back edges is 0 for the most senior person in this group, then 1, then 2, then 3, which can be done in log time with lazy propagation (overwrite any previous info to avoid issues with for example 2-3 then 1-4)
      // This operation does the following: from this example array, [1,5,6,2,10,4,7] setRangeIncremental(start=2,end=5,firstvalue=19) does: [1,5,19,20,21,22,7]
    // S.setRange(A,B,A) //The new reporting group for all of these employees starts at A and ends at B
    // E.setRange(A,B,B)
    // S_i = N(N-1)/2 + D.rangeSum(1,N) //sum of all back edges
    // Do product and mod

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1'000'000'007;

template <class Ta,class Tb>
inline Tb modProduct(Ta a, Ta b, Tb mod) {
  return ((a % mod)*(b % mod))%mod;
}

class SegmentTreeBase {

public:
    SegmentTreeBase(const vector<long long> &A) { 
      n = A.size(); 
      st.assign(4*n,10000000); 
      lazy.assign(4*n,false); 
      lazyDelta.assign(4*n,0);  
      build(A,0,n-1,1);
    }

    long long allQuery() {
      return st[1];
    }

    long long operator [] (int index) {
      return pointQuery(index,0,n-1,1); 
    }

  protected:
    int n; 
    vector<long long> st; 
    vector<bool> lazy; 
    vector<long long> lazyDelta; 

    int l(int idx) {return idx<<1;} 
    int r(int idx) {return (idx<<1)+1;} 

    virtual void propagateLazy(int S,int L,int R) {}

    void build(const vector<long long> &A,int L, int R, int S) {  
        if (L == R) 
          st[S] = A[L];
        else {
          build(A,L,(L+R)/2,l(S)); 
          build(A,(L+R)/2+1,R,r(S));
          st[S] = st[l(S)]+st[r(S)];
        }
    }

    long long pointQuery(int index, int L, int R, int S) {
      propagateLazy(S,L,R);
      if (L == R)
        return st[S];
      else {
        int leftMax = (L+R)/2;
        if (index <= leftMax)
          return pointQuery(index,L,leftMax,l(S));
        else
          return pointQuery(index,leftMax+1,R,r(S));
      }
    }

};


class SegmentTreeIncremental : public SegmentTreeBase {
  public:
    SegmentTreeIncremental(const vector<long long> &A):SegmentTreeBase(A) {}

    void rangeUpdateIncremental(int L, int R, long long initDelta) {
      if (R < L) 
        return;
      rangeUpdateIncremental(L,R,initDelta,1,0,n-1);
    }

  protected:
    long long computeAmt(long long numToUpdate, long long initDelta) {
      return numToUpdate*initDelta + numToUpdate*(numToUpdate-1)/2;
    }

    void propagateLazy(int S, int aL, int aR) {
      
      if (lazy[S]) {
        lazy[S] = false;
        if (aL != aR)  {
          lazy[l(S)] = true;
          lazy[r(S)] = true;
          lazyDelta[l(S)] = lazyDelta[S]; 
          
          int leftMax = (aL+aR)/2; 
          lazyDelta[r(S)] = lazyDelta[S] + (leftMax-aL+1);
          st[l(S)] = computeAmt(leftMax-aL+1,lazyDelta[l(S)]);
          st[r(S)] = computeAmt(aR-leftMax,lazyDelta[r(S)]);
        }
        lazyDelta[S] = 0;
      } 
    }  

    void rangeUpdateIncremental(int L, int R, long long initDelta, int S, int aL, int aR) {  
   
      propagateLazy(S,aL,aR);
      if (L <= aL && aR <= R) {
        st[S] = computeAmt(R-L+1,initDelta);
        lazy[S] = true; 
        lazyDelta[S] = initDelta;
      } 
        
      else {
        int leftMax = (aL+aR)/2; 

        if (R <= leftMax) { 
          rangeUpdateIncremental(L,R,initDelta,l(S),aL,leftMax); 
        }
        else if (L > leftMax) { 
          rangeUpdateIncremental(L,R,initDelta,r(S),leftMax+1,aR); 
        }
        else { 
          rangeUpdateIncremental(L,leftMax,initDelta,l(S),aL,leftMax); 
          rangeUpdateIncremental(leftMax+1,R,initDelta+(leftMax-L+1),r(S),leftMax+1,aR); 
        }
        st[S] = st[l(S)] + st[r(S)];
      }
    }

};

class SegmentTree : public SegmentTreeBase {

public:
    SegmentTree(const vector<long long> &A):SegmentTreeBase(A) {}

    void rangeUpdate(int L, int R, long long V) {
      if (R < L)
        return;
      rangeUpdate(L,R,V,1,0,n-1);
    }


  private:

    void propagateLazy(int S, int aL, int aR) { 
      
      if (lazy[S]) {
        lazy[S] = false;
        if (aL != aR)  { 
          lazy[l(S)] = true;
          lazy[r(S)] = true;
          lazyDelta[l(S)] = lazyDelta[S];
          lazyDelta[r(S)] = lazyDelta[S];
          st[l(S)] = lazyDelta[S]; 
          st[r(S)] = lazyDelta[S];
        }
        lazyDelta[S] = 0;
      } 
      
    }
  
    void rangeUpdate(int L, int R, long long V, int S, int aL, int aR) {  
      
      propagateLazy(S,aL,aR);
      if (L <= aL && aR <= R) {
        st[S] = V; 
        lazy[S] = true; 
        lazyDelta[S] = V;
      }  
      else {
        int leftMax = (aL+aR)/2; 

        if (R <= leftMax) { 
          rangeUpdate(L,R,V,l(S),aL,leftMax); 
        }
        else if (L > leftMax) { 
          rangeUpdate(L,R,V,r(S),leftMax+1,aR); 
        }
        else { 
          rangeUpdate(L,leftMax,V,l(S),aL,leftMax); 
          rangeUpdate(leftMax+1,R,V,r(S),leftMax+1,aR);
        }
        st[S] = st[l(S)] + st[r(S)];
      }
    }
};


long long solve(int M, int N) {
  
  long long S_i;
  long long S_product = 1;

  vector<long long> range(N+1);
  iota(std::begin(range), std::end(range), 0);
  
  SegmentTree Start(range);
  SegmentTree End(range);
  SegmentTreeIncremental D(vector<long long>(N+1,0));
  
  for (int m=0;m<M;++m) {
    long long A,B;
    scanf("%lld %lld",&A,&B);

    if (A == B) continue;
    if (A > B) swap(A,B);
    A = min(A, Start[A]);
    B = max(B, End[B]);
    D.rangeUpdateIncremental(A,B,0);
    Start.rangeUpdate(A,B,A);
    End.rangeUpdate(A,B,B);

    S_i = (static_cast<long long>(N)*(static_cast<long>(N)-1))/2 + D.allQuery();
    S_product = modProduct(S_product, S_i, MOD);
  }
  
  return S_product;
}

int main() {
  int T;
  scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int N, M;
    scanf("%d %d",&N,&M);
    printf("Case #%d: %lld\n",t,solve(M, N));
  }
}
