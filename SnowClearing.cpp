#include <bits/stdc++.h>
using namespace std;
int main() {
  int T;
  cin >> T;
  string line;
  getline(cin,line);
  for (int t=0;t<T;t++) {
    int x,y;
    cin >> x;
    cin >> y;
    long double dist = 0;
    getline(cin,line);
    for (getline(cin,line);line != "" && !cin.eof();getline(cin,line)) {
      int x1,y1,x2,y2;
      sscanf(line.c_str(),"%d %d %d %d",&x1,&y1,&x2,&y2);
      dist += 2*sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    }
    dist /= 20000;

    int mins = round(dist * 60); //minutes
    int hours = floor(mins/60);
    mins = (mins - hours*60);
    cout << hours << ":";
    if (mins < 10) 
      cout << "0";
    cout << mins << "\n";
    if (t != T-1) {
      cout << "\n";
    }
  }
  return 0;
}
