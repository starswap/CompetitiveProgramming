#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    for (int t=0;t<T;++t) {
        int n;
        cin >> n;
        vector<int> A(n);
        vector<int> B(n);
        for (int i=0;i<n;++i) {
            cin >> A[i];
        }
        for (int i=0;i<n;++i) {
            cin >> B[i];
        }
        int m;
        cin >> m;
        vector<int> R(m);
        for (int i=0;i<m;++i) {
            cin >> R[i];
        }


        // cout << "solving" << endl;

        bool fail = false;

        for (int i=0;i<n;++i) {
            fail = fail || (B[i] > A[i]);
        }
        if (!fail) {
            map<int,vector<int>> indexMap;
            map<int,int> razorCounts;
            for (int i=0;i<n;++i) {
                indexMap[B[i]].push_back(i);
            }
            for (int i=0;i<m;++i) {
                if (!razorCounts.count(R[i])) razorCounts[R[i]] = 1;
                else {
                    razorCounts[R[i]]++;
                }
            }

            // cout << "H" << endl;

            set<int> blockedIndices;
            for (auto it = indexMap.rbegin(); it != indexMap.rend(); it++) {
                auto [hair, indices] = *it;
                vector<int> indicesNoSameHeight;
                int razorsNeeded = indices.size();
                for (int i=0;i<static_cast<int>(indices.size());++i) {
                    int id = indices[i];
                    if (A[id] == B[id]) razorsNeeded--; // don't need to cut if same size before and after
                    else indicesNoSameHeight.push_back(id);
                }

                for (int i=0;i<static_cast<int>(indicesNoSameHeight.size())-1;++i) {
                    int id = indicesNoSameHeight[i];
                    if ( (blockedIndices.lower_bound(id) == blockedIndices.end() || *blockedIndices.lower_bound(id) > indicesNoSameHeight[i+1])) razorsNeeded--;
                }

                // cout << "G" << endl;
                if (razorsNeeded > razorCounts[hair]) {
                    fail = true;
                    break;
                }
                for (int id : indices) blockedIndices.insert(id);
            }
        }

        cout << ((fail) ? "NO" : "YES") << endl;

    }
    return 0;
}


// first check if any of bori's hair needs to grow longer = bad
// map of elements in B to the indices that they are occurring in
// take the unique elements of B, sort them and iterate downwards, starting at the top
// count razors of each type

// have a set of "blockers"
// for each unique target hair height in B:
//    compute number of razors needed as number of occurrences of that height - number of adjacent pairs with no blockers in between
//    add all current ones to blockers
//    if number of razors needed exceeds amount available (fail)
//  success