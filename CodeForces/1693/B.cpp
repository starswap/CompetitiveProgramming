#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 200000;
int p[MAX_N + 2];
int l[MAX_N + 2];
long long r[MAX_N + 2];
vector<vector<int>> AL;
int N;

pair<int,int> solve(int u) {
    long long rSum = 0;
    int num = 0;
    for (int child : AL[u]) {
        auto [subR, subNum] = solve(child);
        rSum += subR;
        num += subNum;
    }
    rSum = min(r[u], rSum);

    if (rSum < l[u]) {
        num += 1;
        rSum = r[u];
    }
    return make_pair(rSum,num);
}


int main() {
    int T;
    scanf("%d", &T);
    for (int t = 0; t < T; t++) {
        scanf("%d", &N);
        AL.assign(N+1,vector<int>());

        for (int n = 2; n < N + 1; ++n) {
            scanf("%d", &p[n]);
            AL[p[n]].push_back(n);
        }
        
        for (int n = 1; n <= N; ++n) {
            scanf("%d", &l[n]);
            scanf("%lld", &r[n]);
        }


        printf("%d\n", solve(1).second);

    }

}