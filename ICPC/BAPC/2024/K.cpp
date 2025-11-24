#include <bits/stdc++.h>
using namespace std;

using ll = __int128;

inline ll mod(ll f, ll N) {
    return (f + N) % N;
}

const int INF = 1000000;
const int MAX_N = 5000; 

ll prefix_hash[MAX_N + 5];
ll pows_of_a[MAX_N + 5];

const ll a = 53;
const ll N = 10'657'331'232'548'839;
const ll two_N = N * 2;

void prepare_hash(const string& s) {
    // c_i a^{i}
    ll h = 0;
    ll p_n = a;

    for (ll i = 0; i < (ll) s.size(); ++i) {
        ll c = (s[i] - 'a' + 1);
        
        h += (c * p_n); 
        h = mod(h, N);

        prefix_hash[i] = h;
        p_n *= a;
        p_n %= N;
    }

    ll e = 1;
    for (int i = 0; i < MAX_N + 3; ++i) {
        pows_of_a[i] = e;
        e *= a;
        e %= N;
    }
}

long long hash_range(int s, int e) {
    ll prev = (s == 0) ? 0 : prefix_hash[s - 1];
    ll to_shift = mod((prefix_hash[e] - prev), N);
    ll shift_val = pows_of_a[MAX_N + 2 - s];

    return mod((to_shift * shift_val), N);
}

int main() {
    // string s("nananana");
    // prepare_hash(s);
    // cout << hash_range(1, 3) << endl;
    // cout << hash_range(3, 5) << endl;

    string str;
    cin >> str;

    prepare_hash(str);

    int N = str.size();
    
    unordered_map<long long, pair<int, int>> counts;
    counts.reserve(N * N / 2);

    for (int s = 0; s < N; ++s) {
        for (int e = s + 1; e < min(s + N / 2 + 1, N); ++e) {
            ll h = hash_range(s, e);
            auto &[count, end] = counts[h];

            if (end < s || s == 0) {
                count++;
                end = e;
            }
        }
    }

    int best = N + 1;
    for (int s = 0; s < N; ++s) {
        for (int e = s + 1; e < min(s + N / 2 + 1, N); ++e) {
            long long h = hash_range(s, e);
            int l = (e - s + 1);
            int cost = N - counts[h].first * l + counts[h].first + (e - s + 1);

            best = min(cost, best);
        }
    }

    cout << best << endl;
    return 0;
}
