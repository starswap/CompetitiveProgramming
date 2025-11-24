#include <bits/stdc++.h>
using namespace std;

int cnt[1007];

int main(){
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        cnt[a]++;
    }

    int score = 0;
    for (int i = 0; i < 1007; i++) {
        if (cnt[i] >= i) {
            score += cnt[i] - i;
        }else{
            score += cnt[i];
        }
    }

    cout << score << "\n";
}