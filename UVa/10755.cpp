#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; scanf("%d",&T);
  while (T--) {
    int A,B,C; scanf("%d %d %d",&A,&B,&C);
    long long garbageValue[20][20][20];
    long long partial[20][20][20];
    long long maxVal = -1e17; 
    for (int a=0;a<A;++a) {
      for (int b=0;b<B;++b) {
        for (int c=0;c<C;++c) {
          cin >> garbageValue[a][b][c];
          maxVal = max(maxVal,garbageValue[a][b][c]);
        }
      }
    }

    for (int c=0;c<C;++c) {
      for (int a=0;a<A;++a) {
        for (int b=0;b<B;++b) {
          if (a == 0 && b == 0)
            partial[a][b][c] = garbageValue[a][b][c];
          else if (a == 0)
            partial[a][b][c] = partial[a][b-1][c] + garbageValue[a][b][c];
          else if (b == 0)
            partial[a][b][c] = partial[a-1][b][c] + garbageValue[a][b][c];
          else
            partial[a][b][c] = partial[a-1][b][c] + partial[a][b-1][c] - partial[a-1][b-1][c] + garbageValue[a][b][c];
        }
      }
    }
    
    long long bestOverall;
  
    if (maxVal <= 0)
      bestOverall = maxVal;
    else {
      bestOverall = -1e17;
      for (int spaces1=0;spaces1<A*B;++spaces1) { //this iteration could be done more clearly by iterating a1 and then a2 from a1, and iterating b1 and then b2 from b1.
         for (int spaces2=spaces1;spaces2<(A*B);++spaces2) {
           int a1 = spaces1%A;
           int b1 = spaces1/A;
           int a2 = spaces2%A;
           int b2 = spaces2/A;

           if (a2 < a1) continue;

           
        //   printf("a1:%d,b1:%d,, a2:%d,b2:%d\n",a1,b1,a2,b2);
           long long bestContinue = 0; 
           for (int c=0;c<C;++c) {
             long long thisLayer = 0;
             if (a1 == 0 && b1 == 0)
               thisLayer = partial[a2][b2][c];
             else if (a1 == 0)
               thisLayer = partial[a2][b2][c] - partial[a2][b1-1][c];
             else if (b1 == 0)
               thisLayer = partial[a2][b2][c] - partial[a1-1][b2][c];
             else
               thisLayer = partial[a2][b2][c] - partial[a1-1][b2][c] - partial[a2][b1-1][c] + partial[a1-1][b1-1][c];
  
             bestContinue += thisLayer;
             if (bestContinue < 0)
               bestContinue = 0;
             else
               bestOverall = max(bestContinue,bestOverall);
           }
         } 
      }
    }
    cout << bestOverall << endl;
    if (T != 0)
      cout << endl;
  }
}