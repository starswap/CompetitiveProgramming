#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
vector<string> vs[21];

int main() {
    int N;
    cin >> N;

    set<string> words;
    for (int n = 0; n < N; ++n) {
        string s; cin >> s;
        vs[s.size()].push_back(s);
        assert(!words.count(s));
        words.insert(s);
    }

    map<pair<string, string>, int> ans_counts;

    for (int l = 0; l <= 20; ++l) {
        for (int i = 0; i < vs[l].size(); ++i) {
            for (int j = i + 1; j < vs[l].size(); ++j) {
                vector<int> non_matching;
                for (int id = 0; id < l; ++id) {
                    if (vs[l][i][id] != vs[l][j][id] && non_matching.size() < 3) {
                        non_matching.push_back(id);
                    }
                }
                if (non_matching.size() == 2 && non_matching[0] + 1 == non_matching[1]) {
                    string s(vs[l][i]);
                    string t(vs[l][j]);

                    for (int id = 0; id < l; ++id) {
                        if (id != non_matching[0] && id != non_matching[1]) {
                            s[id] = '_';
                            t[id] = '_';
                        }
                    }

                    ans_counts[make_pair(min(s, t), max(s, t))]++;
                }
            }
        }
    }

    int a = 0;
    for (const auto &[poss, cnt] : ans_counts) {
        if (cnt == 1) {
            a++;
        }
    }
    cout << a << endl;

    return 0;
}
