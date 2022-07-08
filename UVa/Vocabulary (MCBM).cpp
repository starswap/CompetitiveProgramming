#include <bits/stdc++.h>
using namespace std;

bool isMatch(unordered_map<char,int> &word1, unordered_map<char,int>& word2) {
  for (auto [chr,reqAmt] : word2) {
    if (word1.count(chr) == 0 || word1[chr] < reqAmt) //Jill wins
      return false;
  }
  return true;
}


int AugPath(int L,vector<vector<int>>& AL,vector<int>& matches,vector<int>& visited) {
  if (visited[L]) return 0;
  visited[L] = 1;
  for (auto &R : AL[L]) {
    if (matches[R] == -1 || AugPath(matches[R],AL,matches,visited)) {
      matches[R] = L;
      return 1;      
    }
  }
  return 0;
}

int MCBM(vector<vector<int>> AL,int Vtot,int VLeft) {
  int totalMatches = 0;
  vector<int> matches(Vtot,-1);
  vector<int> visited;

  for (int L=0;L<VLeft;L++) {
    visited.assign(VLeft,0); 
    totalMatches += AugPath(L,AL,matches,visited);
  }

  return totalMatches;
}

int main() {
  int Jack,Jill;
  while ( cin >> Jack ) {
    cin >> Jill;
    vector<unordered_map<char,int>>JackVocab(Jack);
    vector<unordered_map<char,int>>JillChalls(Jill);

    for (int i=0;i<Jack;i++) {
      string word;
      cin >> word;
      for (auto c : word) {
        if (JackVocab[i].count(c) == 0)
          JackVocab[i].insert(pair<char,int>(c,1));
        else
          JackVocab[i][c] += 1;
      }
    }
    for (int i=0;i<Jill;i++) {
      string word;
      cin >> word;
      for (auto c : word) {
        if (JillChalls[i].count(c) == 0)
          JillChalls[i].insert(pair<char,int>(c,1));
        else
          JillChalls[i][c] += 1;
      }
    }

    vector<vector<int>> AL(Jack+Jill,vector<int>(0));
    int i = 0,j;
    for (auto w : JackVocab) {
      j = Jack;
      for (auto w2 : JillChalls) {
        if (isMatch(w,w2)) {
          AL[i].push_back(j);
          AL[j].push_back(i);
        }
        j++;
      }
      i++;
    }
    cout << MCBM(AL,Jill+Jack,Jack) << endl;
  }
}
