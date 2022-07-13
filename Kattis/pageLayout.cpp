//In theory this could be TLE if the maximum size of 20 was asked for every time (2^20 subsets * 500 test cases = 524x10^6 i.e 5.2 secs assuming 100M ops per sec), but due to pruning it will be ok as we don't examine all 2^20 subsets since we only examine subsets where the stories can sit together without conflict.

#include <bits/stdc++.h> //include all C++ STL libraries
using namespace std;

inline int LSOne(int a) { //Gets Least Significant 1 in a binary number (Two's Complement negative representation: -ve a is "flip all the bits except the LS one bit" so when we take a AND -a only the LS one bit is set) 
  return ((a)&(-a));
}

class Story { //use as a struct to store the story characteristics and calculate score; makes it easier to code the routine to check for intersection.
  public:
    int x;
    int y;
    int h;
    int w;
    int score;

    Story(int nW,int nH,int nX, int nY) {
      x = nX; w = nW; y = nY; h = nH;
      score = w*h;
    }

};

vector<Story> stories; //all stories; will be used to determine which go with which and to get their scores when used 
static int permissible[20]; //bitmasks for each story indicating the other stories it can go with.
static int scores[20]; //once we have pre-determined the intersections using OOP for ease of coding we save the scores of each Story to this array for faster processing and do away with the OOP which we no longer use during the main backtracking routine.

bool intersect(const Story& a, const Story & b) {
  //Determine if two rectangles overlap, as detailed here: https://www.geeksforgeeks.org/find-two-rectangles-overlap
  
  if (a.x >= b.x+b.w || b.x >= a.x+a.w) // one is to the right of the other.
    return false; //and so no overlap
  if (b.y >= a.y+a.h || a.y >= b.y+b.h) // one is below the other.
    return false; //and so no overlap
  return true; //all non-overlap cases failed therefore must overlap
}


int bestSet(int canUse) {
  //Determines the best possible score when choosing a set of stories
    //canUse = bitmask for the stories that we are allowed to choose, given our previous choices
  
  if (canUse == 0) //nothing left to choose so return
    return 0;

  //currentStory = the story we are about to decide to chuck out or keep
  int currentStory = __builtin_ctz(LSOne(canUse)); // (builtinctz acts as a logarithm (gives number of trailing 0s) so can be used as the inverse of 1<<x). So we are now going to decide whether or not to take the lowest index story that is still possible.
  
  int optimal = scores[currentStory]; //At worst we can always pick the current story and nothing else, which scores us the area of the current story, as previously calculated.
  canUse ^= 1<<currentStory; //turn off the bit for the current story so we don't pick it again

  //pick this one and decide whether we should pick the next compatible story or not

  optimal = max(optimal,bestSet(canUse & permissible[currentStory])+scores[currentStory]); //only stories compatible with the currentStory can be picked in future, and so we prune by using the bitwise & on the bitmasks.


  //don't pick this one and move to the next story compatible with our previous choices
  optimal = max(optimal,bestSet(canUse));

  //optimal now contains the maximum achievable score from with the available stories as described by canUse, be that taking or leaving currentStory.
  
  return optimal; // ... and so this is the answer which we return to the caller
}

int main() {  
  int N; //number of stories
  while (scanf("%d",&N), N != 0) { 
    
    stories.clear(); //reset global for new test case
    for (int n=0;n<N;++n) { //get story properties (width, height, xPos, yPos for top left)
      int w,h,x,y;
      scanf("%d %d %d %d",&w,&h,&x,&y);
      stories.emplace_back(w,h,x,y);
    }
    
    for (int i=0;i<N;++i) {
      permissible[i] = 0; //reset all bitmasks to 0 
      scores[i] = stories[i].score; //cache the scores so we no longer need to bother with OOP
    }

    //for each pair of stories
    for (int i=0;i<N;++i) {
      for (int j=i+1;j<N;++j) {
        if (!(intersect(stories[i],stories[j]))) { //can they both be placed on the same page?
          permissible[i] |= 1 << j; //if they can, then we flag in the bitmasks that they are compatible
          permissible[j] |= 1 << i; //this needs to be done in both directions (i.e. A compatible with B and B compatible with A)
        }
      }
    }  
      
    printf("%d\n",bestSet(pow(2,N)-1)); //The answer is the best possible score (as returned by bestSet(), starting with all stories available to be placed
  }
  
  return 0;
}
