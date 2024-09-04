#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; 
    cin >> N;
    vector<int> strengths(N);
    for (int n = 0; n < N; ++n) {
        cin >> strengths[n];
    }
    sort(strengths.begin(), strengths.end());
    reverse(strengths.begin(), strengths.end());
    
    long long score = 0;
    for (int i = 1; i < N / 3 * 2; i += 2) {
        score += strengths[i];
    }

    cout << score << endl;
    
    return 0;
}