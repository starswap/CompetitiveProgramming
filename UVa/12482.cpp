#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,L,C;
  while(scanf("%d %d %d",&N,&L,&C) != EOF ) {
    
    int characters = 0;
    int lines = 1;
    for (int n=0;n<N;++n) {
      string word; cin >> word;
      int chars = word.size() + (n != N);
      characters += word.size();
      if (characters > C) {
        lines++;
        characters = chars; // or chars
      } else {
        characters++;
      }
    }
    cout << (ceil(static_cast<double>(lines) / static_cast<double>(L))) << endl;  
  }
}
