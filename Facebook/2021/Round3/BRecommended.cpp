#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9+10;
const int MOD = 1e9+7;

class SegmentTree {
  public:
    SegmentTree(int n):n(n) { 
      st.assign(4*n,0); 
      lazy.assign(4*n,false); 
    }

    long long rangeQuery(int L, int R) {
      return rangeQuery(L,R,0,n-1,1);
    }

    void rangeUpdate(int v, int L, int R) {
      rangeUpdate(v,L,R,0,n-1,1);
    }

  protected:
    int n; 
    vector<long long> st; 
    vector<bool> lazy; 

    int l(int idx) {return idx<<1;} 
    int r(int idx) {return (idx<<1)+1;} 

    void propagateLazy(int S,int L,int R) {
      if (lazy[S] == true) {
        lazy[S] = false;
        if (L != R) {
          lazy[l(S)] = lazy[r(S)] = true;
          st[l(S)] = st[r(S)] = st[S];
        }
      }
    }

    long long rangeQuery(int L, int R, int aL, int aR, int S) {   
      propagateLazy(S,aL,aR);
      if (aL == L && aR == R)
        return st[S];

      int leftMax = (aL+aR)/2; 
      if (R <= leftMax)//fully covered by left.
        return rangeQuery(L,R,aL,leftMax,l(S));  
      else if (L >= leftMax+1)
        return rangeQuery(L,R,leftMax+1,aR,r(S));
      else {
        return max(rangeQuery(L,leftMax,aL,leftMax,l(S)),rangeQuery(leftMax+1,R,leftMax+1,aR,r(S)));
      }
    }

    void rangeUpdate(int v,int L, int R, int aL, int aR, int S) {   
      propagateLazy(S,aL,aR);
      if (L <= aL && aR <= R) { //current range inside target range;
        st[S] = v;
        lazy[S] = true;
      }
      else {
        int leftMax = (aL+aR)/2;
        if (R <= leftMax)//fully covered by left.
          rangeUpdate(v,L,R,aL,leftMax,l(S));  
        else if (L >= leftMax+1)
          rangeUpdate(v,L,R,leftMax+1,aR,r(S));
        else {
          rangeUpdate(v,L,leftMax,aL,leftMax,l(S));
          rangeUpdate(v,leftMax+1,R,leftMax+1,aR,r(S));
        }
        st[S] = max(st[r(S)],st[l(S)]);
      }
    }
};

class CrazySegmentTree {
  public:
    CrazySegmentTree(int n):n(n) { 
      st.assign(4*n,vector<vector<long long>>(3,vector<long long>(3,INF))); 
    }

    long long getWithAandB(int R1, int R2, int a, int b) {
      return getRows(R1,R2,0,n-1,1)[a][b];
    }

    void add(int R, int C) {
      add(R,C,0,n-1,1);
    }

  protected:
    int n; 
    vector<vector<vector<long long>>> st; 

    int l(int idx) {return idx<<1;} 
    int r(int idx) {return (idx<<1)+1;} 
    vector<vector<long long>> getRows(int R1, int R2, int aL, int aR, int S) {
      if (R1 <= aL && aR <= R2) {//inside target range
        return st[S];
      }
      else {
        int leftMax = (aL+aR)/2;
        if (R2 <= leftMax)//fully covered by left.
          return getRows(R1, R2, aL, leftMax,l(S));  
        else if (R1 >= leftMax+1)
          return getRows(R1,R2,leftMax+1,aR,r(S));
        else {
          vector<vector<long long>> side = getRows(R1,R2,aL,leftMax,l(S));
          vector<vector<long long>> side2 = getRows(R1,R2,leftMax+1,aR,r(S));
          vector<vector<long long>> result(3,vector<long long>(3,INF));
          
          for (int a=0;a<3;++a) {
            for (int b=0;b<3;++b) {
              for (int c=0;c<3;++c) {
                result[a][b] = min(result[a][b],side[a][c]+side2[c][b]+1);
              }
            }
          }
          return result;
        }
      }
    } 
    void add(int R, int C, int aL, int aR, int S) {  
      if (aL == aR && aR == R) { //we found the target row
        st[S][C][C] = 0;

        //lateral moves
        if (C-1 >= 0 && st[S][C-1][C-1] == 0) {
          st[S][C-1][C] = 1;
          st[S][C][C-1] = 1;
        }
        if (C+1 < 3 && st[S][C+1][C+1] == 0) {
          st[S][C+1][C] = 1;
          st[S][C][C+1] = 1;
        }
        if (C+2 < 3 && st[S][C+2][C+2] == 0 && st[S][C+1][C+1] == 0) {
          st[S][C+2][C] = 2;
          st[S][C][C+2] = 2;
        }
        if (C-2 >= 0 && st[S][C-2][C-2] == 0 && st[S][C-1][C-1] == 0) {
          st[S][C-2][C] = 2;
          st[S][C][C-2] = 2;
        }
       if (C-1 >= 0 && C+1 < 3 && st[S][C-1][C] == 1 && st[S][C][C+1] == 1) {
         st[S][C-1][C+1] = 2;
         st[S][C+1][C-1] = 2;
       }
      
      }
      else {
        int leftMax = (aL+aR)/2;
        if (R <= leftMax) //fully covered by left.
          add(R,C,aL,leftMax,l(S));  
        else 
          add(R,C,leftMax+1,aR,r(S));


        for (int a=0;a<3;++a) {
          for (int b=0;b<3;++b) {
            for (int c=0;c<3;++c) {
              st[S][a][b] = min(st[S][a][b],st[l(S)][a][c]+st[r(S)][c][b]+1);
            }
          }
        }
      }
      
    }

};

const int N_MAX = 1e6;
vector<int> counts;
vector<vector<int>> grid;
set<int> emptyRows;
SegmentTree leftSegTree(N_MAX);
SegmentTree rightSegTree(N_MAX);
CrazySegmentTree midSectionTree(N_MAX);

void reset(int N) {
  counts.assign(N,0);
  emptyRows.clear();
  grid.assign(N,vector<int>(3,0));
  leftSegTree.rangeUpdate(1,0,N-1);
  rightSegTree.rangeUpdate(1,0,N-1);
  midSectionTree = CrazySegmentTree(N);
}

void addToGrid(int R, int C) {
  if (C == 0)
    leftSegTree.rangeUpdate(0,R,R);
  else if (C == 2)
    rightSegTree.rangeUpdate(0,R,R);

  counts[R] += 1;
  if (counts[R] == 3)
    emptyRows.insert(R);

  midSectionTree.add(R,C);
  grid[R][C] = 1;
}

long long solve(int R1, int C1, int R2, int C2) {
  long long minCost = INF;

  for (int a=0;a<3;++a) {
    for (int b=0;b<3;++b) {
      if (grid[R1][a] && grid[R2][b]) {
        //top section 
        long long topSection = INF;
        if (a == C1) topSection = 0;
        else if (abs(a-C1) == 1) topSection = 1;
        else if (emptyRows.find(R1) != emptyRows.end()) {
          topSection = 2;
        }
        else {
          if (emptyRows.lower_bound(R1) != emptyRows.begin())  {
            int firstCrossingPoint = *prev(emptyRows.lower_bound(R1));
            if (leftSegTree.rangeQuery(firstCrossingPoint,R1) == 0 && rightSegTree.rangeQuery(firstCrossingPoint,R1) == 0) {
              topSection = 2+2*(R1-firstCrossingPoint);        
            }
          }
        }
        //middle section
        long long midSection = 0;
        midSection = midSectionTree.getWithAandB(R1,R2,a,b);
        
        //bottom section
        long long bottomSection = INF;
        if (b == C2) bottomSection = 0;
        else if (abs(b-C2) == 1) bottomSection = 1;
        else {
          if (emptyRows.lower_bound(R2) != emptyRows.end()) {
            int secondCrossingPoint = *emptyRows.lower_bound(R2);
            if (leftSegTree.rangeQuery(R2,secondCrossingPoint) == 0 && rightSegTree.rangeQuery(R2,secondCrossingPoint) == 0) {
              bottomSection = 2+2*(secondCrossingPoint-R2);        
            }
          }
        } 
        
        minCost = min(minCost,topSection+midSection+bottomSection);

      }
    }
  }
  return minCost;
}




int main() {
  int T;
  scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int N,M;
    scanf("%d %d",&N,&M);

    reset(N);
    
    int ans = 1;    
    vector<tuple<int,int,int,int,int>> ops;

    for (int n=0;n<N;++n) {
      for (int i=0;i<3;++i) {
        int A;
        scanf("%d",&A);
        ops.emplace_back(A,-1,-1,n,i);
      }
    }

    for (int m=0;m<M;++m) {
      int R1,C1,R2,C2,A;
      scanf("%d %d %d %d %d",&R1,&C1,&R2,&C2,&A);
      --R1;--C1;--R2;--C2;
      if (R1 > R2) {
        swap(R1,R2);
        swap(C1,C2);
        //Now R1 <= R2;
      }
      ops.emplace_back(A,R1,C1,R2,C2);      
    }

    sort(ops.begin(),ops.end());
    for (auto [A,R1,C1,R2,C2] : ops) {
      if (R1 == -1) {
        addToGrid(R2,C2);
      }
      else {
        long long cost = solve(R1,C1,R2,C2);
        if (cost >= INF)
          cost = 1;
        ans = (ans * (cost % MOD)) % MOD;
      }
    }
    printf("Case #%d: %d",t,ans);
    cout << endl;
  }
  
  return 0;
}
