#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int t=0;t<T;++t) {
        int N;
        cin >> N;
        map<int, int> counts;
        vector<vector<int>> nums(N);
        for (int n=0;n<N;++n) {
            int K;
            cin >> K;
            for (int k=0; k<K; ++k) {
                int f;
                cin >> f;
                nums[n].push_back(f);
                counts[f]++;
            }
        }

        bool fail = true; 
        for (int n=0; n<N; ++n) {
            bool hasUnique = false;
            for (int b : nums[n]) {
                hasUnique = hasUnique || (counts[b] == 1);
            }
            fail = hasUnique && fail; 
        }
        cout << (fail ? "no" : "yes" ) << endl;


    }
    return 0;
}