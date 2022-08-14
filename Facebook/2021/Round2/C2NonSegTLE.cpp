//Not using segment tree; for debugging purposes; otherwise same as C2. 

#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace __gnu_pbds;
using namespace std;

// Order Statistics Tree
typedef tree<int, null_type, less<int>, rb_tree_tag,
             tree_order_statistics_node_update>
    OST;

int main() {
  int T; scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int R,C,K,S; scanf("%d %d %d %d",&R,&C,&K,&S); K--;
    vector<vector<bool>> garage(R,vector<bool>(C));   //Is there a car here?
    vector<int> spacesAbove(C,0);
    vector<int> spacesBelow(C,0);
    
    for (int r=0;r<R;++r) {
      string str;
      cin >> str;
      for (int c=0;c<C;++c) {
        garage[r][c] = (str[c] == 'X');
        if (r < K) {
          spacesAbove[c] += (str[c] == '.');
        }
        if (r > K) {
          spacesBelow[c] += (str[c] == '.');
        }        
      }
    }

    vector<pair<int,int>> spells;
    for (int s=0;s<S;++s) {
      int r,c;
      scanf("%d %d",&r,&c);
      r--; c--;
      spells.emplace_back(r,c);
    }
    
    vector<bool> rowK = garage[K];
    int total = 0;
    vector<int> shiftCosts(R+2); // Will become a segment tree.
    vector<OST> cars(C);

    //Downward shifts    
    for (int shift=1;shift<=K+1;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesBelow[c] > 0 || rowK[c] == false) { //Can we push into this space?
          //...Only if no gridlock or gridlock below and this space is empty.
          
          if (rowK[c]) --spacesBelow[c]; //pushed down a car
          if (K-shift < 0) 
            rowK[c] = 0;
          else
            rowK[c] = garage[K-shift][c];
        }
        total += rowK[c];
        
        if (K-shift >= 0 && garage[K-shift][c]) {
          cars[c].insert(K+1-shift);
        }
        
      }
      shiftCosts[K+1-shift] = shift+total;
    }

    rowK = garage[K];
    total = 0;
    //No shifts, total Xs.
    for (int c=0;c<C;++c) {
      total += rowK[c];
      if (garage[K][c]) {
        cars[c].insert(K+1);
      }
    }    
    shiftCosts[K+1] = (total);
    
    //For all upward shifts:
    rowK = garage[K];
    for (int shift=1;shift<=R-K;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesAbove[c] != 0 || rowK[c] == false) { //Can we push into this space? (NOTE: TCs a little weak; don't require rowK[c] == false here.)
          //...  Only if no gridlock or gridlock above and this space is empty. 
          
          if (rowK[c]) --spacesAbove[c]; //pushed up a car so one fewer empty space. 
          if (K+shift >= R) //Create new empty spaces from the bottom
            rowK[c] = 0;
          else
            rowK[c] = garage[K+shift][c];
        }
        total += rowK[c]; //Total number of one car at a time moves needed.
        if (K+shift < R && garage[K+shift][c]) {
          cars[c].insert(K+1+shift);
        }
      }
      shiftCosts[K+1+shift] = (shift+total);
    }

    int M_sum = 0;
    int prevGridlock, currGridlock, prevGridlock2, currGridlock2;
    
    for (auto [r,c] : spells) {
      int shift = r+1;
      
      if (garage[r][c] == true) { //Wong is removing a car
        
        if (cars[c].find_by_order(K) != cars[c].end()) { //gridlock occurs one later now than it did before
          prevGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...
        }
        else {
          prevGridlock = shiftCosts.size();
        }
        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //doesn't occur now.
          prevGridlock2 = -1;
        }
        else {
          prevGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K));
        }


        if (shift <= prevGridlock && shift >= prevGridlock2)
          shiftCosts[shift] -= 1;
        
        cars[c].erase(shift);
        if (cars[c].find_by_order(K) == cars[c].end()) { //doesn't occur now.
          currGridlock = shiftCosts.size();
        }
        else {currGridlock = *cars[c].find_by_order(K);}

        //otherwise would have been gridlocked already just groikvkj it.
        //still has a car so don't change it.
        for (int g=prevGridlock+1;g<currGridlock;++g) {
            shiftCosts[g] -= 1;
        }
        
        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //doesn't occur now.
          currGridlock2 = -1;
        }
        else {currGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K));}

        for (int g=currGridlock2+1;g<prevGridlock2;++g) { //still has a car so don't change it.
          if (!(prevGridlock <= g && g < currGridlock))     //provided we haven't already dealt with it.      
            shiftCosts[g] -= 1;
        }
        
      }
      else { //Wong is adding a car
        if (cars[c].find_by_order(K) == cars[c].end()) { //gridlock occurs one earlier now than it did before
          prevGridlock = shiftCosts.size();
        }
        else
          prevGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...

        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //gridlock occurs one later now than it did before
          prevGridlock2 = -1;
        }
        else
          prevGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K)); //shift at which gridlock currently occurs or end...
      
        
        cars[c].insert(shift);
        
        if (cars[c].find_by_order(K) == cars[c].end()) { //gridlock occurs one later now than it did before
          currGridlock = shiftCosts.size();
        }
        else
          currGridlock = *cars[c].find_by_order(K); //shift at which gridlock currently occurs or end...



        if (cars[c].find_by_order(cars[c].size()-(R-K)) == cars[c].end()) { //gridlock occurs one later now than it did before
          currGridlock2 = -1;
        }
        else
          currGridlock2 = *cars[c].find_by_order(cars[c].size()-(R-K)); //shift at which gridlock currently occurs or end...

        if (shift <= currGridlock && shift >= currGridlock2)
          shiftCosts[shift] += 1;

        for (int g=currGridlock+1;g<prevGridlock;++g) {
       //   if (!(g <= prevGridlock2 currGridlock <= g && g < prevGridlock))          
            shiftCosts[g] += 1;
        }
        
        for (int g=prevGridlock2+1;g<currGridlock2;++g) {
          if (!(currGridlock <= g && g < prevGridlock))
            shiftCosts[g] += 1;
        }
      
      }
      garage[r][c] = !garage[r][c];

      int minn = *min_element(shiftCosts.begin(),shiftCosts.end());
      printf("%d\n",minn);
      M_sum += minn; 
      
    }
    
    printf("Case #%d: %d\n",t,M_sum);
  }
  
  return 0;
}
