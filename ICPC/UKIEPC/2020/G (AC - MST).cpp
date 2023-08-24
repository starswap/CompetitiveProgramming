#include <bits/stdc++.h>
using namespace std;

const long long INF = 1'300'000'000'000'000;

int N, M;
vector<int> A;
vector<int> C;
vector<vector<pair<int, long long>>> AL;

long long MST_cost(const vector<vector<pair<int, long long>>>  &AL) {
    auto comp = [](pair<long long, int> a, pair<long long, int> b){ return b.first < a.first;};

    priority_queue<pair<long long, int>, vector<pair<long long, int>>, decltype(comp)> pq(comp);
    vector<long long> costs(N + 1, INF);
    set<int> tree;

    pq.emplace(0, 0);
    costs[0] = 0;

    long long mst_cost = 0;
    
    while (pq.size()) {
        auto [cost, u] = pq.top(); pq.pop();
        if (cost != costs[u]) continue;
        tree.insert(u);
        mst_cost += cost;
        for (auto [v, w] : AL[u]) {
            if (w < costs[v] && !tree.count(v)) {
                costs[v] = w;
                pq.emplace(w, v);
            }
        }
    } 
    return mst_cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;
    A.resize(M);
    C.resize(M);
    AL.resize(N + 1);

    for (int i = 0; i < M; ++i) {
        cin >> C[i] >> A[i];
    }

    for (int i = 0; i < M; ++i) {
        AL[C[i]].emplace_back(0, A[i]);
        AL[0].emplace_back(C[i], A[i]);
    }

    long long cost_to_next;
    for (int i = 1; i < N; ++i) {
        cin >> cost_to_next;
        AL[i].emplace_back(i + 1, cost_to_next);
        AL[i + 1].emplace_back(i, cost_to_next);
    }
    cin >> cost_to_next;
    AL[N].emplace_back(1, cost_to_next);
    AL[1].emplace_back(N, cost_to_next);
    
    long long cost = MST_cost(AL);
    cout << cost << endl;
    return 0;
}