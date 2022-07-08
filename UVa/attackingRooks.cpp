#include <bits/stdc++.h>
using namespace std;

int augPath(unordered_map<string,vector<string>> &AL,unordered_set<string> &visited,unordered_map<string,string> &matches, string L) {
  if (visited.count(L) == 1) return 0;
  visited.insert(L);
  for (auto R : AL[L]) {
    if (matches.count(R) == 0 || augPath(AL,visited,matches,matches[R])) {
      matches[R] = L;
      return 1;
    }
  }
  return 0;
}

int MCBM(unordered_map<string,vector<string>> &AL,vector<string> leftSet) {
  unordered_map<string,string> matches;
  unordered_set<string> visited;
  int totalMatches = 0;
  for (auto L : leftSet) {
    totalMatches += augPath(AL,visited,matches,L);
    visited.clear();
  }
  return totalMatches;
} 

int main() {
  int N;
  while (cin >> N) {
    vector<string> board;

    for (int i=0;i<N;i++) {
      string line;
      cin >> line;
      board.push_back(line);
    }

    unordered_map<string,vector<string>> AL;
    vector<int> onColumnGroup(N,65);
    vector<string> rows;
    for (int i=0;i<N;i++) {
      int onRowGroup = 65;
      for (int j =0;j<N;j++) {
        if (board[i][j] == 'X'){
          onRowGroup++;
          onColumnGroup[j]++;
        } else {
          string colCombined = "C";
          colCombined.push_back(j+65);
          colCombined.push_back(onColumnGroup[j]);
          string rowCombined = "R";
          rowCombined.push_back(i+65);
          rowCombined.push_back(onRowGroup);
          if (AL.count(colCombined) == 0)
            AL[colCombined] = vector<string>(1,rowCombined);
          else
            AL[colCombined].push_back(rowCombined);
          
          if (AL.count(rowCombined) == 0) {
            rows.push_back(rowCombined);
            AL[rowCombined] = vector<string>(1,colCombined);
          }
          else
            AL[rowCombined].push_back(colCombined);
        }
      }
    }

    cout << MCBM(AL,rows) << endl;

  }
}
