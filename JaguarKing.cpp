#include <bits/stdc++.h>
using namespace std;
vector<int> j;
int N;
inline int dfsA(int lim,int g,int h,int kOld,int kNew,int p);
int dfs(int lim, int g, int h,int k,int p);

template <typename T>
ostream& operator << (ostream& o, vector<T> v) {
  o << "[";
  for (auto a : v) {
    o << a << ",";
  }
  o << "]";
  return o;
}

inline int h1() {
  int h = 0;
  for (int i=0;i<N;i++) {
    if (j[i] != 1) {
      h += abs((j[i]-1)/4-i/4);
      int possible = abs(((j[i]-1)%4 - i%4));
      if (possible == 3)
        possible = 1;
      h += possible;

    }
  }
  return h;
}

inline int dh(int onePos, int otherPos) {
  int possA = abs(((j[otherPos]-1)%4 - otherPos%4));
  int possB = abs(((j[otherPos]-1)%4 - onePos%4));
  if (possA == 3)
    possA = 1;
  if (possB == 3)
    possB = 1;
  return -(abs((j[otherPos]-1)/4-otherPos/4) + possA) + (abs((j[otherPos]-1)/4-onePos/4) + possB);
}


inline int valid(int p) {
  return !(p<0 || p>=N);
}

inline int dfsA(int lim,int g,int h,int kOld,int kNew,int p) {
  if (p == kNew)
    return -1;
  int newH = h+dh(kOld,kNew);
  swap(j[kOld],j[kNew]);
  int r = dfs(lim,g+1,max(0,newH),kNew,kOld);
  if (r == -1)
    swap(j[kOld],j[kNew]);
  return r;
}
int dfs(int lim, int g, int h,int k,int p) {
 // cout << j << h << endl;
  
  if (g+h > lim)
    return -1;
  if (h == 0) {
//    cout << j << endl;
    return g;
  }

  int c;
  switch (k%4) {
    case 0: {
      if (valid(k+1) && ((c = dfsA(lim,g,h,k,k+1,p)) != -1))
        return c;
      if (valid(k+3) && ((c = dfsA(lim,g,h,k,k+3,p)) != -1))
        return c; 
      if (valid(k+4) && ((c = dfsA(lim,g,h,k,k+4,p)) != -1))
        return c; 
      if (valid(k-4) && ((c = dfsA(lim,g,h,k,k-4,p)) != -1))
        return c; 
    } break;
    case 1: {
      if (valid(k+1) && ((c = dfsA(lim,g,h,k,k+1,p)) != -1))
        return c;
      if (valid(k-1) && ((c = dfsA(lim,g,h,k,k-1,p)) != -1))
        return c; 
      if (valid(k+4) && ((c = dfsA(lim,g,h,k,k+4,p)) != -1))
        return c; 
      if (valid(k-4) && ((c = dfsA(lim,g,h,k,k-4,p)) != -1))
        return c; 
    } break;
    case 2: {
      if (valid(k+1) && ((c = dfsA(lim,g,h,k,k+1,p)) != -1))
        return c;
      if (valid(k-1) && ((c = dfsA(lim,g,h,k,k-1,p)) != -1))
        return c; 
      if (valid(k+4) && ((c = dfsA(lim,g,h,k,k+4,p)) != -1))
        return c; 
      if (valid(k-4) && ((c = dfsA(lim,g,h,k,k-4,p)) != -1))
        return c; 
    } break;
    case 3: {
      if (valid(k-3) && ((c = dfsA(lim,g,h,k,k-3,p)) != -1))
        return c;
      if (valid(k-1) && ((c = dfsA(lim,g,h,k,k-1,p)) != -1))
        return c; 
      if (valid(k+4) && ((c = dfsA(lim,g,h,k,k+4,p)) != -1))
        return c; 
      if (valid(k-4) && ((c = dfsA(lim,g,h,k,k-4,p)) != -1))
        return c;
    } break;
  }
  return -1;
}

int IDA_Star(int kingPos) {
  int lim = h1();
  int res = -1;
  while (res == -1) {
 //   cout << lim << endl;
    //cout << h1();
    //cout << kingPos;
    res = dfs(lim,0,h1(),kingPos,-1);
    ++lim;
  }
  return res;
}

int main() {
  cin >> N;
  int m=1;
  while (N != 0) {
    j.assign(N,0);
    int kp;
    for (int n=0;n<N;n++) {
      cin >> j[n];
      if (j[n] == 1)
        kp = n;
    }

  //  cout << h1() << endl; 
    int no = IDA_Star(kp);
    printf("Set %d:\n%d\n",m,no);
    cin >> N;
    ++m;
  }
  return 0;
}
