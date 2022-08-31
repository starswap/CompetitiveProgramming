//Takes around 30 seconds on the official practice input.

//Compile with C++20;
//I have been unable to submit this, but I think it works as it has been tested. 

//Using sqrt(N) small/big sets in a slightly different way to the suggested way:

//My way:
  
  // For each edge A-B: -> Does all *L* 
    // Deal with direct
    // If B light, consider all edges BC for the indirect path ABC
    // If A light, consider all edges AC for the indirect path BAC

  // For each query A,B -> Does all *H*
    // For each heavy node C
      // deal with indirect A-C-B

// Official way:
  // For each heavy node: -> Deals with all H-*
    // Take all possible two-steps from that node and save scores for where you end up
    // (This is O(root n) heavy nodes * O(M) edges which can each be used at most once per big node - can see this since each edge out of big node is traversed once then we traverse all edges out of the next node - i.e. it's a capped DFS, O(V+E))

  // For each query A-B of the form L-L
    // Loop through all C in neighbours(A) and neighbours(B) to deal with indirect A-C-B
    // -> Will have to do this with a map which we populate with costs from A, and then overwrite with the minimum of that and the cost from B.


#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

int T,N,M,Q;
const int THRESHOLD = 660; // sqrt(400K). Define a vertex to be "Heavy" if it has more than this many neighbours. 
const long long MAX = 200'001;

vector<pair<int,int>> EL;
vector<vector<int>> AL;
vector<pair<int,int>> Queries;

unordered_map<int,unordered_map<int,long long>> AM; 
unordered_map<long long,long long> queryCosts;
unordered_set<int> heavy;

long long hash_pair(pair<int,int> p) {
  long long f = static_cast<long long>(p.first);
  long long s = static_cast<long long>(p.second);
  return MAX*f + s;
}

pair<int,int> unhash_pair(long long p) {
  long long f = p/MAX;
  long long s = p%MAX;
  return make_pair(static_cast<int>(f),static_cast<int>(s));
}

void getInput() {
  scanf("%d %d %d",&N,&M,&Q);
  AL.assign(N,vector<int>());
  //AM.assign(N,vector<long long>(N,0));
  
  for (int m=0;m<M;++m) {
    int A,B; 
    long long C;
    scanf("%d %d %lld",&A,&B,&C);
    A--; B--;
    EL.emplace_back(A,B);
    AL[A].push_back(B);
    AL[B].push_back(A);
    AM[A][B] = C;
    AM[B][A] = C;
  }

  Queries.assign(Q,make_pair(0,0));
  for (int q=0;q<Q;++q) {
    int X,Y;
    scanf("%d %d",&X,&Y);
    X--;Y--;
    if (X > Y) swap(X,Y); //X <= Y now. 
    Queries[q] = make_pair(X,Y);
    queryCosts[hash_pair(make_pair(X,Y))] = 0;
  }
}

void reset() {
  EL.clear();
  AL.clear();
  AM.clear();
  heavy.clear();
  queryCosts.clear();
  Queries.clear();
}

void findHeavy() {
  for (int i=0;i<N;++i) {
    if (AL[i].size() >= THRESHOLD)
      heavy.insert(i);
  }
}

void updateEdge(int A, int B, long long cost) {
  if (A > B) swap(A,B);
  if (queryCosts.find(hash_pair(make_pair(A,B))) != queryCosts.end())
      queryCosts[hash_pair(make_pair(A,B))] += cost;
}

void updateEdge(int A, int B, pair<int,int> one, pair<int,int> two) {
  if (A > B) swap(A,B);
  if (queryCosts.find(hash_pair(make_pair(A,B))) != queryCosts.end()) {
    
    if (AM.contains(one.first) && AM[one.first].contains(one.second)
        && AM.contains(two.first) && AM[two.first].contains(two.second)) {
      
        queryCosts[hash_pair(make_pair(A,B))] += min(AM[one.first][one.second],AM[two.first][two.second]);
    }
  }
}


void dealWithLight() {
  //Calcualte all direct A-B and all *-Light-*
  for (auto [A,B] : EL) {
    updateEdge(A,B,4*AM[A][B]); //twice what we need; will divide

    if (heavy.find(A) == heavy.end()) //A is light set node
      for (int C : AL[A])
        updateEdge(B,C,make_pair(A,B),make_pair(A,C));     
    
    if (heavy.find(B) == heavy.end()) //B is light set node
      for (int C : AL[B])
        updateEdge(A,C,make_pair(A,B),make_pair(B,C));


  }
  
  for (auto key_value : queryCosts) {
      queryCosts[key_value.first] /= 2; // double counting.
  }
  
}

void dealWithHeavy() {
  //Calculate for all *-Heavy-*
  for (auto key_value : queryCosts) {
    auto [A,B] = unhash_pair(key_value.first);
    for (int C : heavy)
      updateEdge(A,B,make_pair(A,C),make_pair(B,C)); // FIX
  }
}

vector<long long> solve() {
  findHeavy();
  dealWithLight();
  dealWithHeavy();
  
  vector<long long> Fs;
  for (auto [A,B] : Queries) {
    Fs.push_back(queryCosts[hash_pair(make_pair(A,B))]);
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
