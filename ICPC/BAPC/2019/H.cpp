#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct pedestal {
    int first;
    int second;
    int id;
    bool operator < (pedestal other) {
        if (first == other.first) {
            if (second == other.second) {
                return id < other.id;
            } else {
                return second < other.second;
            }
        } else {
            return first < other.first;
        }
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int p,v;
    cin >> p >> v;

    vector<pedestal> ds(p);
    for (int i = 0; i < p; ++i) {
        int a,b;
        cin >> a >> b;
        ds[i].first = min(a, b);
        ds[i].second = max(a, b);
        ds[i].id = i + 1;
    }

    sort(ds.begin(), ds.end());

    vector<pair<int, int>> vs(v);
    for (int i = 0; i < v; ++i) {
        cin >> vs[i].first;
        vs[i].second = i;
    }

    sort(vs.begin(), vs.end());

    vector<int> ans(v, -1);
    for (int i = 0, j = 0; i < v && j < p; ++j) {
        if (vs[i].first == ds[j].first || vs[i].first == ds[j].second) {
            ans[vs[i].second] = (ds[j].id);
            ++i;
        }
    }

    bool possible = true;
    for (int i : ans) {
        possible &= i != -1;
    }

    if (possible) {
        for (int i : ans) {
            cout << i << endl;
        }

    } else {
        cout << "impossible" << endl;
    }
    return 0;
}
