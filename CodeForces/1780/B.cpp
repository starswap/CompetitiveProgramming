#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    for (int t=0; t<T; t++) {
        int N; cin >> N;
        
        long long sum = 0; 
        vector<int> nums(N);
        for (int n = 0; n < N; ++n) {
            cin >> nums[n];
            sum += (long long) nums[n];
        }

        long long left = 0;
        long long best = 0;
        for (int i = 0; i < N - 1; ++i) {
            left += (long long) nums[i];
            long long right = sum - left;
            best = max(best, __gcd(left, right));
        }

        cout << best << endl;

    }
        
}