#include <bits/stdc++.h>
using namespace std;

// Possible iff:
//   - At most one subarray is decreasing
//   - every time we encounter a number larger than the previous one it is a new maximum
//   - the last number in the decreasing subarray is not smaller than the number before the first one.

int main() {
    int N;
    cin >> N;
    vector<int> nums(N + 1,-1);

    int maxi = -1, maxIndex; // maximum seen so far, index of the maximum. 
    int runStart, runEnd; // if a reversible run exists it will be stored here. 

    int decreasingSegments = 0; 
    bool everyIncreaseNewMax = true;
    bool lastOfDecreasingIsLargeEnough = true; 

    bool increasingSegment = true;

    for (int n = 1; n < N + 1; ++n) {
        cin >> nums[n];

        if (nums[n] > nums[n-1]) { // increasing
            if (increasingSegment == false) { // just started a new increasing segment
                runStart = maxIndex; // the decreasing segment is bounded by the previous maximum
                runEnd = n - 1; // and the one before this element
                if (nums[n-1] < nums[maxIndex - 1]) { // for it to be valid we need the smallest item of the decreasing sequence to be larger than the one it will follow after reversal
                    lastOfDecreasingIsLargeEnough = false;
                }
                increasingSegment = true; // now we are increasing
            }
            if (nums[n] < maxi) { // didn't find a new maximum even though we increased; no good
                everyIncreaseNewMax = false; 
                break;
            } else if (nums[n] > maxi) { // found a new maximum; update
                maxi = nums[n];
                maxIndex = n;
            }
        } else if (nums[n] < nums[n-1]) { // decreasing
            if (increasingSegment) { // started a new decreasing segment
                increasingSegment = false;
                decreasingSegments++; // count them up
            }
        }
    }

    // One final check at the end - if we were decreasing we need to track the decreasing segment ending at the end.
    if (increasingSegment == false) {
        runStart = maxIndex;
        runEnd = N;
        if (nums[N] < nums[maxIndex - 1]) {
            lastOfDecreasingIsLargeEnough = false;
        }
    }

    bool valid = lastOfDecreasingIsLargeEnough && everyIncreaseNewMax;
    if (valid && decreasingSegments == 0) { // all increasing - can just reverse a single number
        cout << "1 1" << endl;
    }
    else if (valid && decreasingSegments == 1) { // one decreasing segment and works if we switch it
        cout << runStart << " " << runEnd << endl;
    } else { // invalid or too many decreasing segments
        cout << "impossible" << endl;
    }
    return 0;
}