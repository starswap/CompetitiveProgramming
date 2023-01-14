// bugs initially: not reading all input
// checking if it is not 0 instead of if it is 0

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d",&T);
    for (int t=0;t<T;++t) {
        int n;
        scanf("%d",&n);
        vector<int> bs(n/2);

        set<int> unused;
        for (int i=1;i<=n;++i) {
            unused.insert(i);
        }

        bool fail = false;
        for (int i=0;i<n/2;++i){
            scanf("%d",&bs[i]);
            if (unused.count(bs[i]) == 0) {
                fail = true;
                // break;
            }
            unused.erase(bs[i]);
        }

        vector<int> ps;
        for (int i=n/2-1;i>=0;i--) {
            ps.push_back(bs[i]);
            auto lb = unused.lower_bound(bs[i]);
            if (unused.size() == 0 || lb == unused.begin()) {
                fail = true;
                break;
            }
            else {
                ps.push_back(*(prev(lb)));
                unused.erase(prev(lb)); 
            }
        }

        if (fail) {
            cout << "-1" << endl;
        }
        else {
    
            vector<int>::reverse_iterator it;
            for (it = ps.rbegin();it != prev(ps.rend()); it++) 
                cout << *(it) << " ";
            cout << *it << endl;
        }
        
    }
}