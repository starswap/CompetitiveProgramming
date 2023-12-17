#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct mll { /* Modded Long Long */
    private:
        static const ll MOD = 998'244'353;
        ll x;

    public:
        mll(ll x):x(x) {}
        ll get() {
            return x;
        } 
    
    friend mll operator +(mll a, mll b) {
        return mll((a.x + b.x) % MOD);
    } 
    
    friend mll operator -(mll a, mll b) {
        return mll(((a.x - b.x) + MOD) % MOD);
    } 

    friend mll operator *(mll a, mll b) {
        return mll((a.x * b.x) % MOD);
    } 

    friend mll operator ^(mll a, mll b) {
        ll base = a.x; ll exp = b.x;
        base %= MOD;
        ll result = 1;
        while (exp > 0) {
            if (exp & 1) result = (result * base) % MOD;
            base = (base * base) % MOD;
            exp >>= 1;
        }
        return mll(result);
    }
};

struct eqn { /* Equations of the form ax + b */
    public:
        mll x_coeff;
        mll constant;
        eqn(): x_coeff(0), constant(0) {}
        eqn(mll x_coeff, mll constant): x_coeff(x_coeff), constant(constant) {}
        
        mll apply(mll x) {
            return x * x_coeff + constant;
        }
    
    friend eqn operator +(eqn a, eqn b) {
        return eqn(a.x_coeff + b.x_coeff, a.constant + b.constant);
    }
};

map<ll, eqn> dp;

eqn build(ll nodes) { 
    if (nodes == 1) {
        return eqn(1, 0);
    }
    if (!dp.count(nodes)) {
        /* LEFT */
        ll l_size = nodes - (nodes / 2);
        eqn a1 = build(l_size);
        eqn b1 = eqn(mll(2) * a1.x_coeff, a1.constant); /* We want to use x = 2 * x in the LHS */
        
        /* RIGHT */
        ll r_size = nodes / 2;        
        eqn a2 = build(r_size);
        eqn b2 = eqn(mll(2) * a2.x_coeff, a2.x_coeff + a2.constant); /* We want to use x = 2 * x + 1 in the RHS */

        /* Number of times that this node is the LCA */
        eqn b3 = eqn(((mll(2) ^ l_size) - 1) * ((mll(2) ^ r_size) - 1), 0);

        dp[nodes] = b1 + b2 + b3;
    }
    
    return dp[nodes];
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        ll N; cin >> N;
        eqn ans = build(N);
        cout << ans.apply(1).get() << endl;
    }
    return 0;
}
