//This DP version examines more states than the optimal complete search method because it considers different orders that the stories could be selected in which is excessive computation, and as a result it's TLE.

#include <bits/stdc++.h>
using namespace std;

class Story {
  public:
    int x;
    int y;
    int h;
    int w;

    Story(int nW,int nH,int nX, int nY) {
      x = nX; w = nW; y = nY; h = nH;
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

// bool intersect(const Story&a,const Story&b) {
//   return (b.y < a.y && a.y < b.y+b.h && b.x < a.x && a.x < b.x+b.w )
// }


vector<int> permissible;

int longestPath(const vector<vector<int>>&AL,int u,int visited,int memo[20][2097151], int compatible) {
  if (memo[u][visited] != -1)
    return memo[u][visited];
  
  int pathLength = stories[u].w*stories[u].h;
  for (int v : AL[u]) {
    if (!(visited & 1<<v) && (compatible & 1<<v)) {
      pathLength = max(pathLength,stories[u].w*stories[u].h+longestPath(AL,v,visited ^ (1<<v),memo,compatible & permissible[u]));
    }
  }

  memo[u][visited] = pathLength;
  return pathLength;
}

static int memo[20][2097151];

int main() {
  int N;
  while (scanf("%d",&N), N != 0) {
    stories.clear();
    for (int n=0;n<N;++n) {
      int w,h,x,y;
      scanf("%d %d %d %d",&w,&h,&x,&y);
      stories.emplace_back(w,h,x,y);
    }
    
    vector<vector<int>> AL(N);

    for (int i=0;i<N;++i) {
      for (int j=i+1;j<N;++j) {
        if (!(intersect(stories[i],stories[j]) || intersect(stories[j],stories[i]))) {
          AL[i].push_back(j);
          AL[j].push_back(i);          
        }
      }
    }
    permissible.clear();
    for (int i=0;i<N;++i) {
      int options = 0;
      for (int v : AL[i]) {
        options |= 1<<v;
      }
      permissible.push_back(options);
    }

    for (int i=0;i<N;++i){ 
      for (int j=0;j<2097151;++j) {
        memo[i][j] = -1;
      }
    }

    int maxi = 0;
    for (int i=0;i<N;++i) {
      maxi = max(maxi,longestPath(AL,i,1<<i,memo,2097151));
    }

    printf("%d\n",maxi);

  }
  
  return 0;
}