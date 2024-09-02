#include <bits/stdc++.h>
using namespace std;


long long solve_equal(int n, int m, int k){
    long long ans = 0;
    if(n%m == 0){
        int eq = n/m;
        int turns_to_kill = eq/k;
        for(int g=0; g < m; g++){
            ans += (m-g)*eq;
            ans += (turns_to_kill*eq);
            // Now need to subtract k * triangle number
            ans -= k*(turns_to_kill*(turns_to_kill-1))/2;
        }

    }else{
        // Group size doesn't divide gnomes
        int big = n/m + 1;
        // To kill the big groups 
        int turns_to_kill = big/k;
        for(int g=0; g < n%m; g++){
            ans += (n%m - g)*big + (m - n%m)*(n/m);
            ans += turns_to_kill*big;
            ans -= k*(turns_to_kill*(turns_to_kill-1))/2;

        }
        for(int g=0; g < m-(n%m); g++){
            
        }

    }


}

long long solve_ones(int n, int m, int k){

    if(n <= m){
        // One gnome in each
        long long ans = n*(n+1) / 2;
        return ans;
    } else{
        int big = n-m-1;
        
        int turns_to_kill_big = big/k;

        long long ans = 0;
        for(int i=0; i < turns_to_kill_big; i++){
            ans += m-1;
            ans += (big-i*k);
        }
        if(big%k == 0){
            ans += m*(m-1)/2;
            // Just m-1 groups of 1 left 
        }else if(big%k == 1){
            // m groups of 1 left
            ans += m*(m+1)/2;
        }else{
            // We have a bigger remainder than one
            // so the lightning dude strikes this one first
            ans += (big%k)+m-1;
            ans += m*(m+1)/2;
        }
        return ans;




    }


}


int main(){

    cin >> n >> m >> k;





    return 0;
}