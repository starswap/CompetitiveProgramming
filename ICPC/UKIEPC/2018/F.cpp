#include <bits/stdc++.h>
using namespace std;

const int MAX_S = 1'000'005;
const int MAX_C = 1'000'005;

int counts[MAX_S];  // Map from token to the count of times it occurs.
map<int, set<int>> countsRev;  // Map from occurrence count to the list of tokens which occur that many times

vector<int> fibSum;   // Sum of the fibonacci numbers up to nth fib;
void makeFibs() {
    int a = 0;
    int b = 1;
    int s = 0;   // fib sum so far
    
    while (b < MAX_C) {
        // Compute sum
        s += b;
        fibSum.push_back(s);
        
        // Update fib
        int temp = b;
        b = a + b;
        a = temp;
    }
}

int fibCodeLength(int c) {
    // Get the length of the nth fib code starting at 1.
    // O(20)
    int l = 1;
    for (int fs : fibSum) {
        l++;
        if (fs >= c) {
            break;
        } 
    }
    return l;
}

int main() {
    makeFibs();

    // Read input
    int N; cin >> N;
    vector<int> nums(N, 0);

    for (int n = 0; n < N; ++n) {
        cin >> nums[n];
    }

    // Maintain partial answer as we go through the tokens
    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int s = nums[i]; // current symbol
        int oldCount = counts[s]; // how many times it occurred before
        counts[s]++; // we've seen it once more
        
        // find ordinal for this symbol - n such that s is now the nth (equal) most used
        //   symbol 
        int sum = 1; // will compute the value we are looking for
        for (auto it = countsRev.rbegin(); it != countsRev.rend(); it++) { // go down the buckets of occurrences
            auto &[count, ref] = *it;
            if (count == oldCount) break; // we only wanted to count the symbols which occur more than the current one
            sum += ref.size();
        }

        countsRev[oldCount].erase(s); // this count no longer has s
        countsRev[oldCount+1].insert(s); // the new count has s
        if (countsRev[oldCount].size() == 0) countsRev.erase(oldCount); // clean up so we don't iterate over lots of empty sets
     
        // General idea - if s previously occurred 10 times and there are 20 symbols occurring more frequently, as s is now going to 11 times, we can assume we assigned s to have the shortest code out of all of those with 10 times. This is code number 21.
        ans += fibCodeLength(sum);
        cout << ans << " ";

    }
    cout << endl;

    return 0;
}