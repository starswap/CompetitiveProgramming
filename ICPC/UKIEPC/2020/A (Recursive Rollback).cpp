#include <bits/stdc++.h>
using namespace std;

int N, K;
vector<int> piranhas;
vector<int> target_piranhas;
vector<int> moves;

bool interval_done(int curr_interval) {
    bool done;
    if (curr_interval == 0) {
        done = piranhas[curr_interval] == target_piranhas[curr_interval];
    } else if (curr_interval == K) {
        done = piranhas[curr_interval - 1] == target_piranhas[curr_interval - 1];
    } else {
        done = piranhas[curr_interval] == target_piranhas[curr_interval]  && piranhas[curr_interval - 1] == target_piranhas[curr_interval - 1];
    }

    return done;
}

bool interval_blocked(int curr_interval) {
    bool blocked;
    if (curr_interval == 0) {
        blocked = (piranhas[curr_interval] <= 1);
    } else if (curr_interval == K) {
        blocked = (piranhas[curr_interval - 1] >= N - 2);
    } else {
        blocked = piranhas[curr_interval] - piranhas[curr_interval - 1] <= 3;
    }

    return blocked;
}

void finger_interval(int curr_interval) {
    if (curr_interval > 0) {
        piranhas[curr_interval - 1]++; 
    }
    if (curr_interval < K) {
        piranhas[curr_interval]--;
    }
    moves[curr_interval]++;
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
    
    for (int interval = 0; interval < K + 1; ++interval) {
        if (!interval_done(interval)) {
            int old_interval = interval;
            while (interval_blocked(interval)) {
                interval--;
            }
            
            if (interval < 0) {
                interval = old_interval;
                continue;
            }

            for (; interval <= old_interval; ++interval) {
                finger_interval(interval);
            }

            interval = -1;
        }
    }

    int mini = *min_element(moves.begin(), moves.end());
    int total_steps = 0;
    for (int i = 0; i < K + 1;++i) {
        moves[i] -= mini;
        total_steps += moves[i];
    }

    bool success = true;
    for (int i = 0; i < K; ++i) {
        success &= piranhas[i] == target_piranhas[i];
    }

    if (success) {
        cout << total_steps << endl;
    } else {
        cout << "impossible" << endl;
    }
    
    return 0;
}