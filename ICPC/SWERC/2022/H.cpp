#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n;
    cin >> n;
    
    long long plus = 0, minus = 0;
    
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if(c == '+') {
            plus++;
        }
        else{
            minus++;
        }
    }
    
    int k;
    cin >> k;
    for (int i = 0; i < k; i++){
        long long a, b;
        cin >> a >> b;
        if(a > b) {
            swap(a, b);
        }
        long long curr = (plus - minus) * a;
        long long delta = b - a;
        if(delta == 0) {
            cout << (curr == 0 ? "YES" : "NO") << "\n";
            continue;
        }
        if (curr % delta != 0) {
            cout << "NO\n";
            continue;
        }

        long long avail = (curr < 0 ? plus : minus);
        curr = abs(curr);
        if (curr > avail * delta) {
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
    
    return 0;
}