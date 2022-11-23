#include <bits/stdc++.h>
using namespace std;

unordered_map<string,double> unitNames;
vector<vector<pair<int,double>>> AL;
unordered_set<int> visited;

double convert(double amt, int u1, int u2) {

    if (u1 == u2) {
        return amt;
    }
    else {
        visited.insert(u1);
        for (auto [v,cost] : AL[u1]) {
            if (!visited.count(v)) {
                double res = convert(amt*cost,v,u2);
                if (res != -1) {
                    return res;
                }
            }
        }
        return -1;
    }
}


int main() {
    int N,Q;
    scanf("%d %d",&N,&Q);
    
    AL.assign(2*N,vector<pair<int,double>>());

    int unitNumber = 0;

    for (int n=0;n<N;++n) {
        string s1_;
        string s2_;
        double amt;
        cin >> amt; // kill "1"
        cin >> s1_;
        cin >> s2_; // kill "="
        cin >> amt; 
        cin >> s2_;

        if (!unitNames.count(s1_)) {
            unitNames.emplace(s1_,unitNumber);
            unitNumber++;   
        }
        if (!unitNames.count(s2_)) {
            unitNames.emplace(s2_,unitNumber);
            unitNumber++;
        }

        AL[unitNames[s1_]].emplace_back(unitNames[s2_],amt);
        AL[unitNames[s2_]].emplace_back(unitNames[s1_],1/amt);

    }

    for (int q=0;q<Q;++q) {
        string s1_;
        string s2_;
        double amt;

        cin >> amt;
        cin >> s1_; // kill "to"
        cin >> s2_;
        cin >> s2_;

        visited.clear();
        cout << setprecision(10);
        double res = convert(amt,unitNames[s1_],unitNames[s2_]);
        if (res == -1) {    
            cout << "impossible" << endl;
        }
        else {
            cout << res << endl;
        }
    }

    return 0;
}