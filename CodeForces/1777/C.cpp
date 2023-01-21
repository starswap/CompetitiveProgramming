#include <bits/stdc++.h>
using namespace std;

int N, M;

vector<int> fact(int N) {
    vector<int> ans;
    int i = 1;
    while (i*i <= N && i <= M) {
        if (N % i == 0) {
            ans.push_back(i);
            if (i * i != N && N / i <= M ) {
                ans.push_back(N / i);
            }
        }
        i++;
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        cin >> N;
        cin >> M;
        vector<int> nums(N);
        for (int n=0;n<N;++n) {
            cin >> nums[n];
        } 

        
        sort(nums.begin(), nums.end());
        int l = 0;
        int r = -1;
        int numMissingFactors = M;
        vector<int> counts(M+1, 0);

        int bestTeam = 10000000;
        while (l < N) {
            if (numMissingFactors == 0) {
                if (r != -1)
                   bestTeam = min(bestTeam, nums[r] - nums[l]);
                for (int fact : fact(nums[l])) {
                    if (counts[fact] == 1) {
                        numMissingFactors += 1;
                    }
                    counts[fact]--;
                }
                l++;
            }
            else {
                if (r < N - 1) {
                    r++;
                    for (int fact : fact(nums[r])) {
                        if (counts[fact] == 0) {
                            numMissingFactors -= 1;
                        }
                        counts[fact]++;
                    }
                }
                else {
                    if (bestTeam == 10000000) {
                        bestTeam = -1;
                    }
                    break;
                }
            }
        }
        cout <<  bestTeam << "\n";
    } 
    return 0;
}