#include <bits/stdc++.h>
using namespace std;

const int MAX_ITER = 200;
const int MAX_ITER_IN = 20000;

int random(int l, int u) {
    return rand() % (u - l + 1) + l;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    srand(time(0));

    int M;
    cin >> M;

    vector<int> shorts, talls, mentors(M);
    for (int m = 0; m < M; ++m) {
        int tall, mentor;
        cin >> tall >> mentor;
        (tall ? talls : shorts).push_back(m); 
        mentors[m] = mentor - 1;
    }

    vector<int> ans;
    for (int k = 0; k < MAX_ITER; ++k) {
        ans.clear();
        random_shuffle(shorts.begin(), shorts.end());
        for (int i = 0; i < M / 2; ++i) {
            int s = shorts[i], j, t, iters = 0;
            do {
                j = random(i, M / 2 - 1);
                t = talls[j];
                iters++;
            } while (((mentors[t] == s) || (mentors[s] == t)) && iters != MAX_ITER_IN);
            if ((mentors[t] == s) || (mentors[s] == t)) {
                break;
            } else {
                talls[j] = talls[i];
                talls[i] = t;
                ans.push_back(t);
            }
        }
        if (ans.size() == M / 2) break;
    }
    if (ans.size() == M / 2) {
        for (int x : ans) {
            cout << x + 1 << " ";
        }
        cout << endl;
        for (int x : shorts) {
            cout << x + 1 << " ";
        }
        cout << endl;
    } else {
        cout << "impossible" << endl;
    }
    return 0;
}
