//NOT DONE Yet.

//O(RC)

//A removal of a single car can only affect one square and thus can only give you a maximum benefit of one square in the end.
//Therefore it is never more beneficial to remove a car then shift the empty square into the current row than to shift the rows first and then remove the car.
//This means that we can do all of the shifting first and then the removal of individual cars.
//It can also be seen that there is nobenefit to shifting down and then up or vice versa. While this isn't the same as doing nothing, it cannot have better result than just an up shift for example.
//As a result, we remove the need for branching from the solution because we can try all up shifts first, then subsequently individual removals. Then we try all down shifts and all subsequent individual removals.
//The brute force solution would be at least O(3^C) as you have to try up to C moves to clear the row, and there are 3 moves per possibility. This is ridiculously large with R = 2M.
//This way means that we only have to try O(C) moves.
//However we still need to ensure that we can perform each move in O(C) or O(R) or better to avoid TLE. This is trivial for the remove one car moves, but for the shift moves we need a mechanism which doesn't involve actually performing the shifts. We can do this by keeping track of the number of free spaces above and below the current row, and using this to see if gridlock has occurred:
    //Find amount of free spaces above row K in each column
    //Each time you push an X up the number of free spaces above reduces. 
    //IF the number of free spaces above is 0 we are in gridlock; no further changes
    //If the number of free spaces above is more than 0, then we get whatever is in the row (K+shift) which is located below, since gridlock is the only thing which prevents this, i.e. without gridlock everything would effectively shift.
    //Repeat for downward shifts.
    

#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; scanf("%d",&T);
  for (int t=1;t<=T;++t) {
    int R,C,K,S; scanf("%d %d %d %d",&R,&C,&K,&S); K--;
    vector<vector<bool>> garage(R,vector<bool>(C));   //Is there a car here?
    vector<int> spacesAbove(C,0);
    vector<int> spacesBelow(C,0);
    vector<int> shifts;

    vector<vector<int>> freeAboveBecomes(C,vector<int>(R,-1));
    vector<vector<int>> freeBelowBecomes(C,vector<int>(R,-1));
    
    
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
    for (int c=0;c<C;++c) {
      freeBelowBecomes[c][spacesBelow] = 0;
      freeAboveBecomes[c][spacesBelow] = 0; 
    }


    vector<pair<int,int>> spells;
    for (int s=0;s<S;++s) {
      int r,c;
      scanf("%d %d",&r,&c);
      spells.emplace_back(r,c);
    }
    

    vector<bool> rowK = garage[K];
    int best,total = 0;

    //For all downward shifts:
     for (int shift=1;shift<=K+1;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesBelow[c] > 0 || rowK[c] == false) { //Can we push into this space?
          //...Only if no gridlock or gridlock below and this space is empty.
          
          if (rowK[c]) --spacesBelow[c]; //pushed down a car
          freeBelowBecomes[c][spacesBelow+1] = shift;
          if (K-shift < 0) 
            rowK[c] = 0;
          else
            rowK[c] = garage[K-shift][c];
        }
        total += rowK[c];
      }
      shifts.push_back(shift+total);
    }

    //No shifts, total Xs.
    for (int c=0;c<C;++c) {
      total += rowK[c];
    }
    shifts.push_back(total);
    

    //Repeat for upward shifts
    rowK = garage[K];

    for (int shift=1;shift<=R-K+1;shift++) {
      total = 0;
      for (int c=0;c<C;++c) {
        if (spacesAbove[c] != 0 || rowK[c] == false) { //Can we push into this space? (NOTE: TCs a little weak; don't require rowK[c] == false here.)
          //...  Only if no gridlock or gridlock above and this space is empty. 
          
          if (rowK[c]) --spacesAbove[c]; //pushed up a car so one fewer empty space. 
          freeAboveBecomes[c][spacesAbove+1] = shift;
          if (K+shift >= R) //Create new empty spaces from the bottom
            rowK[c] = 0;
          else
            rowK[c] = garage[K+shift][c];
        }
        total += rowK[c]; //Total number of one car at a time moves needed.
      }
      shifts.push_back(total+shift);
    }


    for (auto [r,c] : spells) {
      int shift = r+1;
      if (garage[r][c] == true) { //Wong is removing a car
        if (shift >= K+1) {
          
        }
        else if (shift < K+1) { //upward shift to access
          int shiftUpValue = shift-(K+1);

if fi

          
          if (freeAboveBecomes[c][0] < shiftUpValue) //Filling gridlock occurs with a lesser shift than this one, so no change.
          else if (freeAboveBecomes[c][0] > shiftUpValue) { //Filling gridlock occurs currently at a greater shift than this one.
            if (freeAboveBecomes[c][1] < shiftUpValue ) { //Non-filling gridlock occurs currently at a lesser shift than this one
                //Filling gridlock occurs at this one
            }
            else if (freeAboveBecomes[c][1] > shiftUpValue) { //Non-filling gridlock occurs currently at a greater shift than this one
              //filling gridlock occurs at the point non-filling gridlock previously occurred
            }

            if it never occurs ????
          }
          else {
            cout << "should not occur" << endl;
          }
            
  
          
        }

        
        shifts[shift] += 1;
        garage[r][c] = false;
      }
      else {
        
        shifts[shift] -= 1;
        garage[r][c] = true;
      }

        or K minus shift.
    }


    printf("Case #%d: %d\n",t,best);
  }
  
  return 0;
}
