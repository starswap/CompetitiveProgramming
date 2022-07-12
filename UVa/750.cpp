
#include <bits/stdc++.h>
using namespace std;

int solNo;
int row[9];

bool canPlace(int r,int c) {
  for (int previousQueen=1;previousQueen<c;previousQueen++) {
    if (row[previousQueen] == r) return false; //same row
    if (r + c == row[previousQueen] + previousQueen) return false; //same upward sloping diagonal
    if (abs(r-row[previousQueen]) == abs(c-previousQueen)) return false; //same downward sloping diagonal
  }
  return true;
}

void backtrack(const int &targetR, const int &targetC, int c) {
  if (c == 9) {
    if (solNo < 10) {
      printf(" ");
    }
    printf("%d      %d %d %d %d %d %d %d %d\n",solNo,row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
    solNo++;
  }
  else {
    for (int r=1;r<=8;++r) {
      if (c == targetC && r != targetR) continue;
      if (canPlace(r,c)) {
        row[c] = r;
        backtrack(targetR,targetC,c+1);
      }
    }
    
  }
  
}



int main() {
  int T; cin >> T;
  int targetR, targetC;
  bool first = true;
  while (scanf("%d %d",&targetR,&targetC) != EOF) {
    if (!first) {
      cout << endl;
    } else {
      first = false;
    }
    cout << "SOLN       COLUMN" << endl;
    cout << " #      1 2 3 4 5 6 7 8\n" << endl;
    solNo = 1;
    backtrack(targetR,targetC,1);
    
  }
  return 0;
}