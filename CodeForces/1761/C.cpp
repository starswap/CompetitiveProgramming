#include <bits/stdc++.h>
using namespace std;
 
vector<unordered_set<int>> sets;
vector<vector<int>> AL;

ostream &operator << (ostream& o, unordered_set<int> s) {
    o << s.size() << " ";
    for (int a : s) {
        o << a + 1 << " ";
    }
    return o;
}

int main() {
    int T;
    scanf("%d",&T);

    for (int t=0;t<T;++t) {
        int N;
        scanf("%d",&N);
        AL.assign(N,vector<int>());
        for (int n=0;n<N;++n) {
            for (int nc=0;nc<N;++nc) {
                char c = ' ';

                while (c != '0' && c != '1')
                    scanf("%c",&c);

                if (c == '1') {
                    AL[n].push_back(nc);
                }
            }
        }
        
        sets.assign(N,unordered_set<int>());
        for (int n=0;n<N;++n) {
            sets[n].insert(n);
            for (int v : AL[n]) {
                sets[v].insert(n);
            }
        }

        for (auto s : sets) {
            cout << s << endl;
        }
    }


}