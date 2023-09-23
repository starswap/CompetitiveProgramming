#include <bits/stdc++.h>
using namespace std;

int main() {
    int K; cin >> K;
    vector<int> process;
    for (int k = 0; k < K; ++k) {
        int N;
        cin >> N;
        vector<int> heights(N);
        multiset<int> before;
        multiset<int> after;
        for (int n = 0; n < N; ++n) {
            cin >> heights[n];
            after.insert(heights[n]);
        }
        for (int n = 0; n < N - 1; ++n) {
            auto aliceIt = before.upper_bound(heights[n]);
            if (aliceIt != before.end() && *aliceIt < *prev(after.end())) {
                process.push_back(k + 1);
                break;
            }
            after.erase(after.find(heights[n]));
            before.insert(heights[n]);
        }
    }

    cout << process.size() << endl;
    for (int s : process) {
        cout << s << endl;
    }
    return 0;
}