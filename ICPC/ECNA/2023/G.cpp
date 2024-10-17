#include <bits/stdc++.h>
using namespace std;

pair<int, int> upR(const pair<int, int>& t, const pair<int, int>& s) {
    return make_pair(t.first - s.first, t.second - s.second);
}

pair<int, int> rightR(const pair<int, int>& t, const pair<int, int>& s) {
    return make_pair(t.first - s.second, t.second + s.first);
}

pair<int, int> downR(const pair<int, int>&t, const pair<int, int>& s) {
    return make_pair(t.first + s.first, t.second + s.second);
}

pair<int, int> leftR(const pair<int, int>& t, const pair<int, int>& s) {
    return make_pair(t.first + s.second, t.second - s.first);
}



pair<int, int> upR_rev(const pair<int, int>& r, const pair<int, int>& s) {
    return make_pair(r.first + s.first, r.second + s.second);
}

pair<int, int> rightR_rev(const pair<int, int>&r, const pair<int, int>&s) {
    return make_pair(r.first + s.second, r.second - s.first);
}

pair<int, int> downR_rev(const pair<int, int>& r, const pair<int, int>& s) {
    return make_pair(r.first - s.first, r.second - s.second);
}

pair<int, int> leftR_rev(const pair<int, int>& r, const pair<int, int>& s) {
    return make_pair(r.first - s.second, r.second + s.first);
}

int main() {
    vector<function<pair<int, int>(const pair<int, int>&, const pair<int, int>&)>> rotations = {upR, leftR, downR, rightR};
    vector<function<pair<int, int>(const pair<int, int>&, const pair<int, int>&)>> rotations_rev = {upR_rev, leftR_rev, downR_rev, rightR_rev};

    int T, S, R; cin >> T >> S >> R;
    vector<pair<int, int>> trees(T);
    set<pair<int, int>> is_tree;
    vector<pair<int, int>> sensor(T);
    for (int t = 0; t < T; ++t) {
        cin >> trees[t].first >> trees[t].second;
        is_tree.insert(trees[t]);
    }

    for (int s = 0; s < S; ++s) {
        cin >> sensor[s].first >> sensor[s].second;
    }

    assert(is_tree.size() == T);

    pair<int, int> ans;
    int cnt = 0;

    for (const auto& tree : trees) {
        for (int ri = 0; ri < 4; ++ri) {
            auto [rx, ry] = rotations[ri](tree, sensor[0]);

            bool ok = !(is_tree.count(make_pair(rx, ry)));
            set<pair<int, int>> seen;
            for (int i = 1; i < S; ++i) {
                const auto t3 = rotations_rev[ri](make_pair(rx, ry), sensor[i]);
                ok &= (is_tree.count(t3));
                if (!ok) break;
                seen.insert(t3);
            }
            seen.insert(tree);

            for (const auto& t2 : trees) {
                int dist = abs(t2.first - rx) + abs(t2.second - ry); 
                if (dist <= R && !seen.count(t2)) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                ans = make_pair(rx, ry);
                cnt++;
            }
        }
    }

    if (cnt == 0) {
        cout << "Impossible" << endl; 
    } else if (cnt >= 2) {
        cout << "Ambiguous" << endl;
    } else {
        cout << ans.first << " " << ans.second << endl;
    }

    return 0;
}