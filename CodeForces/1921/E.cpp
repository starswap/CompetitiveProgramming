#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        int H, W, Ra, Ca, Rb, Cb;
        cin >> H >> W >> Ra >> Ca >> Rb >> Cb;
        int dr = abs(Ra - Rb);
        int dc = abs(Ca - Cb);

        if (Ra > Rb) {
            cout << "Draw" << endl;
        } else {
            if (dr % 2 == 0) {
                int run_side_space = (Ca < Cb) ? Cb - 1 : (W - Cb); 
                if (dc >= 1 && run_side_space > dr/2) {
                    cout << "Draw" << endl;
                } else {
                    cout << "Bob" << endl;
                }
            } else {
                int run_side_space = (Cb < Ca) ? Ca - 1 : (W - Ca); 
                if (dc >= 2 && run_side_space > dr/2 + 1)  {
                    cout << "Draw" << endl;
                } else {
                    cout << "Alice" << endl;
                }

            }
        }
    }
    return 0;
}