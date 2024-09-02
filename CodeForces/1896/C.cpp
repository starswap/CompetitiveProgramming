// for the biggest ones in A take the largest that they can beat
#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, X;
        cin >> N >> X;
        vector<pair<int, int>> A(N);
        vector<int> A_orig(N);
        for (int i = 0; i < N; ++i) {
            cin >> A[i].first;
            A[i].second = i;
            A_orig[i] = A[i].first;
        } 
        vector<int> B(N);
        for (int i = 0; i < N; ++i) {
            cin >> B[i];
        }
        sort(A.begin(), A.end());
        sort(B.begin(), B.end());
        reverse(A.begin(), A.end());
        reverse(B.begin(), B.end());
 
        deque<pair<int, int>> Adeque(A.begin(), A.end());
        deque<int> Bdeque(B.begin(), B.end());

        int maxi = 0;
        vector<int> B_matched(N);
        for (int i = 0; i < N; ++i) {
            if (Adeque.front().first > Bdeque.front()) {
                maxi++; 
                B_matched[Adeque.front().second] = Bdeque.front();
                Adeque.pop_front(); 
                Bdeque.pop_front();
            }
            else {
                B_matched[Adeque.back().second] = Bdeque.front();
                Bdeque.pop_front();
                Adeque.pop_back();
            }
        }

        
        int d = maxi - X;
        bool ok = (maxi >= X);
        for (int i = 0; i < d; ++i) {
            int bottom = i;
            int top = maxi - d + i;
            ok &= (B_matched[bottom] >= A_orig[top]);
        }
        cout << (ok ? "YES" : "NO") << endl;
        if (ok) {
            for (int i = d; i < maxi; ++i) {cout << B_matched[i] << " ";}
            for (int i = 0; i < d; ++i) {cout << B_matched[i] << " ";}
            for (int i = maxi;  i < N; ++i) {cout << B_matched[i] << " ";}
            cout << endl;
        }
    }
    return 0;
}