#include <bits/stdc++.h>
using namespace std;

class SparseTable {
    private:
        vector<int> A, L2;
        vector<vector<int>> SpT; //SpT[by 2^i][from j]

    public:
        SparseTable(vector<int> &A):A(A) {
            int n = A.size();
            int logn = static_cast<int>(log2(n)) + 1;
            L2.assign(1 << logn, 0);
            SpT.assign(logn, vector<int>(n, 0));

            for (int i = 0; i < logn; ++i)
                L2[(1<<i)] = i;
            
            for (int i = 2; i < L2.size(); ++i) {
                if (L2[i] == 0) {
                    L2[i] = L2[i - 1];
                }
            }

            for (int i = 0; i < n; ++i) {
                SpT[0][i] = i;
            }

            for (int i = 1; (1 << i) <= n; ++i) {
                for (int j = 0; j + (1<<i) - 1 < n; ++j) {
                    int x = SpT[i - 1][j];
                    int y = SpT[i - 1][j + (1 << (i - 1))];
                    SpT[i][j] = A[x] >= A[y] ? x : y;
                }
            }
        }

        int rmq(int x, int y) {
            int k = L2[y - x + 1];
            return max(A[SpT[k][x]], A[SpT[k][y - (1 << k) + 1]]);
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