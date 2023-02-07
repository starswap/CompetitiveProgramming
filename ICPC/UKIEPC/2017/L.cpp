#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> vec;
typedef pair<int, int> point; 

int Tx, Ty, N;
map<pair<int, int>, vector<point>> lizard_buckets;
map<point, int> lizard_to_height;

int lis(const vector<int>& xs) {
    int n = xs.size();
    int k = 0;
    vector<int> endValLengthL(n, 0);
    vector<int> endIdxLengthL(n, 0);

    for (int i = 0; i < n; ++i) {
        int l = lower_bound(endValLengthL.begin(), endValLengthL.begin() + k, xs[i]) - endValLengthL.begin();
        endValLengthL[l] = xs[i];
        endIdxLengthL[l] = i;
        if (l == k) k++;
    }

    return k;
}

int sgn(int x) {
    if (x == 0) return 0;
    else return x / abs(x);
}

void sortVec(vec v, vector<point> &liz) {
    sort(liz.begin(), liz.end(), [v](point a, point b) {
        a.first *= sgn(v.first);
        a.second *= sgn(v.second);
        b.first *= sgn(v.first);
        b.second *= sgn(v.second);
        return a < b;
    });
} 

int solve() {
    int total = 0;
    for (auto [dVec, liz] : lizard_buckets) {
        sortVec(dVec, liz);
        vector<int> H;
        for (point p : liz) {
            H.push_back(lizard_to_height[p]);
        }
        total += lis(H);
    }
    return total;
}

// bucket by 1ed vector to tv.
// LIS over each one.
// sum of LIS lengths

int main() {
    
    cin >> Tx >> Ty;
    cin >> N;

    for (int n=0; n<N; n++) {
        int x, y, h;
        cin >> x >> y >> h;
        lizard_to_height[make_pair(x, y)] = h;

        int dx = x - Tx ;
        int dy = y - Ty;
        lizard_buckets[make_pair(dx / __gcd(abs(dx), abs(dy)), dy / __gcd(abs(dx), abs(dy)))].emplace_back(make_pair(x,y));
    }     

    cout << solve() << endl;   
}
