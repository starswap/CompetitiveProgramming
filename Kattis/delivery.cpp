#include <bits/stdc++.h>
using namespace std;

int main() {
  int N,K; scanf("%d %d",&N,&K);
  vector<int> letters(N);
  vector<int> places(N);
  for (int i=0;i<N;++i)
    scanf("%d %d",&places[i],&letters[i]);

  //already sorted

  int spareCap = 0; //spare truck capacity from points further out than this one 
  int i = 0; //index of the current point being considered
  int totalDist = 0; //total distance travelled

  //from furthest out -ve to 0.
  while (places[i] < 0) {
    int amtAboveNTrucks = letters[i]%K;
    if (spareCap >= amtAboveNTrucks){ //enough spare capacity to cover this one down to one fewer trip// should this be awhile? Could you get a whole van spare? I don't think so.
      spareCap -= amtAboveNTrucks; //use up the spare capacity
      letters[i] -= amtAboveNTrucks; //no longer need N+1 trucks
    } else { // can't bring this one down to use fewer trucks
      spareCap += K - (amtAboveNTrucks); //pocket the spare capacity.
    }
    totalDist += 2*abs(places[i])*ceil(static_cast<double>(letters[i])/static_cast<double>(K)); //twice the distance to this one, times the no of trips. 
    i++;
  }

  //from furthest out +ve to 0; reset spare capacity as will pass through 0 before getting there.
  spareCap = 0;
  i = N-1; //iterating backwards.
  while (places[i] > 0) {
    int amtAboveNTrucks = letters[i]%K;    
    if (spareCap >= amtAboveNTrucks){ //enough spare capacity to cover this one down to one fewer trip// should this be awhile? Could you get a whole van spare? I don't think so.
      spareCap -= amtAboveNTrucks;
      letters[i] -= amtAboveNTrucks;
    } else {
      spareCap += K - (amtAboveNTrucks);
    }
    totalDist += 2*abs(places[i])*ceil(static_cast<double>(letters[i])/static_cast<double>(K));
    i--; //iterate backwards
  }  
  cout << totalDist << endl; //final answer;

  return 0;
}