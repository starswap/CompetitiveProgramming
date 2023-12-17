#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<char> s(N);
        multiset<char> letters;
        for (int n = 0; n <N ;++n) {
            cin >> s[n];
            letters.insert(s[n]);
        }

        vector<char> subsequence;
        vector<char> others;
        set<int> seq_i;
        for (int n = 0; n < N; ++n) {
            if (s[n] == *letters.rbegin()) { // in subsequence
                letters.erase(letters.find(s[n]));
                subsequence.push_back(s[n]);
                seq_i.insert(n);
            }
            else { // not in subsequence
                letters.erase(letters.find(s[n]));
                others.push_back(s[n]);
            }
        }

        vector<char> new1(s);
        vector<char> new2(s);
        char prev; //= subsequence[subsequence.size() - 1];
        int ans = subsequence.size();
        int i = 0;
        // for (i = subsequence.size() - 1; i > -1; i--) {
        //     if (prev != subsequence[i]) break;
        //     prev = subsequence[i];
        //     ans -= 1;
        // }
        prev = subsequence[0];
        for (i = 0; i < subsequence.size(); ++i) {
            if (prev != subsequence[i]) break;
            prev = subsequence[i];
            ans -= 1;
        }
        ans = max(0, ans);
        


        sort(subsequence.begin(), subsequence.end());
        sort(new1.begin(), new1.end());
        i = 0;
        for (int n = 0; n < N; ++n) {
            if (seq_i.count(n)) {
                new2[n] = subsequence[i];
                i++;
            }
        }

        bool ok = true;
        for (int i = 0; i < N; ++i) {
            ok &= (new1[i] == new2[i]);
        }

        if (ok) {
            cout << ans << endl;
        } else {
            cout << -1 << endl;
        }
        // check that others are in the correct order.

 

    }
    return 0;
}