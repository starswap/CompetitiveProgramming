#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  private:
    vector<int> st;
    vector<int> lazy;
    int n;
    inline int parent(int a) {return a>>1;}
    inline int lChild(int a) {return a<<1;}
    inline int rChild(int a) {return (a<<1) + 1;}
    inline int compare(int a,int b) {return a+b;}

    void build(vector<int> &A,int L,int R,int p) {
      if (L==R) {st[p] = A[L];}
      else if (L > R) {return;}
      else {
        int middle = (L+R)/2;
        build(A,L,middle,lChild(p));
        build(A,middle+1,R,rChild(p));
        st[p] = compare(st[lChild(p)],st[rChild(p)]);
      }
    }

    void propagateLazy(int L, int R, int p) {
      if (L == R) {lazy[p] = 0;return;}

      if (lazy[p] == 1) {
        lazy[lChild(p)] = 1;
        lazy[rChild(p)] = 1;
        st[lChild(p)] = st[p]/(R-L+1) * ((R-L+1)/2 + ((R-L+1)%2))  ;
        st[rChild(p)] = st[p]/(R-L+1)*( (R-L+1)/2 );
        lazy[p] = 0;
      } else if (lazy[p] == 2){ //lazy inverse operation

        //push lazies down before they get overwritten.OR NOT???
        if (lazy[lChild(p)] != 0)
          propagateLazy(L,(L+R)/2,lChild(p));
        if (lazy[rChild(p)] != 0)
          propagateLazy((L+R)/2+1,R,rChild(p));

        lazy[lChild(p)] = 2;
        lazy[rChild(p)] = 2;
        st[lChild(p)] = (R-L+1)/2 + ((R-L+1)%2) - st[lChild(p)];
        st[rChild(p)] = (R-L+1)/2 - st[rChild(p)];
        lazy[p] = 0;
      }
    }

    void rangeUpdate(int i,int j,int L, int R, int val,int p) {
        propagateLazy(L,R,p);
        //MAY NEED TO DO SOMETHING IF i > j; i..e return.
        if (L >= i && R <= j) { //we are within the required range
          st[p] = (R-L+1)*val;
          lazy[p] = 1; //may need to popagate lazy flags again here.
        } 
        else {
          int leftMax = (L+R)/2;
          if (i > leftMax) { //desired range fully enclosed by right child of this node
            rangeUpdate(i,j,leftMax+1,R,val,rChild(p));
          } else if (j <= leftMax) { //desired range fully enclosed by left child of this node
            rangeUpdate(i,j,L,leftMax,val,lChild(p));
          } else { //desired range split across both children of this node.
            rangeUpdate(i,leftMax,L,leftMax,val,lChild(p));
            rangeUpdate(leftMax+1,j,leftMax+1,R,val,rChild(p));
          }
          st[p] = compare(st[lChild(p)],st[rChild(p)]);
        }
    }

    void inverseUpdate(int i,int j,int L, int R, int p) {
        propagateLazy(L,R,p);
        if (L >= i && R <= j) { //we are within the required range
          st[p] = (R-L+1)-st[p];
          lazy[p] = 2; //may need to popagate lazy flags again here.
        } 
        else {
          int leftMax = (L+R)/2;
          if (i > leftMax) { //desired range fully enclosed by right child of this node
            inverseUpdate(i,j,leftMax+1,R,rChild(p));
          } else if (j <= leftMax) { //desired range fully enclosed by left child of this node
            inverseUpdate(i,j,L,leftMax,lChild(p));
          } else { //desired range split across both children of this node.
            inverseUpdate(i,leftMax,L,leftMax,lChild(p));
            inverseUpdate(leftMax+1,j,leftMax+1,R,rChild(p));
          }
          st[p] = compare(st[lChild(p)],st[rChild(p)]);
        }
    }    
    
    int RSQ(int i, int j, int L, int R, int p) {
      propagateLazy(L,R,p);
      if (L >= i && R <= j) {return st[p];}
      else {
        int leftMax = (L+R)/2;
        if (i > leftMax) { //desired range fully enclosed by right child of this node
          return RSQ(i,j,leftMax+1,R,rChild(p));
        } else if (j <= leftMax) { //desired range fully enclosed by left child of this node
          return RSQ(i,j,L,leftMax,lChild(p));
        } else { //desired range split across both children of this node.
          return compare(RSQ(i,leftMax,L,leftMax,lChild(p)),RSQ(leftMax+1,j,leftMax+1,R,rChild(p)));
        }
        st[p] = compare(st[lChild(p)],st[rChild(p)]);
      }
    }


  public:
    SegmentTree (vector<int> A) {
      n = A.size();
      st.assign(4*n,-1); //4* should give enough space.
      lazy.assign(4*n,0);
      build(A,0,n-1,1); //NOTE: the internal indexing (on st) should start from 1.
    }

    void rangeUpdate(int i, int j,int val) {
      rangeUpdate(i,j,0,n-1,val,1);
    }

    void inverseUpdate(int i, int j) {
      inverseUpdate(i,j,0,n-1,1);
    }    

    int RSQ(int i, int j) {
      return RSQ(i,j,0,n-1,1);
    }

};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  cin >> T;
  for (int t=0;t<T;t++) {
    cout << "Case " << t+1 << ":" << '\n';
    int M;
    cin >> M;
    int times;
    vector<int> Pirates;
    string pirates;

    for (int m=0;m<M;m++) {
      cin >> times;
      cin >> pirates;
      for (int tim=0;tim<times;tim++) {
        for (auto chr : pirates) {
          if (chr == '0')
            Pirates.push_back(0);
          else if (chr == '1')
            Pirates.push_back(1);
        }
      }
    }
    SegmentTree t1(Pirates);
    int Q;
    cin >> Q;
    int gq = 1;
    for (int q=0;q<Q;q++) {
      char cmd;
      int a,b;
      cin >> cmd;
      cin >> a; cin >> b;
      switch (cmd) {
        case 'F' : t1.rangeUpdate(a,b,1); break;
        case 'E' : t1.rangeUpdate(a,b,0); break;
        case 'I' : t1.inverseUpdate(a,b); break;
        case 'S' : {
          cout << "Q" << gq << ": " << t1.RSQ(a,b) << '\n'; 
          ++gq;
        }
      }
    }

  }
}
