#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M;
        cin >> N >> M;
        vector<int> A(N);
        vector<int> B(M);
        for (int n = 0; n < N; ++n) {
            cin >> A[n];
        }
        for (int m = 0; m < M; ++m) {
            cin >> B[m];
        }

        // 2020s problems will likely only accept O(n log k) solution
        // new limit: n can be up to 200K
        int k = 0, lis_end = 0;
        vi L(N, 0), L_id(N, 0);

        for (int i = 0; i < N; ++i) {                  // O(n)
            int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
            L[pos] = A[i];                               // greedily overwrite this
            L_id[pos] = i;                               // remember the index too
            if (pos == k) {                              // can extend LIS?
                k = pos+1;                                 // k = longer LIS by +1
                lis_end = i;                               // keep best ending i
            }
        }

        int best_lis_len = k;

        k = 0, lis_end = 0;
        L.assign(N, 0), L_id.assign(N, 0);

        vector<int> key_idx; 

        for (int i = 0; i < N; ++i) {                  // O(n)
            int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
            L[pos] = A[i];                               // greedily overwrite this
            L_id[pos] = i;                               // remember the index too
            if (pos >= k - 1) {                              // can extend LIS?
                k = pos+1;                                 // k = longer LIS by +1
                lis_end = i;                               // keep best ending i
                if (k == best_lis_len) {
                    key_idx.push_back(i);
                }
            }
        }

        sort(B.begin(), B.end());
        reverse(B.begin(), B.end());
        int B_pt = 0;
        int A_pt = 0;

        vector<int> C;
        
        // put all in from B that are greater than or equal to key_idx[key_idx_pts]
        // then put in all from A up to that points
        for (int key_idx_pts = 0; key_idx_pts < key_idx.size(); ++key_idx_pts) {
            while (B[B_pt] >= A[key_idx[key_idx_pts]] && B_pt < M) {
                C.push_back(B[B_pt]);
                B_pt++;
            }
            for (int i = A_pt; i <= key_idx[key_idx_pts]; ++i) {
                C.push_back(A[i]);
            }
            A_pt = key_idx[key_idx_pts] + 1;
        }

        for (int i = A_pt; i < N; ++i) {
            C.push_back(A[i]);
        }

        for (int i = B_pt; i < M; ++i) {
            C.push_back(B[i]);
        }




        for (int i = 0; i < N + M; ++i) {
            cout << C[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
