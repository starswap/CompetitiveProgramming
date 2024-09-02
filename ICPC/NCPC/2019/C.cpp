
#include <bits/stdc++.h>
using namespace std;


bool solve(long long a, long long n, long long m){
    bool can = false;

    // CHeck if it divides
    for(long long f=1; f*f <= a; f++){
        if(a%f == 0){
            long long o = a/f;
            if(min(o,f) <= n && max(o,f) <= m){
                return true;
            }
        }
    }
    return false;

}
int main(){
        long long n,m,a;



    cin >> n >> m >> a;
    if(m < n){
        swap(n,m);
    }

    if(a%n == 0 || a%m == 0){
        cout << 1 << "\n";
    }else{
        bool res = solve(a,n,m) || solve(n*m - a, n,m);

        if(res){
            cout << "2\n";
        }else{
            cout << "3\n";
        }

    }


    return 0;
}