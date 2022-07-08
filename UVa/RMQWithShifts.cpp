#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  private:
    int n;
    vector<int> st;
    inline int l(int a) {return a<<1;}
    inline int r(int a) {return (a<<1)+1;}
    vector<int> Arr;

    void build(const vector<int> &A,int L, int R, int p) {
      if (L==R) {st[p] = A[L];}
      else {
        build(A,L,(L+R)/2,l(p));
        build(A,(L+R)/2+1,R,r(p));
        st[p] = min(st[l(p)],st[r(p)]);
      }
    }

    void pointUpdate(int i,int val,int L, int R, int p) {
      if (L==R) {st[p] = val;Arr[L] = val;}
      else {
        int mid = (L+R)/2;
        if (i >= mid+1) {
          pointUpdate(i,val,mid+1,R,r(p));
        } else {
          pointUpdate(i,val,L,mid,l(p));
        }
        st[p] = min(st[l(p)],st[r(p)]);
      }
    }

    int rmq(int i, int j, int L, int R, int p) {
      if (L >= i && R <= j) {return st[p];}
      else {
        int m = (L+R)/2;
        if (i >= m+1) {
          return rmq(i,j,m+1,R,r(p)); //fully enclosed by right.
        } else if (j <= m) {
          return rmq(i,j,L,m,l(p)); //fully enclosed by left
        } else {
          return min(rmq(i,m,L,m,l(p)),
                     rmq(m+1,j,m+1,R,r(p)));
        }
      }
    }

  public:
    SegmentTree(const vector<int> &A) {
      Arr = A;
      n = A.size();
      st.assign(4*n,-1);
      build(A,0,n-1,1);
    }
    void pointUpdate(int i, int val) {
      pointUpdate(i,val,0,n-1,1);
    }
    int rmq(int i, int j) {
      return rmq(i,j,0,n-1,1);
    }
    void cycle(const vector<int> &args) {
      int save = Arr[args[0]-1];
      for (int i=1;i<args.size();i++){
        pointUpdate(args[i-1]-1,Arr[args[i]-1]);
      }
      pointUpdate(args[args.size()-1]-1,save);
    }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int N,Q;
  scanf("%d%d",&N,&Q);

  vector<int> nums(N);
  for (int n=0;n<N;n++){
    scanf("%d",&nums[n]);
  }
  vector<int> args;

  SegmentTree t1(nums); 
  for (int q=0;q<Q;q++) {
    char action[50];
    args.clear();

    scanf("\n%[^\(](",action);
    int nextArg;
    while (scanf("%d,",&nextArg) != 0) {
      args.push_back(nextArg);
    }
    scanf(")");

    if (strcmp(action,"shift") == 0) {
      t1.cycle(args);
    } else {
      printf("%d\n",t1.rmq(args[0]-1,args[1]-1));
    }
  }

  return 0;
}
