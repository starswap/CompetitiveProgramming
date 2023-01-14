#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;
                 
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

int main() {
    int N;
    cin >> N;

    vector<int> a(N);
    long long amt = mod_pow(2, N-2, MOD);

    for (int n=0;n<N;++n) {
        cin >> a[n];
    }

    unordered_map<int,long long> values;
    values.reserve(300*300);
    values[a[1]] = 1;

    for (int i=2;i<N;++i) {
        if (values.contains(0)) {
            amt -= (values[0] * mod_pow(2, ((N-2) - (i - 1)), MOD)) % MOD;
            amt %= MOD;
        }
        unordered_map<int, long long> newValues;
        newValues.reserve(300*300);
        for (auto [item, occs] : values) {
            int total = a[i] + item;
            if (newValues.contains(total)){
                newValues[total] += occs % MOD;
                newValues[total] %= MOD;
            }
            else
                newValues[total] = occs % MOD;
            
            if (item != 0) {
                total = a[i] - item;
                if (newValues.contains(total)) {
                    newValues[total] += occs % MOD;
                    newValues[total] %= MOD;
                }
                else
                    newValues[total] = occs % MOD;
            }
        }
        values = newValues;
    }
 
    cout << ((amt + MOD) % MOD) << endl; 
}
