#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

struct slot {
    int tw, wi, dist;
    slot(int tw, int wi):tw(tw), wi(wi) {}
};

struct coin {
    int ma, wi;
    coin(int ma, int wi):ma(ma), wi(wi) {}
};

int S, C;
vector<slot> slots;
vector<coin> coins;

long long solve() {
    sort(coins.begin(), coins.end(), [] (coin c1, coin c2) {return c1.ma < c2.ma;});
    sort(slots.begin(), slots.end(), [] (slot s1, slot s2) {return s1.tw < s2.tw;});

    // widestSoFar is a set of the triggerable slots (i.e. the ones with low enough trigger weight
    //    to be triggered by the current coin) but only the ones which have the highest width so far
    //    since a coin can only drop into a slot which is the widest so far.
    // We are going to need to binary search over this to find the earliest index which holds a slot
    //   wide enough to take the current coin. For this to be efficient we need to be able to get
    //   random access into the set in logn or better, so we use OST (pbds) here. Any data structure
    //   supporting log n or better random access and log n or better insertion would work too. 
    auto comp = [] (int i, int j) {return slots[i].dist < slots[j].dist;};
    tree<int,null_type,decltype(comp),rb_tree_tag,tree_order_statistics_node_update> widestSoFar(comp);

    int s = 0;
    long long ans = 0;

    for (coin co : coins) {

        // Update slots array to include new triggerables
        while (s < S && co.ma >= slots[s].tw) { // triggerable
            auto it = widestSoFar.lower_bound(s);
            while (it != widestSoFar.end() && slots[s].wi > slots[*it].wi) { // while we are wider than the one after
                widestSoFar.erase(it); // remove it as it is no longer the widest so far.
                it = widestSoFar.lower_bound(s); 
            }

            if (widestSoFar.lower_bound(s) == widestSoFar.begin() ||
                slots[s].wi > slots[*prev(widestSoFar.lower_bound(s))].wi) { // we are wider than the previous one
                widestSoFar.insert(s); // insert us as we are the new widest so far.
            }
            s++;
        }

        // Find out where we drop this coin, by binary searching to find the earliest triggerable index which is wide enough
        int L = -1; // not in
        int H = widestSoFar.size() - 1; // in
        while (H - L > 1) {
            int M = (H + L) / 2;
            slot curr = slots[*widestSoFar.find_by_order(M)];
            if (curr.wi >= co.wi) { // large enough
                H = M;
            } else { // not large enough
                L = M;
            }
        }

        // Update answer
        int toDropIdx = *widestSoFar.find_by_order(H);
        ans += slots[toDropIdx].dist;
    }
    return ans;
}

int main() {
    cin >> S;
    slots.assign(S, slot(0, 0));

    for (int s = 0 ; s < S; ++s) {
        int tw, wi;
        cin >> wi >> tw;
        slots[s].wi = wi;
        slots[s].tw = tw;
        slots[s].dist = s + 1;
    }

    cin >> C;
    coins.assign(C, coin(0, 0));
    for (int c = 0 ; c < C; ++c) {
        int ma, wi;
        cin >> wi >> ma;
        coins[c].wi = wi;
        coins[c].ma = ma;
    }

    cout << solve() << endl;

    return 0;
}
