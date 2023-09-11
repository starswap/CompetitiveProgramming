#include <bits/stdc++.h>
using namespace std;

int main() {
    int N,K;
    cin >> N >> K;
    map<string, int> attr_to_index;
    vector<int> attr_score(N);

    for (int i = 0; i < N; ++i) {
        string name; int amt;
        cin >> name >> amt;
        attr_to_index[name] = i;
        attr_score[i] = amt;
    }

    int L;
    cin >> L;
    vector<pair<int, int>> events(L);
    vector<int> max_thresh(N, 0);
    vector<int> max_occurs(N, 0);
    vector<int> total_occurs(N, 0);

    for (int l = 0; l < L; ++l) {
        string attr; int thresh;
        cin >> attr >> thresh;
        int idx = attr_to_index[attr];
        events[l] = make_pair(idx, thresh);
        if (thresh > max_thresh[idx]) {
           max_thresh[idx] = thresh; 
           max_occurs[idx] = 1;
        } else if (thresh == max_thresh[idx]) {
            max_occurs[idx]++;
        }
        total_occurs[idx]++;
    }

    long long needs = 0;
    for (int i = 0; i < N; ++i) {
        if (max_thresh[i] > attr_score[i]) needs += max_thresh[i] - attr_score[i];
    }

    if (needs > K) {
        cout << 0 << endl;
    } else {
        int remaining = K - needs; 
        priority_queue<pair<long long, int>> amt_avail;
        long long curr_score = 0;
        vector<bool> first(N, true);

        for (int i = 0; i < N; ++i) {
            int other_occur = total_occurs[i] - max_occurs[i];
            if (attr_score[i] > max_thresh[i]) {
                first[i] = false;
                amt_avail.emplace(total_occurs[i], i);
                curr_score += (long long) attr_score[i] * (long long) total_occurs[i];
            } else {
                long long score_delta = ((long long) (max_thresh[i] + 1)) * (long long) max_occurs[i] + (long long) other_occur;
                amt_avail.emplace(score_delta, i);
                curr_score += (long long) max_thresh[i] * (long long) other_occur;
            }
        }

        bool done = false;
        long long last_delta = 0;
        while (remaining > 0 && !done) {
            auto [delta, i] = amt_avail.top(); amt_avail.pop();
            done = !first[i];
            first[i] = false;
            curr_score += delta;
            last_delta = delta;
            amt_avail.emplace(total_occurs[i], i);
            remaining--;
        }

        curr_score += (long long) remaining * last_delta;
        cout << curr_score << endl;
    }

    return 0;
}