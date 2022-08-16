//using the recommended method with ordered set to store the groups (use order statistics to easily find the position where a particular worker index would go)
//slightly slower than my custom segment tree algorithm for two possible reasons:
  // A higher constant factor due to either the use of the OST rather than the ST, or the use of additional log operations
  // Initial building in Nlogn rather than n.

//TtoR from checking their solution:
  // cin >> a >> b;
  // can use set::lower_bound instead of OST.
  // can actually do it by erasing and readding, substracting set size as necessary, because each group is only deleted at most once, and there are at most N+M groups that get seen throughout the whole process.  


#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

const long long MOD = 1'000'000'007;
const int N_MAX = 2'000'002;

template <class Ta,class Tb>
inline Tb modProduct(Ta a, Ta b, Tb mod) {
  return ((a % mod)*(b % mod))%mod;
}

template <class T>
using OST = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

pair<int,int> find_group(const OST<pair<int,int>>&groups, int target) {
  return *groups.find_by_order(groups.order_of_key(make_pair(target,N_MAX))-1);
}

void join_group(OST<pair<int,int>> &groups, pair<int,int> group1, pair<int,int> group2) {
  groups.erase(group1);
  groups.erase(group2);
  groups.insert(make_pair(group1.first,group2.second));
}

template <class T,class S>
ostream & operator << (ostream &o, pair<T,S> p) {
  o << "(" << p.first << "," << p.second << ")";
  return o;
}

template <class T>
ostream & operator << (ostream &o, OST<T> ost) {
  for (T i : ost) {
    o << i << " ";
  }
  return o;
}

long long solve(int M, int N) {
  
  long long S_i = static_cast<long long>(N)*static_cast<long long>(N-1)/2;
  long long S_product = 1;

  OST<pair<int,int>> groups;
  for (int i=1;i<=N;++i) {
    groups.insert(make_pair(i,i));
  }
  
  for (int m=0;m<M;++m) {
    long long A,B;
    scanf("%lld %lld",&A,&B);

    if (A == B) continue;
    if (A > B) swap(A,B);

    pair<int,int> Agroup, Bgroup;    
    Agroup = find_group(groups,A);
    Bgroup = find_group(groups,B);
    while (!(Agroup == Bgroup)) {
      pair<int,int> groupToJoin = find_group(groups,Bgroup.first-1);
      join_group(groups,groupToJoin,Bgroup);
      S_i += (static_cast<long long>(groupToJoin.second)-static_cast<long long>(groupToJoin.first)+1)*(static_cast<long long>(Bgroup.second)-static_cast<long long>(Bgroup.first)+1);
      Agroup = find_group(groups,A);
      Bgroup = find_group(groups,B);      
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
