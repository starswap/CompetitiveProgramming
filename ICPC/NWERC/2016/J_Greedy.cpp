#include <bits/stdc++.h>
using namespace std;

int N, Q, S;

vector<tuple<int, int, int>> constraints; // time, amount, queue
vector<int> sensor_map;
vector<int> queue_size;
vector<int> max_downlink;
vector<vector<int>> queue_gen;

bool solve() {
  vector<int> queue_amt(Q, 0);
  for (int n = 0; n < N; ++n) {
    for (int q = 0; q < Q; ++q) {
      queue_amt[q] += queue_gen[n][q];
      if (queue_amt[q] > queue_size[q]) {
        constraints.emplace_back(n, queue_amt[q] - queue_size[q], q);
      }
    }
  }

  // needs to be empty at the end
  for (int q = 0; q < Q; ++q) {
    constraints.emplace_back(N, queue_amt[q], q);
  }

  sort(constraints.begin(), constraints.end());

  queue_amt.assign(Q, 0);
  for (int n = 0; n < N; ++n) {
    for (int q = 0; q < Q; ++q) {
      queue_amt[q] += queue_gen[n][q];
    }

    int dl_left = max_downlink[n];
    vector<int> dq(Q, 0);
    for (auto &[time, amt, queue] : constraints) {
      amt -= dq[queue]; // from previous ones this time. 

      if (n == time && amt != 0) { // missed this constraint
        return false;
      } else {
        int amount_dl = min(min(dl_left, amt), queue_amt[queue]);
        amt -= amount_dl;
        dl_left -= amount_dl;
        dq[queue] += amount_dl;
        queue_amt[queue] -= amount_dl;
      }
    }      
  }

  for (auto &[time, amt, queue] : constraints) {
    if (amt != 0) { // missed this constraint
      return false;
    }
  }
  return true;
}

int main() {
  cin >> N >> Q >> S;

  // Get the queue that each sensor feeds into
  sensor_map.assign(S, -1);
  for (int s = 0; s < S; ++s) {
    int m; cin >> m;
    sensor_map[s] = m - 1;
  }

  // Get the size of each queue
  queue_size.assign(Q, -1);
  for (int q = 0; q < Q; ++q) {
    cin >> queue_size[q];
  }

  max_downlink.assign(N, -1);
  queue_gen.assign(N, vector<int>(Q, 0));

  for (int n = 0; n < N; ++n) {
    cin >> max_downlink[n];
    for (int s = 0; s < S; ++s) {
      int amt; cin >> amt;
      queue_gen[n][sensor_map[s]] += amt;
    }
  }

  cout << ((solve()) ? "possible" : "impossible") << endl;
  
  return 0;
}
