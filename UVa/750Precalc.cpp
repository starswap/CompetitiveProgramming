
#include <bits/stdc++.h>
using namespace std;

int solNo;
vector<int> row(9,0);
vector<vector<int>> nQueens; 

bool canPlace(int r,int c) {
  for (int previousQueen=1;previousQueen<c;previousQueen++) {
    if (row[previousQueen] == r) return false; //same row
    if (r + c == row[previousQueen] + previousQueen) return false; //same upward sloping diagonal
    if (abs(r-row[previousQueen]) == abs(c-previousQueen)) return false; //same downward sloping diagonal
  }
  return true;
}

void backtrack(int c) {
  if (c == 9) {
    nQueens.push_back(row);
  }
  else {
    for (int r=1;r<=8;++r) {
      if (canPlace(r,c)) {
        row[c] = r;
        backtrack(c+1);
      }
    }
    
  }
  
}

template <class T>
ostream &operator << (ostream& o,vector<T> v) {
  o << '[';
  for (int i=0;i<v.size();++i) {
    o << v[i];
    if (i != v.size()-1)
      o << ',';
  }
  o << ']';
  return o;
}

int main() {
  solNo = 1;
  backtrack(1);

  cout << nQueens << endl;
  return 0;
}