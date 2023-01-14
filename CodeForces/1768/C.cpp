#include <bits/stdc++.h>
using namespace std;


set<int>::iterator oneBeforeLB(const set<int> &s, int t) {
    if (*s.lower_bound(t) == t) { return s.lower_bound(t);}
    else if (s.lower_bound(t) == s.begin()) {return s.end();}
    else {
        return prev(s.lower_bound(t));
    }
}


int main() {
    int T;
    cin >> T;

    for (int t=0;t<T;++t) {
        int N;
        cin >> N;
        vector<int> a(N,0);
        multimap<int,int> locations;
        for (int n=0;n<N;++n) {
            cin >> a[n];
            locations.emplace(a[n],n);
        } 


        set<int> unusedA;
        set<int> unusedB;
        for (int i=1;i<=N;++i) {
            unusedA.insert(i);
            unusedB.insert(i);
        }
        vector<int> p(N,0);
        vector<int> q(N,0);
        bool fail = false;
        for (auto [maxi, ind] : locations) {
            if (unusedA.contains(maxi) && oneBeforeLB(unusedB,maxi) != unusedB.end()) {
                p[ind] = maxi;
                unusedA.erase(maxi);
                q[ind] = *unusedB.begin();
                unusedB.erase(unusedB.begin());
            }
            else if (unusedB.contains(maxi) && oneBeforeLB(unusedA,maxi) != unusedA.end()) {
                p[ind] = *unusedA.begin();
                unusedA.erase(unusedA.begin());
                q[ind] = maxi;
                unusedB.erase(maxi);
            }
            else {
                fail = true;
                break;
            }
        }
        if (fail) {
            cout << "NO" << endl;
        }
        else {
            cout << "YES" << endl;
            for (int v : p) cout << v << " ";
            cout << endl;
            for (int v : q) cout << v << " ";
            cout << endl;
        }


    }
    return 0;
}
