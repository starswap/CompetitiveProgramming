//WA/TLE: This version is mistaken because it tries to use both iteration and recursion over the stories when only one is needed, which leads to excessive repeat computation and causes TLE. The intersect() method may also not be correct as it is excessively complicated, meaning that potentially a mistake may have been made in it. 


#include <bits/stdc++.h>
using namespace std;

inline int LSOne(int a) {
  return ((a)&(-a));
}

class Story {
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

vector<Story> stories;

bool intersect(const Story& a, const Story & b) {
  vector<int> cornersBX;
  vector<int> cornersBY;
  cornersBX.push_back(b.x);
  cornersBX.push_back(b.x+b.w);
  cornersBX.push_back(b.x+b.w);
  cornersBX.push_back(b.x);

  cornersBY.push_back(b.y);
  cornersBY.push_back(b.y);
  cornersBY.push_back(b.y+b.h);
  cornersBY.push_back(b.y+b.h);

  int numBorderline = 0;
  for (int i=0;i<4;++i) {
    int x = cornersBX[i];
    int y = cornersBY[i];
    if ((a.x < x && x < a.x+a.w && a.y < y && y < a.y+a.h))//this current corner is contained within A.
      return true;
    
    if ((a.x <= x && x <= a.x+a.w && a.y < y && y < a.y+a.h) || (a.x < x && x < a.x+a.w && a.y <= y && y <= a.y+a.h)) { //this current corner is contained within A.
      numBorderline++;
    }
  }
  if (numBorderline >= 2)
    return true;
  
  return false; 
}

vector<int> permissible;

vector<int> dp;

int bestSet(int currentStory,int canUse) {
  if (dp[canUse] != -1)
    return dp[canUse];
  
  int optimal = stories[currentStory].score;

  //pick this one as well
  int canUseCopy = canUse & permissible[currentStory];
  int maxScore = 0; //maximum total if we could place all of the others
  // while (canUseCopy) {
  //   maxScore += stories[__builtin_ctz(LSOne(canUseCopy))].score;
  //   canUseCopy ^= LSOne(canUseCopy);    
  // }
  
  canUseCopy = canUse & permissible[currentStory];
  while (canUseCopy) {
    // if (maxScore + stories[currentStory].score > optimal)
      optimal = max(optimal,bestSet(__builtin_ctz(LSOne(canUseCopy)),(canUse & permissible[currentStory] ^ (LSOne(canUseCopy))))+stories[currentStory].score);
    canUseCopy ^= LSOne(canUseCopy);
  }

  //don't pick this one as well
  // canUseCopy = canUse;  
  // while (canUseCopy) {
  //   maxScore += stories[__builtin_ctz(LSOne(canUseCopy))].score;
  //   canUseCopy ^= LSOne(canUseCopy);    
  // }
  canUseCopy = canUse;    
  while (canUseCopy) {
    // if (maxScore > optimal)
      optimal = max(optimal,bestSet(__builtin_ctz(LSOne(canUseCopy)),(canUse ^ (LSOne(canUseCopy)))));
    canUseCopy ^= LSOne(canUseCopy);    
  }  

  dp[canUse] = optimal;
  return optimal;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int N;
  while (scanf("%d",&N), N != 0) {
    stories.clear();
    for (int n=0;n<N;++n) {
      int w,h,x,y;
      scanf("%d %d %d %d",&w,&h,&x,&y);
      stories.emplace_back(w,h,x,y);
    }
    
    permissible.assign(N,0);


    for (int i=0;i<N;++i) {
      for (int j=i+1;j<N;++j) {
        if (!(intersect(stories[i],stories[j]) || intersect(stories[j],stories[i]))) {
          permissible[i] |= 1 << j;
          permissible[j] |= 1 << i;
        }
      }
    }

    dp.assign(pow(2,N),-1);

    // int totalAll = 0;
    // for (int i=0;i<N;++i) {
    //   if (permissible[i] == (1<<N)-1)
    //     totalAll += stories[i].w*stories[i].h;
    // }
      
    //printf("starting\n");
    printf("%d\n",bestSet(0,pow(2,N)-2));

  }
  
  return 0;
}
