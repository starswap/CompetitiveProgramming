#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d",&T);
  for (int t=0;t<T;++t) {
    int R,C;
    scanf("%d %d",&R,&C);

    int totalTrees = 0;
    for (int r=0;r<R;++r) {
      string row;
      cin >> row;      
      for (int c=0;c<C;++c) {
        if (row[c] == '^')
          totalTrees += 1;
      }
    }

    
    printf("Case #%d: ",t+1);    
    if (!(R == 1 || C == 1)) { // definitely possible; just fill.
      cout << "Possible" << endl;
      for (int r=0;r<R;++r) {
        for (int c=0;c<C;++c) {
          printf("^");
        }
        printf("\n");
      }
    }
    else {
      if (totalTrees == 0) {
        cout << "Possible" << endl;  
        for (int r=0;r<R;++r) {
          for (int c=0;c<C;++c) {
            printf(".");
          }
          printf("\n");
        }
      }
      else {
        cout << "Impossible" << endl;
      }
    }      
  }
  return 0;
}
