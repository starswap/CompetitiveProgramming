#include <bits/stdc++.h>
using namespace std;

vector<long long> factors(long long N) {
    int i = 1;
    vector<long long> facts;
    while (i * i <= N) {
        if (N % i = 0) {
            facts.push_back(i);
            facts.push_back(N / i);
        }
        i++;
    }
    return facts;
}

pair<long long, bool> mod_pow_fail(long long f, long long g, long long mod) {
    if (f == 1) {
        return make_pair(1, false);
    }
    else if (g == 0) {
        return make_pair(0, false);
    }
    else if (g % 2 == 0) {
        auto [fail, after] = mod_pow_fail(f * f, g / 2, mod);
        return make_pair(fail || after > mod, after);
    }
    else {
        auto [fail, after] = mod_pow_fail(f, g - 1, mod);
        return make_pair(fail || f * after > mod, f * after);
    }
}

pair<long long,long long> solve(long long n) {
    vector<long long> facts = factors(n);
    sort(facts.begin(), facts.end());
    for (long long f : facts) {
        for (long long g : facts) {
            if (pow(f, g) > n || mod_pow_fail(f, g, INT_MAX - 7).second) break;
            if (pow(g, f) > n || mod_pow_fail(g, f, INT_MAX - 7).second) break;
            else {
                if (f * pow(g, f) + g * pow(f, g) == n) return make_pair(f, g);
            }
        }
    }
    return make_pair(-1, -1);
}

int main() {
    int T;
    cin >> T;
    

    for (int t=0; t<T; t++) {
        int N; cin >> N;
        auto ans = solve(N);
        if (ans.first == -1) {
            cout << -1 << endl;
        }
        else {
            cout << ans.first << " " << ans.second << endl;
        }
    }        
}
