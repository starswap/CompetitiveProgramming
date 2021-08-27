#include <bits/stdc++.h>
using namespace std;

void DFS(vector<vector<int>> &AL,vector<bool> &visited,int v) {
  if (visited[v]) {return;}
  else {
    visited[v] = true;
    for (int u : AL[v])
      DFS(AL,visited,u);
  }
}

bool checkEulerian(vector<vector<int>> &AL) {
  for (vector<int> vs : AL) {
    if (vs.size() % 2 == 1)
      return false; //odd degree
  }


  vector<bool> visited(AL.size(),false);
  int start;
  for (start=0;AL[start].size() == 0;start++) {}
  DFS(AL,visited,start);
  for (int i=0;i<visited.size();i++) {
    if (!visited[i] && AL[i].size() > 0){
      return false;
    }
  }
  return true;
}

vector<int> findEulerianTour(vector<vector<int>> &AL,int start) {
  vector<int> stack,result,amountOfUsedConns(AL.size(),0);
  stack.push_back(start);
  multiset<pair<int,int>> usedEdges;
  while (!stack.empty()){
    int top = *stack.rbegin();

    //In case we previously used the next edge in the reverse direction
    while (amountOfUsedConns[top] < AL[top].size() && usedEdges.count(pair<int,int>(AL[top][amountOfUsedConns[top]],top)) > 0) {
      usedEdges.erase(usedEdges.find(pair<int,int>(AL[top][amountOfUsedConns[top]],top))); //we've seen the back-edge.  
      amountOfUsedConns[top]++;
    }

    if (amountOfUsedConns[top] >= AL[top].size()) {
      stack.pop_back();
      result.push_back(top);
    } else {
      stack.push_back(AL[top][amountOfUsedConns[top]]); //remember indexing
      if (top != AL[top][amountOfUsedConns[top]])
        usedEdges.insert(pair<int,int>(top,AL[top][amountOfUsedConns[top]]));
      else
        ++amountOfUsedConns[top]; //will be there twice so need to double up - self loop
      ++amountOfUsedConns[top];
    }
  }
  //may need to reverse;
  return result;
}



int main() {
  int T;
  cin >> T;
  for (int t=0;t<T;t++) {
    cout << "Case #" << t+1 << "\n";
    int N;
    cin >> N;
    vector<vector<int>> AL(51,vector<int>(0));
    for (int n=0;n<N;n++) {
      int c1, c2;
      cin >> c1;
      cin >> c2;
      AL[c1].push_back(c2);
      AL[c2].push_back(c1);
    }

    
    if (checkEulerian(AL) == false)
      cout << "some beads may be lost" << '\n';
    else {
      int start;
      for (start=0;AL[start].size() == 0;start++) {}
      vector<int> necklace = findEulerianTour(AL,start);

      cout << necklace[0] << " ";
      for (int i=1;i<necklace.size()-1;i++) 
        cout << necklace[i] << "\n" << necklace[i] << " ";
      cout << necklace[0] << '\n';
    }

    if (t!= T-1)
      cout << '\n';
  }
  return 0;
}
