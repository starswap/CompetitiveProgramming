#include <bits/stdc++.h>
using namespace std;

inline int LSOne(int a) {
  return (a&-a);
}

class Point {
  public:
    double x, y;
    Point() : x(0), y(0) {};
    Point(double nx,double ny):x(nx), y(ny) {};
};

const int MAX2 = 11;
const int MAX1 = 1<<MAX2;

double dp[MAX1][MAX2]; //dp[visitedBM][u]

vector<string> currentPlaces;
unordered_map<string,int> nameToIndex;
vector<Point> points;

inline double cost(string a, string b) {
  Point p1 = points[nameToIndex[a]];
  Point p2 = points[nameToIndex[b]];
  return hypot(p1.x-p2.x,p1.y-p2.y);
} 

double tsp(int visitedBM, int u) {
  if (visitedBM == 0) 
    return cost(currentPlaces[u],"home"); //finish

  if (dp[visitedBM][u] != -1)
    return dp[visitedBM][u];
  
  int prevVisited = visitedBM;
  double best = 1e20;
  while (visitedBM > 0) {
    int twoPowV = LSOne(visitedBM);
    int v = __builtin_ctz(twoPowV);
    best = min(best,cost(currentPlaces[u],currentPlaces[v])+tsp(prevVisited^twoPowV,v));
    visitedBM ^= twoPowV;
  }

  dp[prevVisited][u] = best;
  return best;
}

void printDP(int visitedBM, int u) {
  int prevVisited = visitedBM;
  double best = 1e20;
  int bestIndex = 0;
  int iter = 0;
  while (visitedBM > 0) {
    int twoPowV = LSOne(visitedBM);
    int v = __builtin_ctz(twoPowV);
    
    double newCost = cost(currentPlaces[u],currentPlaces[v])+tsp(prevVisited^twoPowV,v);
    if (newCost < best) {
      best = newCost;
      bestIndex = v;
    }
    visitedBM ^= twoPowV;
    ++iter;
  }

  if (iter == 1)
    cout << currentPlaces[bestIndex] << endl;
  else {
    cout << currentPlaces[bestIndex] << " ";
    printDP(prevVisited ^ (1<<bestIndex),bestIndex);
  }
}


int main() {
  int n; 
  scanf("%d",&n);

  points.assign(n,Point());
  for (int i=0;i<n;++i) {
    string name;
    cin >> name;
    scanf("%lf %lf",&points[i].x,&points[i].y);
    nameToIndex.emplace(name,i);
  }

  char nextChar; //either space or newline after each place is read in.
  string place;
  currentPlaces.push_back("work");
  do {
    cin >> place;
    currentPlaces.push_back(place);
  } while (scanf("%c",&nextChar) != EOF && nextChar != '\n'); //Read one line which may be the last
  
  while (!cin.eof()) {
    for (int j=0;j<MAX1;j++) {
      for (int k=0;k<MAX2;k++) {
        dp[j][k] = -1;
      }
    }
    //get best
    tsp(((1<<currentPlaces.size())-2),0);
    printDP((1<<currentPlaces.size())-2,0);

    currentPlaces.clear();  
    currentPlaces.push_back("work");    
    do {
      cin >> place;
      currentPlaces.push_back(place);
    } while (scanf("%c",&nextChar) != EOF && nextChar != '\n'); //Read one line which may be the last
  }
  
  return 0;
}
