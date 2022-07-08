// AC 07/07/2022

#include <bits/stdc++.h>

using namespace std;

class Report {
  public:
    double totalProb;
    long long numOccur;
    double expectedLength; 

    Report(double tp,long long no,double el) {
      totalProb = tp;
      expectedLength = el;
      numOccur = no;
    }
};


//tail rec?
inline long long f(long long i) {
  if (i == 0)
    return 1;
  else 
    return i*f(i-1);
}


int main() {
  int N; cin >> N;
  double pSunny,pCloudy,pRainy,pFrogs;
  scanf("%lf %lf %lf %lf",&pSunny,&pCloudy,&pRainy,&pFrogs);

//  vector<long long> f(N+1,1);
//  for (int i=1;i<=N;++i) {
 //   f[i] = f[i-1]*i;
 // }
  
    
  // Using lambda to compare elements.
  auto cmp = [](Report left, Report right) { return (left.totalProb) > (right.totalProb); };
  priority_queue<Report, vector<Report>, decltype(cmp)> pq(cmp);

  for (int numSunny=0;numSunny<=N;++numSunny) {
    for (int numCloudy=0;numCloudy<=N-numSunny;++numCloudy) {
       for (int numRainy=0;numRainy<=N-numSunny-numCloudy;++numRainy) {
         int numFrogs = N-numSunny-numRainy-numCloudy;
         double prob = pow(pSunny,numSunny)*pow(pCloudy,numCloudy)*pow(pRainy,numRainy)*pow(pFrogs,numFrogs);
         long long numOccur = f(N)/(f(numSunny)*f(numRainy)*f(numFrogs)*f(numCloudy)); 
         pq.push(Report(prob,numOccur,0));
      }
    }
  }

  while (pq.size() != 1) {
    Report top = pq.top();pq.pop();

    if (top.numOccur == 1) {
      Report next = pq.top();pq.pop();

      double expected = (1+top.expectedLength)*(top.totalProb)/(top.totalProb+next.totalProb) + (1+next.expectedLength)*next.totalProb/(top.totalProb+next.totalProb);
      pq.push(Report(top.totalProb+next.totalProb,1,expected));
      
      if (next.numOccur > 1) {
        pq.push(Report(next.totalProb,next.numOccur-1,next.expectedLength));
      }
    } else if (top.numOccur % 2 == 0) {
      pq.push(Report(top.totalProb*2,top.numOccur/2,1+top.expectedLength));
    } else {
      pq.push(Report(top.totalProb*2,top.numOccur/2,1+top.expectedLength));
      pq.push(Report(top.totalProb,1,top.expectedLength));
    }
  }

  printf("%.6f\n",pq.top().expectedLength);
  return 0;
  
}
