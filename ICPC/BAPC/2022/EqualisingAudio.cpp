#include <bits/stdc++.h>
using namespace std;

int main() {
    int n,x;
    scanf("%d %d",&n,&x);
    vector<long long> amps(n); 
    double t = 0;
    
    for (int i=0;i<n;++i) {
        scanf("%lld",&amps[i]);
        t += static_cast<double>(amps[i])*static_cast<double>(amps[i]);
    }
    t /= static_cast<double>(n);
    if (t == 0)
        t = 1;
    cout << setprecision(9);

    for (int i=0;i<n-1;++i) {
        cout << static_cast<double>(amps[i])*sqrt(static_cast<double>(x)/t) << " ";   
    }
    cout << static_cast<double>(amps[n-1])*sqrt(static_cast<double>(x)/t) << endl;
      
    return 0;
}