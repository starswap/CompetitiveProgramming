#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> piranhas;
vector<int> target_piranhas;
vector<int> moves;
vector<int> interval_steps;

bool interval_blocked(int curr_interval) {
    bool blocked;
    if (curr_interval == 0) {
        blocked = (piranhas[curr_interval] <= 1);
    } else if (curr_interval == K) {
        blocked = (piranhas[curr_interval - 1] >= N - 2);
    } else {
        blocked = piranhas[curr_interval] - piranhas[curr_interval - 1] <= 3;
    }

    return blocked || interval_steps[curr_interval] == moves[curr_interval];
}

int main() {
    cin >> N >> K;
    
    piranhas.assign(K, -1);
    target_piranhas.assign(K, -1);
    moves.assign(K + 1, 0);

    for (int i = 0; i < K; ++i) {
        cin >> piranhas[i];
        piranhas[i]--;
    }

    for (int i = 0; i < K; ++i) {
        cin >> target_piranhas[i];
        target_piranhas[i]--;
    }
    
    interval_steps.assign(K + 1, 0);
    int acc = 0;
    for (int i = 0; i < K; ++i) {
        interval_steps[i] = acc;
        acc += target_piranhas[i] - piranhas[i];
    }
    interval_steps[K] = acc;

    int mini = *min_element(interval_steps.begin(), interval_steps.end());
    int total_steps = 0;
    for (int i = 0; i < K + 1;++i) {
        interval_steps[i] -= mini;
        total_steps += interval_steps[i];
    }

    int curr_interval = 0;
    while (curr_interval < K + 1) {
        if (interval_blocked(curr_interval)) {
            curr_interval++;
        } else {
            if (curr_interval > 0) {
                piranhas[curr_interval - 1]++; 
             }
            if (curr_interval < K) {
                piranhas[curr_interval]--;
            }
            moves[curr_interval]++;
            if (curr_interval > 0) curr_interval--;
        }
    }

    bool ok = true; 
    for (int i = 0; i < K + 1; ++i) {
        ok &= (moves[i] == interval_steps[i]);
    }
    
    if (ok) {
        cout << total_steps << endl;
    } else {
        cout << "impossible" << endl;
    }
    
    return 0;
}