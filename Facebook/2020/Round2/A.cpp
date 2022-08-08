#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; scanf("%d",&T);
  
  for (int t=1;t<=T;++t) {
    int N,K; scanf("%d %d",&N,&K);
    
    vector<long long> S(N);
    vector<long long> X(N);
    vector<long long> Y(N);
    
    long long As,Bs,Cs,Ds;
    long long Ax,Bx,Cx,Dx;
    long long Ay,By,Cy,Dy;
    for (int k=0;k<K;++k) {
      scanf("%lld",&S[k]);
    }
    scanf("%lld %lld %lld %lld",&As,&Bs,&Cs,&Ds);
    for (int k=0;k<K;++k) {
      scanf("%lld",&X[k]);
    }
    scanf("%lld %lld %lld %lld",&Ax,&Bx,&Cx,&Dx);
    for (int k=0;k<K;++k) {
      scanf("%lld",&Y[k]);
    }    
    scanf("%lld %lld %lld %lld",&Ay,&By,&Cy,&Dy);    

    for (int i=K;i<N;++i) {
      S[i] = (As*S[i-2] + Bs*S[i-1] + Cs) % Ds;
      X[i] = (Ax*X[i-2] + Bx*X[i-1] + Cx) % Dx;
      Y[i] = (Ay*Y[i-2] + By*Y[i-1] + Cy) % Dy;
    }

    long long minOut = 0;
    long long maxOut = 0;
    long long minIn  = 0;
    long long maxIn  = 0;
    
    for (int n=0;n<N;++n) {
      minOut += max(static_cast<long long>(0),S[n]-X[n]-Y[n]);
      minIn  += max(static_cast<long long>(0),X[n]-S[n]);
      maxOut += max(static_cast<long long>(0),S[n]-X[n]);
      maxIn  += max(static_cast<long long>(0),X[n]+Y[n]-S[n]);
    }

    if (minIn > maxOut || minOut > maxIn)
      printf("Case #%d: -1\n",t);
    else
      printf("Case #%d: %lld\n",t,max(minOut,minIn));
  }
  
  return 0;
}