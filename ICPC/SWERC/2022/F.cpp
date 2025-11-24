#include <bits/stdc++.h>
using namespace std;

const int max_n = 1e5;

int morn[max_n + 7];
int after[max_n + 7];
int talked[max_n + 7];
int n;

void solve(){
    cin >> n;
    
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        morn[i] = x;
    }
    
    for (int i = 0; i < n; i++){
        int x;
        cin >> x;
        after[i] = x;
    }
    
    for (int i = 0; i <= n; i++) {
        talked[i] = 0;
    }

    int top = n - 1;
    
    for(int i = n - 1; i >= 0; i--){
        // cout << i << " " <<  morn[i] << "\t" << after[top] << " (" << after[top] <<  " talked? " << talked[after[top]] <<  "):\n";
        if(talked[after[top]] == 1){
            cout << top + 1 << "\n";
            return;
        }

        if(morn[i] == after[top]) {
            top--;
            continue;
        }

        talked[morn[i]] = 1;
    }

    cout << top + 1 << "\n";

    return;
}

int main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int t;
    cin >> t;

    while(t--){
        solve();
    }

    return 0;
}


