#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

class SparseTable {                              // OOP style
private:
  vi A, P2, L2;
  vector<vi> SpT;                                // the Sparse Table
public:
  SparseTable() {}                               // default constructor

  SparseTable(vi &initialA) {                    // pre-processing routine
    A = initialA;
    int n = (int)A.size();
    int L2_n = (int)log2(n)+1;
    P2.assign(L2_n, 0);
    L2.assign(1<<L2_n, 0);
    for (int i = 0; i <= L2_n; ++i) {
      P2[i] = (1<<i);                            // to speed up 2^i
      L2[(1<<i)] = i;                            // to speed up log_2(i)
    }
    for (int i = 2; i < P2[L2_n]; ++i)
      if (L2[i] == 0)
        L2[i] = L2[i-1];                         // to fill in the blanks

    // the initialization phase
    SpT = vector<vi>(L2[n]+1, vi(n));
    for (int j = 0; j < n; ++j)
      SpT[0][j] = j;                             // RMQ of sub array [j..j]

    // the two nested loops below have overall time complexity = O(n log n)
    for (int i = 1; P2[i] <= n; ++i)             // for all i s.t. 2^i <= n
      for (int j = 0; j+P2[i]-1 < n; ++j) {      // for all valid j
        int x = SpT[i-1][j];                     // [j..j+2^(i-1)-1]
        int y = SpT[i-1][j+P2[i-1]];             // [j+2^(i-1)..j+2^i-1]
        SpT[i][j] = A[x] >= A[y] ? x : y;
      }
  }

  int rmq(int i, int j) {
    int k = L2[j-i+1];                           // 2^k <= (j-i+1)
    int x = SpT[k][i];                           // covers [i..i+2^k-1]
    int y = SpT[k][j-P2[k]+1];                   // covers [j-2^k+1..j]
    return A[x] >= A[y] ? A[x] : A[y];
  }
};



int main() {
    int N;
    cin >> N;

    vector<vector<int>> rows(2, vector<int>(N));
    vector<int> weights;

    map<int, int> needToLift; // map it to the row we first found it on - so that we know if we found it again on the same row. It's a way of determining which ones are split across rows as we definitely have to lift them.
    map<int, vector<pair<int,int>>> locations; // will always contain a vector of length 2.

    for (int r = 0; r < 2; ++ r) {
        for (int i = 0; i < N; ++i) {
            cin >> rows[r][i];
            if (needToLift.count(rows[r][i]) && needToLift[rows[r][i]] == r) { // already exists and same row
                needToLift.erase(rows[r][i]); // don't necessarily need to lift it as same row
            } else {
                needToLift[rows[r][i]] = r;
                weights.push_back(rows[r][i]); // different row or first time encountering; assume need to lift
            }
            locations[rows[r][i]].push_back(make_pair(r, i));
        }
    }
    
    sort(weights.begin(), weights.end(),greater<int>());

    // For RMaxQs.
    vector<SparseTable> vs;
    for (int r = 0; r < 2; ++r) {
        vs.push_back(SparseTable(rows[r]));
    }
    // cout << "built" << endl;

    bool done = false;
    for (int w : weights) { // iterate downwards over the weights
        if (needToLift.count(w)) { // already determined that we need to lift this one
            cout << w << endl;
            done = true;
            break;
        } else {
            auto [row, col1] = locations[w][0];
            auto [row2, col2] = locations[w][1];

            // largest weight in between
            int maxi = vs[row].rmq(min(col1, col2) + 1, max(col1, col2) - 1);
            if (maxi > w) { // is heavier than this one which means we need to lift this one around it, covers the 2 4 4 2 case
                cout << w << endl;
                done = true;
                break;
            } else { // is lighter than this one so in order to roll this one we'll need to move it.
                needToLift[maxi] = row;
            }
        }
    }

    if (!done) {
        cout << 0 << endl;
    }

    return 0;
}