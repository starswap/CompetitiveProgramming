#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

vector<vector<int>> AL;

// CP Book 4
vi hierholzer(int s, int V) {
  vi ans, idx(V, 0), st;
  st.push_back(s);
  set<pair<int, int>> traversed;
  while (!st.empty()) {
    int u = st.back();
    while ((idx[u] < (int)AL[u].size()) && (traversed.count(make_pair(u, AL[u][idx[u]])) || traversed.count(make_pair(AL[u][idx[u]], u)))) {
      ++idx[u];
    }

    if (idx[u] < (int) AL[u].size()) {
      st.push_back(AL[u][idx[u]]);
      traversed.emplace(u, AL[u][idx[u]]);
      ++idx[u];
    }
    else {
      ans.push_back(u);
      st.pop_back();
    }
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

vi tour;
bool euler_tour(int V) {
    vector<int> odd_degree;
    for (int i = 0; i < V; ++i) {
        if (AL[i].size() % 2 == 1) {
            odd_degree.push_back(i);
        }
    }
    if (odd_degree.size() == 2) {
        tour = hierholzer(odd_degree[0], V);
        return true;
    } else if (odd_degree.size() == 0) {
        tour = hierholzer(0, V);
        return true;
    } else {
        return false;
    }
}

vector<bool> vis;
int cc(int u) {
    int ans = 1;
    vis[u] = true;
    for (int v : AL[u]) {
        if (vis[v]) continue;
        ans += cc(v);
    }
    return ans;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N; cin >> N;

    map<string, int> fns;
    map<string, int> lns;
    int fnc = 0;
    int lnc = 0;   
    vector<pair<string, string>> dieux; 
    vector<string> fns_l;
    vector<string> lns_l;
    for (int n = 0; n < N; ++n) {
        string fn, ln; cin >> fn >> ln;
        if (!fns.count(fn)) {
            fns[fn] = fnc++;
            fns_l.push_back(fn);
        }
        if (!lns.count(ln)) {
            lns[ln] = lnc++;
            lns_l.push_back(ln);
        }
        dieux.emplace_back(fn, ln);
    }

    int V = fns.size() + lns.size();
    int F = fns.size();
    AL.assign(V, vector<int>());
    for (auto [fn, ln] : dieux) {
        AL[fns[fn]].push_back(F + lns[ln]);
        AL[F + lns[ln]].push_back(fns[fn]);
    }

    vis.assign(V, false);
    if (cc(0) == V && euler_tour(V)) {
        for (int i = 0; i < tour.size() - 1; ++i) {
            int fn_i = min(tour[i], tour[i + 1]);
            int ln_i = max(tour[i], tour[i + 1]) - F;
            cout << fns_l[fn_i] << " " << lns_l[ln_i] << endl;
        }
    } else {
        cout << "IMPOSSIBLE" << endl;
    }

    return 0;
}