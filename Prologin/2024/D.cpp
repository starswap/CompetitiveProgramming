#include <bits/stdc++.h>
using namespace std;

void resoudre(vector<int>& A, int N, int R, int K) {
    if (K != 1) { // sinon rien n'arrive
        // R = min(R, (N + (K - 2)) / (K - 1));
        multiset<int> batiments;
        for (int i = 0; i < K; ++i) {
            batiments.insert(A[i % N]);
        }
        if (K >= N) {
            for (int i = 0; i < N ; ++i) {
                A[i] = *batiments.rbegin();
            } 
        } else {
            int aPtr = K % N;
            for (int n = 0; n < R; ++n) {
                int old = A[n % N];
                A[n % N] = *batiments.rbegin();
                batiments.insert(A[aPtr % N]);
                batiments.erase(batiments.find(old));
                aPtr++;
            }
        }
    }
}

int main() {
    int N, R, K;
    cin >> N >> R >> K;
    vector<int> A(N);
    for (int n = 0; n < N; ++n) {
        cin >> A[n];
    }

    resoudre(A, N, R, K);    
    for (int i = 0; i < N - 1; ++i) {
        cout << A[i] << " ";
    }
    cout << A[N - 1] << endl;

    return 0;
}