#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) ((S) & -(S))                    // the key operation

typedef long long ll;                            // for extra flexibility
typedef vector<ll> vll;
typedef vector<int> vi;

class FenwickTree {    // (Steven Halim, Felix Halim, Suhendry Effendy)                           // index 0 is not used
private:
  vll ft;                                        // internal FT is an array
public:
  FenwickTree(int m) { ft.assign(m+1, 0); }      // create an empty FT

  void build(const vll &f) {
    int m = (int)f.size()-1;                     // note f[0] is always 0
    ft.assign(m+1, 0);
    for (int i = 1; i <= m; ++i) {               // O(m)
      ft[i] += f[i];                             // add this value
      if (i+LSOne(i) <= m)                       // i has parent
        ft[i+LSOne(i)] += ft[i];                 // add to that parent
    }
  }

  FenwickTree(const vll &f) { build(f); }        // create FT based on f

  FenwickTree(int m, const vi &s) {              // create FT based on s
    vll f(m+1, 0);
    for (int i = 0; i < (int)s.size(); ++i)      // do the conversion first
      ++f[s[i]];                                 // in O(n)
    build(f);                                    // in O(m)
  }

  ll rsq(int j) {                                // returns RSQ(1, j)
    ll sum = 0;
    for (; j; j -= LSOne(j))
      sum += ft[j];
    return sum;
  }

  ll rsq(int i, int j) { return rsq(j) - rsq(i-1); } // inc/exclusion

  // updates value of the i-th element by v (v can be +ve/inc or -ve/dec)
  void update(int i, ll v) {
    for (; i < (int)ft.size(); i += LSOne(i))
      ft[i] += v;
  }

  int select(ll k) {                             // O(log m)
    int p = 1;
    while (p*2 < (int)ft.size()) p *= 2;
    int i = 0;
    while (p) {
      if (k > ft[i+p]) {
        k -= ft[i+p];
        i += p;
      }
      p /= 2;
    }
    return i+1;
  }
};


int main() {
    int T;
    scanf("%d",&T);

    for (int t=0;t<T;++t) {
        int N,M;
        scanf("%d %d",&N,&M);
        
        vector<ll> twos;

        for (int n=0;n<N;++n) {
            int digit;
            scanf("%d",&digit);
            twos.push_back(digit-1);
        }

        FenwickTree ft(N);
        ft.build(twos);

        for (int m=0;m<M;++m) {
            int X,Y,Z;
            scanf("%d %d %d",&X,&Y,&Z);


            if (Y == 1 && twos[X-1] == 2) {
                ft.update(X,-1);
                twos[X-1] = 1;
            }
            else if (Y == 2 && twos[X-1] == 1) {
                ft.update(X,1);
                twos[X-1] = 2;
            }

            int numTwosInFirstZ = ft.rsq(1,Z);
            int numTwosAfter = ft.rsq(Z+1,N);
            


        }


        printf("Case #%d: %d",t+1,ans);
    }
    return 0;
}