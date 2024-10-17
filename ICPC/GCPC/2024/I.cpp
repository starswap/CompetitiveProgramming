include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;

int main(){
    int n, w;
    cin >> n >> w;
    vi start;
    vi length;
    vi amp;
    string q;
    int p,l,a;
    for(int j=0; j < n; j++){
        cin >> q >> p;

        if(q == "!"){
            cin >> l >> a;
            start.push_back(p);
            length.push_back(l);
            amp.push_back(a);
        } else {
            ll tot = 0;
            for(int i=0; i < start.size(); i++){
                if(start[i] <= p && p <= start[i]+length[i]-1){
                    int inseq =  (p-start[i])%4;
                    if(inseq == 0){
                        tot += amp[i];
                    } else if(inseq == 2){
                        tot -= amp[i];
                    }
                }
            }
            cout << tot << "\n";
        }

    }
}