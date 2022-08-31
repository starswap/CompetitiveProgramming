//Takes around 13 seconds on the official practice input.

//Use std=c++20
//Using alternate recommended method 2 in the editorial.

#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

int T,N,M,Q;
const long long MAX = 200'001;

unordered_map<int,unordered_map<int,long long>> AM; 
unordered_map<long long,long long> queryCostsMemo;
vector<pair<int,int>> Queries;
vector<int> degree;

long long hash_pair(pair<int,int> p) {
  long long f = static_cast<long long>(p.first);
  long long s = static_cast<long long>(p.second);
  return MAX*f + s;
}


void getInput() {
  scanf("%d %d %d",&N,&M,&Q);

  degree.assign(N,0);

  for (int m=0;m<M;++m) {
    int A,B; 
    long long C;
    scanf("%d %d %lld",&A,&B,&C);
    A--; B--;
    AM[A][B] = C;
    AM[B][A] = C;
    degree[A]++;
    degree[B]++;
  }

  Queries.assign(Q,make_pair(0,0));
  
  for (int q=0;q<Q;++q) {
    int X,Y;
    scanf("%d %d",&X,&Y);
    X--;Y--;
    if (degree[X] > degree[Y]) swap(X,Y); //degree[X] <= degree[Y] now.
    Queries[q] = make_pair(X,Y);
  }
}

void reset() {
  degree.clear();
  AM.clear();
  queryCostsMemo.clear();
  Queries.clear();
}

long long processQuery(int A, int B) {
  if (queryCostsMemo.contains(hash_pair(make_pair(A,B)))) 
    return queryCostsMemo[hash_pair(make_pair(A,B))];

  long long cap = 0;
  if (AM[A].contains(B))
    cap += AM[A][B]*2;
  
  for (auto [C,edge_cost] : AM[A]) {
    if (AM[B].contains(C))
      cap += min(AM[A][C],AM[B][C]);
  }
  
  queryCostsMemo[hash_pair(make_pair(A,B))] = cap;
  return cap;
}

vector<long long> solve() {
  
  vector<long long> Fs;
  for (auto [A,B] : Queries) {
    Fs.push_back(processQuery(A,B));
  }
  return Fs;
}

int main() {
  scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    reset();
    getInput();

    vector<long long> Fs = solve();
    printf("Case #%d: ",t);
    for (int i=0;i<Q-1;++i) {
      printf("%lld ",Fs[i]);
    }
    printf("%lld",*Fs.rbegin());
    cout << endl; //flush stream to see progress.
    
  }
  return 0;
}
