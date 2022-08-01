#include <bits/stdc++.h>
using namespace std;

inline int LSOne(int v) {
  return (v&-v);
}

class Point {
  public:  
    int x,y;
    Point() : x(0),y(0) {}; //Default
    Point(int nx, int ny) : x(nx), y(ny) {};
};

inline int cost(Point a, Point b) {
  return abs(a.x-b.x) + abs(a.y-b.y);
}

int maX,maxY,nBeepers;
vector<Point> points;
int dp[1024][10]; //dp[alreadyVisited][u] // max is 10 beepers

int tsp(int visitedBM, int u) {
  if (visitedBM == 0) //all visited
    return cost(points[u],points[0]); //go back to the beginning
  if (dp[visitedBM][u] != -1) return dp[visitedBM][u];
  
  int formerVisited = visitedBM;
  int best = 10000000;
  while (visitedBM != 0) {
    int twoPowV = LSOne(visitedBM);
    int v = __builtin_ctz(twoPowV)+1; //account for start
    best = min(best,cost(points[u],points[v]) + tsp(formerVisited ^ twoPowV,v));
    visitedBM ^= twoPowV;
  }
  dp[formerVisited][u] = best;
  return dp[formerVisited][u];
}

int main() {
  int N; scanf("%d",&N);
  while (N--) {
    points.assign(1,Point());
    scanf("%d %d",&maX,&maxY);
    scanf("%d %d",&points[0].x,&points[0].y);    
    scanf("%d",&nBeepers);
    
    for (int i=1;i<=nBeepers;++i) {
       points.push_back(Point());
       scanf("%d %d",&points[i].x,&points[i].y);
    }

    memset(dp,-1,sizeof dp);
    int start = (1<<nBeepers)-1;
    int best = tsp(start,0);
    printf("The shortest path has length %d\n",best);
      
  }
  return 0;
}
