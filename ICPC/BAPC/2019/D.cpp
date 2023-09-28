#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll HUGE_THRESH = 1000000000000;

ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}

ll crt(ll a, ll m, ll b, ll n, bool &ok) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    ok = ((a - b) % g == 0);
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m*n/g : x;
}

ll lcm(ll a, ll b) {
    return a * b / __gcd(a, b);
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    
    int N; cin >> N;

    vector<int> A(N);
    for (int n = 0; n < N; ++n) {
        cin >> A[n]; A[n]--;
    }
    
    vector<int> B(N);
    for (int n = 0; n < N; ++n) {
        cin >> B[n]; B[n]--;
    }

    vector<bool> visited(N, false);
    
    // method 1
    ll cycle_lcm = 1;

    // method 2
    bool can_do_method_2 = true;
    vector<ll> ks;
    vector<ll> ns;

    for (int i = 0; i < N; ++i) {
        if (!visited[i]) {

            int cycle_size = 0;
            int turns = -1;

            for (int j = i; !visited[j]; j = A[B[j]]) {
                if (j == A[i]) { // turning this many times is equivalent to A
                    turns = cycle_size;
                }
                visited[j] = true; // found the amount of turns of AB to make this number correct, in theory
                cycle_size++;
            }
            
            // Method 1 processing
            cycle_lcm = (cycle_lcm > HUGE_THRESH) ? cycle_lcm : lcm(cycle_lcm, cycle_size);

            // Method 2 processing 
            if (turns == -1) { // couldn't find a number of turns to match A[0] and AB[0]
                can_do_method_2 = false;
            } else if (can_do_method_2) { // speedup - we think we can still do method 2
                int ab_i = i;
                int ab_j = i;

                // make ab_i be turns spaces in front of ab_j, so should always be the next one after ab_j in A.
                for (int n = 0; n < turns; ++n) {
                    ab_i = A[B[ab_i]];
                }

                do {
                    can_do_method_2 &= A[ab_j] == ab_i;
                    ab_j = A[B[ab_j]];
                    ab_i = A[B[ab_i]];
                } while (ab_j != i);

                ns.push_back(cycle_size);
                ks.push_back((-turns + cycle_size) % cycle_size);
            }
        }
    }

    ll ans_1 = cycle_lcm * 2;
    ll ans_2 = HUGE_THRESH + 1;
    if (can_do_method_2) {
        ll ab_steps = ks[0];
        ll mod = ns[0];
        bool ok = true;
        for (int i = 1; ab_steps >= 0 && ok && ab_steps <= HUGE_THRESH && i < ks.size(); ++i) {
            ab_steps = crt(ks[i], ns[i], ab_steps, mod, ok);
            mod = ns[i] * mod / (__gcd(ns[i], mod));
            mod = min(mod, HUGE_THRESH);
        }
        if (ab_steps >= 0 && ab_steps < HUGE_THRESH && ok)
            ans_2 = 2 * ab_steps + 1;
    }

    ll best = min(ans_1, ans_2);
    if (best > HUGE_THRESH) {
        cout << "huge" << endl;
    } else {
        cout << best << endl;
    }

    return 0;
}