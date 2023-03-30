#include <bits/stdc++.h>
using namespace std;

int main() {
    int H, L;
    cin >> H >> L;
 
    vector<int> itinerary(L);

    for (int i = 0; i < L; ++i) {
        cin >> itinerary[i];
        itinerary[i]--;
    }

    int currHat = itinerary[0];
    vector<int> standHits(H, 0);
    vector<int> hatLoc(H, 0);
    for (int i = 0 ; i < H; ++i) {
        hatLoc[i] = i;
    }

    for (int i = 1; i < L; ++i) {
        int nextHat = itinerary[i];
        standHits[hatLoc[nextHat]] += 1;
        hatLoc[currHat] = hatLoc[nextHat];
        currHat = nextHat;
    }

    vector<pair<int, int>> standHitsWithIndex(H);
    for (int i = 0 ; i < H; ++i) {
        standHitsWithIndex[i] = make_pair(standHits[i], i);
    }
    sort(standHitsWithIndex.begin(), standHitsWithIndex.end());
    reverse(standHitsWithIndex.begin(), standHitsWithIndex.end());

    // sort(standHitsWithIndex.rbegin(), standHitsWithIndex.rend());

    long long ans = 0;
    vector<int> res(H-1);
    int k = 0;
    for (int i = 0; i < H; ++i) {
        if (standHitsWithIndex[i].second != itinerary[0]) {
            res[k] = standHitsWithIndex[i].second + 1;
            k++;
            ans += static_cast<long long>(k) * static_cast<long long>(standHitsWithIndex[i].first);
        }
    }

    cout << ans << endl;
    int i = 0;
    for (i = 0 ; i < H - 2; ++i) {
        cout << res[i] << " ";
    }
    if (H -2 >= 0) {
        cout << res[i] << endl;
    }
    
    return 0;
}