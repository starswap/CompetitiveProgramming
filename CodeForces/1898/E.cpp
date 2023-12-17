#include <bits/stdc++.h>
using namespace std;

const int ALPHA = 26;

int main() {
    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        string s, t;
        cin >> s >> t;
        vector<queue<int>> let_idx(ALPHA);
        // location of letter i in source
        for (int i = 0; i < N; ++i) {
            char c = s[i];
            let_idx[c - 'a'].push(i);
        }

        bool fail = false;
        for (int i = 0; i < M; ++i) {
            char next_letter = t[i];
            if (let_idx[next_letter - 'a'].size() == 0) {fail = true; break;}
            int j = let_idx[next_letter - 'a'].front(); let_idx[next_letter - 'a'].pop();
            
            for (char blocker = next_letter - 1; blocker >= 'a'; blocker--) {
                while (let_idx[blocker - 'a'].size() > 0 && let_idx[blocker - 'a'].front() < j) {
                    let_idx[blocker - 'a'].pop();
                }
            }
        }

        cout << ((fail) ? "NO" : "YES") << endl;

    }   
}