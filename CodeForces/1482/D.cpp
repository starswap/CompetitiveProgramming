#include <bits/stdc++.h>
using namespace std;

template <class T>
typename list<T>::iterator cycle(const typename list<T>::iterator i, list<T>& cont) {
    if (i == cont.end()) {
        return cont.begin();
    }
    else {
        return i;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;

    for (int t=0;t<T;++t) {
        int N;
        cin >> N;
        vector<int> nums(N);
        for (int n=0; n<N; n++) {
            cin >> nums[n];
        }

        int groupStart = 0;
        list<pair<int,int>> groups;
        for (int n=0;n<N-1;++n) {
            if (__gcd(nums[n],nums[n+1]) == 1) { // end of group at n;
                groups.emplace_back(groupStart, n);
                groupStart = n+1;
            }
        }
        if (__gcd(nums[N-1], nums[0]) == 1) {
            groups.emplace_back(groupStart, N-1);
        }
        else {
            if (groups.size() > 0) {
                auto [l1, r1] = groups.front();
                groups.pop_front();
                groups.emplace_front(groupStart, r1);
            }
            else {
                groups.emplace_back(0, N-1);
            }
        }

        vector<int> deleted;
        list<pair<int,int>>::iterator curr = groups.begin();

        set<int> numsPresent; // need this to skip to the next number when a group is not contiguous in the original array. Example: 7 5 7 - delete 5 and merge the 7s. Then the group is 0, 2 exclusive. So if you delete 0 it needs to become 2,2 not 1,2.
        for (int i=0;i<N;++i) {
            numsPresent.insert(i);
        }


        while (groups.size() > 1) {
            list<pair<int,int>>::iterator nextP = cycle(next(curr), groups);
            auto &[l1, r1] = *curr;
            auto &[l2, r2] = *nextP;
            
            int newL2;

            if (numsPresent.lower_bound(l2 + 1) == numsPresent.end()) { //wraps
                newL2 = *numsPresent.begin(); 
            }
            else {
                newL2  = *numsPresent.lower_bound(l2 + 1);
            }

            deleted.push_back(l2);
            numsPresent.erase(l2);
            if ((r2 - l2) % N == 0) { // group is now empty
                auto it = groups.erase(nextP);
                auto nextGroup = cycle(it, groups);
                auto &[l3, r3] = *nextGroup;

                if (__gcd(nums[r1], nums[l3]) != 1) { 
                    r1 = r3;
                    groups.erase(nextGroup);
                }
                else {
                    curr = nextGroup; 
                }
            }
            else if (__gcd(nums[r1], nums[newL2]) == 1) { // separate groups
                l2 = newL2;
                curr = nextP;
            }
            else { // join the groups together
                r1 = r2;
                groups.erase(nextP);
            }            
        }

        if (groups.size() > 0) {
            int l = groups.front().first;
            int r = groups.front().second;
            while (__gcd(nums[l], nums[r]) == 1) {
                deleted.push_back(l);
                if (l == r) break;
                numsPresent.erase(l);

                if (numsPresent.lower_bound(l + 1) == numsPresent.end()) { //wraps
                    l = *numsPresent.begin(); 
                }
                else {
                    l  = *numsPresent.lower_bound(l + 1);
                }
                l = l % N;
            }
        }

        cout << deleted.size() << " ";
        for (int del : deleted) {
            cout << del + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}