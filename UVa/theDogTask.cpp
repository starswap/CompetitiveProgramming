#include <bits/stdc++.h>
using namespace std;

class Point {
  public:
    Point(int a,int b):x(a),y(b) {};
    Point():x(0),y(0) {};
    int x;
    int y;
};

bool operator < (const Point &a,const Point &b) {
  if (a.x == b.x)
    return a.y < b.y; //needed for map
  else
    return a.x < b.x;
}

ostream& operator <<  (ostream& o,Point p) {
  o << p.x << " " << p.y;
  return o;
}

int augPath(map<Point,vector<Point>> &AL,Point L,set<Point>& visited,map<Point,Point>&matches) {
  if (visited.count(L) == 1) return 0;
  visited.insert(L);

  for (Point R :AL[L]) {
    if (matches.count(R) == 0 || augPath(AL,matches[R],visited,matches)) {
      matches[R] = L;
      return 1;
    }
  }
  return 0;
} 

pair<map<Point,Point>,int> MCBM(map<Point,vector<Point>> &AL,vector<Point> leftNodes) {
  map<Point,Point> matches;
  set<Point> visited;
  int totalMatches = 0;
  for (Point L : leftNodes) {
    visited.clear();
    totalMatches += augPath(AL,L,visited,matches);
  }
  return pair<map<Point,Point>,int>(matches,totalMatches);
}

float euclidDist(Point &a, Point &b) {
  return sqrt(pow(a.x-b.x,2) + pow(a.y-b.y,2));
}


int main() {
  int T;
  cin >> T;
  for (int t=0;t<T;t++) {
    int N,M;
    cin >> N; //number of required places
    cin >> M; //number of optional places
    map<Point,vector<Point>> AL;
    vector<Point> leftPoints;
    vector<Point> rightPoints;
    for (int n=0;n<N;n++) {
      int a,b;
      cin >> a;
      cin >> b;
      Point newPoint(a,b);
      AL[newPoint] =  vector<Point>();
      leftPoints.push_back(newPoint); //have to go to
    }
    for (int m=0;m<M;m++) {
      int a,b;
      cin >> a;
      cin >> b;
      Point newPoint(a,b);
      AL[newPoint] =  vector<Point>();
      rightPoints.push_back(newPoint);
    }

 //   cout << leftPoints << endl;
   // cout << rightPoints << endl;

    for (int p1=0;p1<leftPoints.size()-1;p1++){ //CHECK-1
      float distToNextPt = euclidDist(leftPoints[p1],leftPoints[p1+1]);
      for (int p2=0;p2<rightPoints.size();p2++) {
        float incurredDist = euclidDist(leftPoints[p1],rightPoints[p2]) + euclidDist(rightPoints[p2],leftPoints[p1+1]);
        if (incurredDist <= distToNextPt*2) {
 //         cout << "rp" << rightPoints[p2] << endl;
   //       cout << "lp" << leftPoints[p1] << endl;
          AL[leftPoints[p1]].push_back(rightPoints[p2]);
          AL[rightPoints[p2]].push_back(leftPoints[p1]);
       //   cout << "AL" << AL << endl;

        }
      }
    }



    auto [matchings,number] = MCBM(AL,rightPoints);
    cout << number+leftPoints.size() << '\n';
  //  cout << matchings << endl;
    for (int p=0;p<leftPoints.size()-1;p++) {
      cout << leftPoints[p] << " ";
      if (matchings.count(leftPoints[p]) == 1) {
        cout << matchings[leftPoints[p]] << " ";
      }
    }
    cout << *leftPoints.rbegin() << endl;
    if (!(t == T-1))
      cout << endl;

  }
}
