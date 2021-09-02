#include <bits/stdc++.h>
using namespace std;

vector<long> H;
vector<long> C;
vector<long> L;
long ind;
void dfs(vector<vector<pair<long,long>>> &AL,long u,long depth) {
  H[u] = ind;
  ind++;
  for (auto &[v,w] : AL[u]) {
    C[ind] = w;
    L[ind] = depth+1;
    dfs(AL,v,depth+1);
    C[ind] = -w;
    L[ind] = depth; 
    ind++;
  }
}

class MinTree {
  public:
    MinTree(vector<long> &B) {
      A = B;
      n = B.size();
      st.assign(4*n,-1);
      build(0,n-1,1);
    }
    long rmq(long i,long j) {
      return rmq(i,j,0,n-1,1);
    } 
  private:
    vector<long> st;
    vector<long> A;
    long n;
    inline long l(long a) {return a<<1;}
    inline long r(long a) {return (a<<1)+1;}
    void build(long L, long R, long p) {
      if (L==R) {st[p] = L;}
      else {
        long m = (L+R)/2;
        build(L,m,l(p));
        build(m+1,R,r(p));
        if (A[st[l(p)]] < A[st[r(p)]])
          st[p] = st[l(p)];
        else
          st[p] = st[r(p)];
      }
    }

    long rmq(long i,long j,long L,long R,long p) { //returns index of min value
      if (L>= i && R <= j) {return st[p];}
      else {
        long m = (L+R)/2;
        if (j <= m)
          return rmq(i,j,L,m,l(p));
        else if(i >= m+1)
          return rmq(i,j,m+1,R,r(p));
        else {
          long a = rmq(i,m,L,m,l(p));
          long b = rmq(m+1,j,m+1,R,r(p));
          if (A[a] < A[b])
            return a;
          else
            return b;
        }
      }
    }
};

class SumTree {
  public:
    SumTree(vector<long> &A) {
      n = A.size();
      st.assign(4*n,-1);
      build(A,0,n-1,1);
    }
    long rsq(long i,long j) {
      return rsq(i,j,0,n-1,1);
    } 
  private:
    vector<long> st;
    long n;
    inline long l(long a) {return a<<1;}
    inline long r(long a) {return (a<<1)+1;}
    void build(vector<long> &A,long L, long R, long p) {
      if (L==R) {st[p] = A[L];}
      else {
        long m = (L+R)/2;
        build(A,L,m,l(p));
        build(A,m+1,R,r(p));
        st[p] = st[l(p)] + st[r(p)];
      }
    }

    long rsq(long i,long j,long L,long R,long p) { 
      if (i>j) {return 0;}
      if (L>= i && R <= j) {return st[p];} 
      else {
        long m = (L+R)/2;
        if (j <= m)
          return rsq(i,j,L,m,l(p));
        else if(i >= m+1)
          return rsq(i,j,m+1,R,r(p));
        else
          return rsq(i,m,L,m,l(p)) + rsq(m+1,j,m+1,R,r(p));
      }
    }
};




int main() { 
  long N;
  cin >> N;
  while (N != 0) {
    vector<vector<pair<long,long>>> AL(N,vector<pair<long,long>>());
    for (long n=0;n<N-1;n++) {
      long a; long b; cin >> a; cin >> b;
      AL[a].push_back(make_pair(n+1,b));
    }

    C.assign(2*N,-1);
    L.assign(2*N,-1);
    H.assign(N,-1);
    ind = 0;
    dfs(AL,0,0);


    SumTree st(C);
    MinTree mt(L);
    long Q; cin >> Q;
    for (long q=0;q<Q;q++) {
      long S,T;
      cin >> S;
      cin >> T;
      long start = H[S];
      long end = H[T];
      if (start > end) {swap(start,end);}
      long LCA = mt.rmq(start,end);
      cout << abs(st.rsq(start+1,LCA)) + abs(st.rsq(LCA+1,end));
      if (q != Q-1)
        cout << " ";
      else
        cout << "\n";
    }
    cin >> N;
  }
  return 0;
}
