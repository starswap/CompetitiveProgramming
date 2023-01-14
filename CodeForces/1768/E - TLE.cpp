// Trying to use Fermat's Little Theorem to compute the inverse every time we need one; too slow. Same algo as E - TLE.py
#include <bits/stdc++.h>
using namespace std;

long long N,M;
long long modfact[3000000];

long long mod_times(const vector<long long> &args) {
    long long it = 1;
    for (long long item : args) {
        it *= item;
        it %= M;
    }
    return it;
}

long long mod_pow(int a, int b, int m) {
    if (b == 1) return a;
    else if (b == 0) return 1;
    else if (b % 2 == 0) {
        long long p = mod_pow(a,b/2,m);
        return (p*p) % m;
    }
    else {                
        return (a*mod_pow(a, b-1, m)) % m;
    }

}

long long mod_inverse(int n) {
    return mod_pow(n, M - 2, M); // Fermat's little theorem; because M is prime.
}

long long mod_choose(int n,int r) {
    return (modfact[n] * mod_inverse((modfact[r] * modfact[n-r]) % M)) % M;
}

int main() {
    cin >> N;
    cin >> M;

    long long MAX_FACT_NEEDED = 3*N;

    // cout << "hop" << endl;
    modfact[0] = 1;
    for (int i=1;i<MAX_FACT_NEEDED+1;++i) {
        modfact[i] = modfact[i-1]*i % M;
    }

    long long le0 = 1;
    long long le1 = (modfact[2*N] * 2 - modfact[N]) % M;
    
    long long intersect = 0;
    for (int i=0;i<N+1;++i) {
        intersect += mod_times(vector<long long>({mod_pow(mod_choose(N,i),2,M),modfact[i],mod_choose(2*N - i, N),modfact[N],mod_choose(N,N-i), modfact[N-i],modfact[N]})) % M;
        intersect %= M;
    }
    
    long long le2 = ((mod_times(vector<long long>({mod_choose(2*N,N) ,modfact[N], modfact[2*N], 2}))) - intersect) % M;
    long long le3 = modfact[3*N] % M;

    long long num0s = le0;
    long long num1s = le1 - le0;
    long long num2s = le2 - le1;
    long long num3s = le3 - le2;


    long long ans = (0*num0s) % M + (1*num1s) % M + (2*num2s) % M + (3*num3s % M);
    cout << (ans + M) % M << endl;
    return 0;
}