#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    scanf("%d",&N);
    vector<pair<int,int>> levels(N);

    for (int n=0;n<N;++n) {
        int b,p;
        scanf("%d %d",&b,&p);
        levels[n] = make_pair(b,p);
    }

    sort(levels.begin(),levels.end());

    if (N % 2 == 1) {
        cout << "impossible" << endl;
    }
    else {
        int i = 0;
        int j = N-1;
        int B = levels[i].first  + levels[j].first;
        int P = levels[i].second + levels[j].second;
        bool poss = true;

        while (i < j) {
            int B_Prime = levels[i].first  + levels[j].first;
            int P_Prime = levels[i].second + levels[j].second;
            if (B_Prime != B  || P_Prime != P) {
                poss = false;
                break;
            }
            i++;
            j--;
        }
        cout << (poss ? "possible" : "impossible") << endl;
    }
    return 0;
}