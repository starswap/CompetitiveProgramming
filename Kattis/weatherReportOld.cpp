//Does not work


#include <bits/stdc++.h>

using namespace std;

class Report {
  public:
    double totalProb;
    long long numOccur;
    long long totalLength;
    long long numPaths; 

    Report(double tp,long long no, long long tl, long long np) {
      totalProb = tp;
      numOccur = no;
      totalLength = tl;
      numPaths = np;
    }
};


//tail rec?
inline long long f(long long i) {
  if (i == 1)
    return 1;
  else 
    return i*f(i-1);
}


int main() {
  int N; cin >> N;
  double pSunny,pCloudy,pRainy,pFrogs;
  scanf("%lf %lf %lf %lf",&pSunny,&pCloudy,&pRainy,&pFrogs);

  // Using lambda to compare elements.
  auto cmp = [](Report left, Report right) { return (left.totalProb) > (right.totalProb); };
  priority_queue<Report, vector<Report>, decltype(cmp)> pq(cmp);

  for (int numSunny=0;numSunny<=N;++numSunny) {
    for (int numCloudy=0;numCloudy<=N-numSunny;++numCloudy) {
       for (int numRainy=0;numRainy<=N-numSunny-numCloudy;++numRainy) {
         int numFrogs = N-numSunny-numRainy-numCloudy;
         double prob = pow(pSunny,numSunny)*pow(pCloudy,numCloudy)*pow(pRainy,numRainy)*pow(pFrogs,numFrogs);
         long long numOccur = f(20)/(f(numSunny)*f(numRainy)*f(numFrogs)*f(numCloudy)); 
         pq.push(Report(prob,numOccur,1,1));
      }
    }
  }

  while (pq.size() != 1) {
    Report top = pq.top();pq.pop();

    if (top.numOccur == 1) {
      Report next = pq.top();pq.pop();
      
      pq.push(Report(top.totalProb+next.totalProb,1,top.totalLength+next.totalLength+top.numPaths+next.numPaths,top.numPaths+next.numPaths));
      
      if (next.numOccur > 1) {
        pq.push(Report(next.totalProb,1,next.totalLength,next.numPaths));
      }
    }
    
    if (top.numOccur % 2 == 0) {
      pq.push(Report(top.totalProb*2,top.numOccur/2,2*top.totalLength,2*top.numPaths));
    } else {
      pq.push(Report(top.totalProb*2,top.numOccur/2,2*top.totalLength,2*top.numPaths));
      pq.push(Report(top.totalProb,1,top.totalLength,top.numPaths));
    }
  }


  return 0;
  
}
