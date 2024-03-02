#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

vector<int> match;
vector<bool> vis;

int Aug(int L, const vector<vector<int>> &AL) {
  if (vis[L]) return 0;                          // L visited, return 0
  vis[L] = 1;
  for (auto &R : AL[L])
    if ((match[R] == -1) || Aug(match[R], AL)) {
      match[R] = L;                              // flip status
      return 1;                                  // found 1 matching
    }
  return 0;                                      // no matching
}

// Estimated O(V^2 + kE) where k is smallish
int AugPathPP(const vector<vector<int>> &AL, int Vleft) {
  // Left is 0..Vleft-1. Right is Vleft..V-1
  int V = AL.size();
  unordered_set<int> freeV;
  for (int L = 0; L < Vleft; ++L) freeV.insert(L);
  match.assign(V, -1);
  int MCBM = 0;
  for (int L = 0; L < Vleft; ++L) {              // O(V+E)
    vi candidates;
    for (auto &R : AL[L])
      if (match[R] == -1)
        candidates.push_back(R);
    if ((int)candidates.size() > 0) {
      ++MCBM;
      freeV.erase(L);                            // L is matched
      int a = rand()%(int)candidates.size();     // randomize this
      match[candidates[a]] = L;
    }
  }                                              // for each free vertex
  for (auto &f : freeV) {                        // (in random order)
    vis.assign(Vleft, 0);                        // reset first
    MCBM += Aug(f, AL);                              // try to match f
  }
  return MCBM;    // the answer is 2 for Figure 4.38
}


int main() {
    ios_base::sync_with_stdio(0);
    int N, M;
    cin >> N >> M;
    vector<vector<int>> AL(N + M, vector<int>());    
    for (int n = 0; n < N; ++n) {
        int C; cin >> C;
        for (int c = 0; c < C; ++c) {
            int col; cin >> col; col--;
            AL[N + col].push_back(n);
            AL[n].push_back(N + col);
        }
    }
    cout << AugPathPP(AL, N) << endl;
    return 0;
}
