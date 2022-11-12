#include <bits/stdc++.h>
using namespace std;

int main() {
    int w;
    long long h;

    scanf("%d %lld",&w,&h);

    vector<int> towers(w);
    for (int n=0;n<w;++n) {
        towers[n] = n+1;
    }
    random_shuffle(towers.begin(),towers.end());
    
    long long best = 0;
    int bestBuilding = 1;
    
    for (int building : towers) {
        if (best == h) {
            break;
        }
        printf("? %d %lld\n",building,best+1);
        fflush(stdout);

        string res;
        cin >> res;    
        if (res == "sky") {
            continue;
        }


        long long minn = best; // included
        long long maxx = h+1; //not included
        
        while (maxx - minn > 1) {
            long long mid = (maxx + minn) / 2; 
            printf("? %d %lld\n",building,mid);
            fflush(stdout);

            string res;
            cin >> res;
            if (res == "sky") {
                maxx = mid;
            }
            else if (res == "building") {
                minn = mid;
            }
        }
        if (minn > best) {
            best = minn;
            bestBuilding = building;
        }
    }
    printf("! %d %lld",bestBuilding,best);
    fflush(stdout);

    return 0;


}