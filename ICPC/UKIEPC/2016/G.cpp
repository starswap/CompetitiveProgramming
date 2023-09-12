#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Line {
	mutable ll m, c, p;
};

// O(N) special case with in-order insert and queries
// Finds max(). If you want min insert the negative.
// maybe don't use reverse
// check if queries go in other order.
struct LineContainer : deque<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(reverse_iterator b, Line n) { // true iff we should remove b
        if (b == rend()) {n.p = -inf; push_back(n); return false;} // nothing in the deque yet; winner from the beginning
        if (n.m == b->m) return n.c > b->c; // parallel; remove old if better, remove new if worse
	    n.p = div(n.c - b->c, b->m - n.m); // n takes over
		if (n.p > b->p) push_back(n); // if n takes over before b takes over, need to remove b.
        return n.p <= b->p;
    }
	void add(ll m, ll c) {
        while(isect(rbegin(), {m, c, 0})) {pop_back();}
    }
	ll query(ll x) {
		assert(!empty());
        while (next(begin()) != end() && next(begin())->p < x) erase(begin());
		return begin()->m * x + begin()->c;
	}
    ll query_bwards(ll x) {
		assert(!empty());
        while (rbegin()->p > x) pop_back();
		return rbegin()->m * x + rbegin()->c;
	}
};

// DP:
//    dp[g][i] = the maximum saving we can make relative to just placing 1 gondola on the last person, given we have g gondolas left and placed the latest gondola on the ith person.
//    dp[g][i] = \max_{j < i}((j + 1) * [skiiers[i] - skiiers[j]] + dp[g -1][j]) // where j + 1 is the number of people that would save time if we placed a gondola at j and the skiiers delta is the time saving.
//             = \max_{j < i}((j + 1) * skiiers[i] - (j + 1) * skiiers[j]] + dp[g -1][j])
//   Let x = skiiers[i] so dp[g][i] = \max_{j < i}((j + 1) * x - (j + 1) * skiiers[j]] + dp[g -1][j])
//   Let c_j = - (j + 1) * skiiers[j]] + dp[g -1][j] so dp[g][i] = \max_{j < i}((j + 1) * x + c_j)
//   Let m_j = (j + 1) so dp[g][i] = \max_{j < i}(m_j * x + c_j)
//   Notice this is in the form of the CHT.
//   Furthermore, the DP can be computed with g as the outer loop and i as the inner loop, both increasing.
//   In this way, we process dp[g][j] for every j below a given i beforehand. While we don't reference this directly (since we use dp[g -1][j])
//     it means we can build the set of lines in question as we go along and this yields a faster CHT solution.
//   Note also that the gradients of the inserted lines occur in increasing order, and the queried x values occur in increasing order too.]
//   This facilitates the use of the more efficient deque-based line container structure.

int solve(vector<int> skiiers, int N, int T, int G) {
    int best = 100000000;
    for (int shifted = 0; shifted < N; ++shifted) { // cycle the array as we don't know which starting point is best.
        int initial_score = 0;
        for (int i = 0; i < N; ++i) {
            initial_score += skiiers[N - 1] - skiiers[i];  // assume we start by placing a gondola at the last person
        }

        int dp[G][N]; //  Gondolas left, position of last gondola placed. Using array for speed.
        for (int g = 0; g < G; ++g) {
            for (int n = 0; n < N; ++n) {
                dp[g][n] = 0;
            }
        }

        LineContainer lc;
        for (int n = 1; n < G; ++n) {
            lc.add(1, -skiiers[0] + dp[n - 1][0]); //for i = 0
            for (int i = 1; i < N; ++i) { // normally we would need to backwards iterate over all positions we could place a gondola
              dp[n][i] = lc.query(skiiers[i]); // Instead we can just use the CHT to work out the optimum in O(1). (due to monotonicity constraint - otherwise log N)
              lc.add(i + 1, -skiiers[i] * (i + 1) + dp[n - 1][i]); // building up our set of lines.
            }
        }

        int score = initial_score - dp[G - 1][N - 1];
        best = min(best, score);
        int last = *skiiers.rbegin();
        skiiers.pop_back();
        skiiers.insert(skiiers.begin(), {last - 2 * T});
    }
    return best;
}

int main() {
    int N, T, G;
    cin >> N >> T >> G;
    vector<int> skiiers(N);    
    for (int n=0; n < N; ++n) {
        cin >> skiiers[n];
        skiiers[n] %= 2 * T;
    }
    sort(skiiers.begin(), skiiers.end());
    cout << solve(skiiers, N, T, G) << endl;
    return 0;
}