#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_N = 200005;
vector<int> with1(MAX_N, -1);
vector<pair<int, int>> with2(MAX_N, {-1, -1});
vector<tuple<int, int, int>> with3(MAX_N, {-1, -1, -1});

int main() {
    cin.tie(0)->sync_with_stdio(0);

    for (int i = 1; (i * (i - 1)) / 2< MAX_N; ++i) {
        with1[(i * (i - 1)) / 2] = i;
    }

    for (int i = 1; (i * (i - 1)) / 2< MAX_N; ++i) {
        for (int j = 2; (j * (j - 1)) / 2 + (i * (i - 1)) / 2 < MAX_N; ++i) {
            with2[(i * (i - 1)) / 2 + (j * (j - 1)) / 2] = make_pair(i, j);
        }
    }


    for (int i = 1; (i * (i - 1)) / 2< MAX_N; ++i) {
        for (int j = 1; (j * (j - 1)) / 2 + (i * (i - 1)) / 2 < MAX_N; ++i) {
            for (int k = 1; (j * (j - 1)) / 2 + (i * (i - 1)) / 2 + (k * (k - 1)) / 2 < MAX_N; ++i) {
                with3[(i * (i - 1)) / 2 + (j * (j - 1)) / 2 + (k * (k - 1)) / 2] = make_tuple(i, j, k);
            }
        }
    }

    int T;
    cin >> T;
    bool poss = false;
    vector<int> finals;
    int ones;
    while (T--) {
        ll N, X, Y, S; cin >> N >> X >> Y >> S;
        
        for (int a = 1 ; a * (a - 1) / 2 < MAX_N; ++a) {
            ll LHS = (S - Y * a * (X / Y) - N * (X % Y)) / Y - (a * (a - 1)) / 2;
            if (LHS < 0) break;

            // remaning n - a;
            if (N - a == 0) {
                if (LHS == 0) {
                    poss = true;
                    finals.push_back(a);
                    break;
                }
            } else if (N - a == 1) {
                if (with1[LHS] != -1) {
                    poss = true;
                    finals.push_back(a);
                    finals.push_back(with1[LHS]);
                    break;
                }
            } else if (N - a == 2) {
                if (with2[LHS] != make_pair(-1, -1)) {
                    poss = true;
                    finals.push_back(a);
                    finals.push_back(with2[LHS].first);
                    finals.push_back(with2[LHS].second);
                    break;
                }
            } else if (N - a >= 3) {
                if (with3[LHS] != make_tuple(-1, -1, -1)) {
                    poss = true;
                    finals.push_back(a);
                    finals.push_back(get<0>(with3[LHS]));
                    finals.push_back(get<1>(with3[LHS]));
                    finals.push_back(get<2>(with3[LHS]));
                    for ()
                    break;
                }
            }
        }
        if (poss) {
            cout << "YES" << endl;
            int curr = X;
            for (int i = 0; i < ones; ++i) {
                finals.push_back(1);
            }
            for (int i : finals) {
                for (int j = 0; j < i; ++j) {
                    cout << curr << " ";
                    curr += Y;
                }
                curr = X % Y;
            }
            cout << endl;
        } else {
            cout << "NO" << endl;
        }
        
    }
    return 0;
}   