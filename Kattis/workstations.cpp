#include <bits/stdc++.h>
using namespace std;

int main() {
  int n,m; scanf("%d %d",&n,&m);
  vector<pair<int,int>> researchers;
  for (int i=0;i<n;++i) {
    int s,a; scanf("%d %d",&a,&s);
    researchers.emplace_back(a,s);
  }
  sort(researchers.begin(),researchers.end());

  priority_queue<int,vector<int>,greater<int>> workstations;

  int totalUnlocks = 0;
  for (int i=0;i<n;++i) {
    auto [a,s] = researchers[i];
    if (workstations.size() == 0) // no reusable workstations
      totalUnlocks++;
    else {
      if (a < workstations.top()) { //no reusable workstations; arrives before first one available.
        totalUnlocks++;
      }
      else {
        while (a > workstations.top()+m) { //while there are more workstations that could be reused and the person is arriving too late, 
          if (workstations.size() == 0) { //there are no reusable workstations left
            totalUnlocks++; break;
          }
        workstations.pop(); //no-one else will arrive early enough for this to be useful
        }
        if (workstations.size() > 0) //we just reused one; bin it.
          workstations.pop();   
      }
    }
    workstations.push(a+s);  
  }

  cout << n - totalUnlocks << endl;
   return 0;   
}