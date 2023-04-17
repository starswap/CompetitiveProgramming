#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<string> nums;

const int MAX_N = 40;
const int MAX_M = 400;
const int MAX_D = 10;
const int INF = 100000000;

int dp[MAX_N][MAX_N][MAX_M][MAX_D];
int bestX[MAX_N][MAX_N][MAX_M][MAX_D];

void initDP() {
    fill(&dp[0][0][0][0], &dp[0][0][0][0] + sizeof(dp) / sizeof(dp[0][0][0][0]), -1);
    fill(&bestX[0][0][0][0], &bestX[0][0][0][0] + sizeof(bestX) / sizeof(bestX[0][0][0][0]), -1);
}

int countNotEqual(int start, int end, int idx, int digit) {
    int score = 0;
    for (int s = start; s <= end; ++s) {
        if (nums[s][idx] != '0' + digit) score++; // need to change it to 9
    }
    return score;
}

// HatSort the numbers between nums[start] and nums[end], from the idx'th digit onwards, where the idx'th digit must be at least digit.  
int sort(int start, int end, int idx, int digit) {
    if (dp[start][end][idx][digit] != -1) return dp[start][end][idx][digit]; // already computed
    else if (idx == M) return 0; // sentinel
    else if (end == start) return (nums[start][idx] - '0' < digit); // sentinel - we only have one number to sort. First digit has to be greater than or equal to digit (so change it if it's not already). Otherwise no changes to be made.
    else if (digit == 9) { // sentinel on digit - all these numbers need to start with a 9
        return dp[start][end][idx][digit] = countNotEqual(start, end, idx, digit) + sort(start, end, idx + 1, 0); // move onto the next space in the number, starting from 0.
    } else {
        int bestx, best = INF;
        for (int x = 0; x <= end - start + 1; x++) { // set the first x to have d as the start digit.
            int score = countNotEqual(start, start + x - 1, idx, digit) // number of changes needed to set the first x to have d as start digit.
                      + ((x > 0) ? sort(start, start + x - 1, idx + 1, 0) : 0) // number of changes needed to sort the remaining M - 1 digits of the first x numbers
                      + ((end >= start + x) ? sort(start + x, end, idx, digit + 1) : 0); // numbers of changes needed to sort the remaining N - X numbers.
            if (score < best) { // new best score
                best = score;
                bestx = x;
            }
        }
        bestX[start][end][idx][digit] = bestx;
        dp[start][end][idx][digit] = best;
        return dp[start][end][idx][digit];
    }  
}

// PRE: Need to run sort(0, N - 1, 0, 0) first in order for this to work.
// Same cases as above.
void buildAnswer(int start, int end, int idx, int digit) {
    if (idx == M) return;
    else if (end == start) {
        if (nums[start][idx] - '0' < digit) // we can't get to the desired digit by advancing from the current digit, so a change will have to be made.
            nums[start][idx] = '0' + digit;
    } 
    else if (digit == 9) {
        for (int s = start; s <= end; ++s)
            nums[s][idx] = '9';
        buildAnswer(start, end, idx + 1, 0);
    } else {
        int x = bestX[start][end][idx][digit];
        for (int s = start; s < start + x; ++s)
            nums[s][idx] = digit + '0';
        if (x > 0)
            buildAnswer(start, start + x - 1, idx + 1, 0);
        if (end >= start + x)
            buildAnswer(start + x, end, idx, digit + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    nums.assign(N, "");
    initDP();

    for (int n = 0; n < N; ++n) {
        cin >> nums[n];
    }
    
    sort(0, N - 1, 0, 0);
    buildAnswer(0, N - 1, 0, 0);
    
    for (int i = 0; i < N; ++i) {
        cout << nums[i] << endl;
    }
    return 0;
}