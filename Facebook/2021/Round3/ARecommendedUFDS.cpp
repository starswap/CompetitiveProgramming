//using the recommended method with union-find to store the groups 

#include <bits/stdc++.h>

using namespace std;

const long long MOD = 1'000'000'007;
const int N_MAX = 2'000'002;

template <class Ta,class Tb>
inline Tb modProduct(Ta a, Ta b, Tb mod) {
  return ((a % mod)*(b % mod))%mod;
}

template <class T>
ostream & operator << (ostream &o, vector<T> v) {
  o << "[";
  for (T item : v) {
    o << item << ",";
  }
  o << "]";
  return o;
}

class UFDS {
  private:
    vector<int> p;
    vector<int> rank;
    vector<int> minValue;
    vector<int> setSize;

  public:
    UFDS(int n) { //n sets of one element.
      p.assign(n,0);
      minValue.assign(n,0);
      rank.assign(n,0);
      for (int i=0;i<n;++i)
        p[i] = minValue[i] = i;
      setSize.assign(n,1);
    }
    int findSet(int i) {
      if (i == p[i]) return i;
      return p[i] = findSet(p[i]);
    }
    bool isSameSet(int i, int j) {
      return (findSet(i) == findSet(j));
    }
    void unionSet(int i, int j) {
      i = findSet(i);
      j = findSet(j);
      if (rank[i] > rank[j]) swap(i,j);
      //rank[i] <= rank[j]
      p[i] = j;
      ++rank[j];
      setSize[j] += setSize[i];
      minValue[j] = min(minValue[j],minValue[i]);
    } 
    int getSetSize(int i) {
      return setSize[findSet(i)];
    }
    int getMinValue(int i) {
      return minValue[findSet(i)];
    }

    friend ostream& operator << (ostream& o, UFDS u) {
      o << "UFDS with:" << endl;
      vector<vector<int>> v(u.p.size());
      for (int i=0;i<u.p.size();++i) {
        v[u.findSet(i)].push_back(i);
      }
      int setNo = 0;
      for (vector<int> vec : v) {
        if (vec.size() > 0) {
          o << "Set No " << setNo << ": " << vec << endl;
          setNo++;
        }
      }
      return o;
    }

};


long long solve(int M, int N) {
  
  long long S_i = static_cast<long long>(N)*static_cast<long long>(N-1)/2;
  long long S_product = 1;

  UFDS groups(N);
  
  for (int m=0;m<M;++m) {
    long long A,B;
    scanf("%lld %lld",&A,&B);
    A--; B--;
    
    if (A == B) continue;
    if (A > B) swap(A,B);

    while (groups.findSet(A) != groups.findSet(B)) {
      //cout << groups << endl; 
      S_i += static_cast<long long>(groups.getSetSize(groups.getMinValue(B)-1))*static_cast<long long>(groups.getSetSize(B));
      groups.unionSet(groups.getMinValue(B)-1,B);
    } 
    
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

