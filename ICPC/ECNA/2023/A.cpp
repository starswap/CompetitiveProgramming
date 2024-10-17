#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;

int main(){
    int n;
    cin >> n;
    vi nums(n+1);
    vi lmax(n+2);
    vi rmin(n+2, 1e9);
    for(int i=1; i <= n; i++) cin >> nums[i];

    for(int i=1; i <= n; i++){
        lmax[i] = max(lmax[i-1], nums[i]);
    }
    for(int i=n; i >= 1; i--){
        rmin[i] = min(rmin[i+1], nums[i]);
    }
    
    vi ans;

    for(int i=1; i <= n; i++){
        if(lmax[i] <= nums[i] && rmin[i] >= nums[i]){
            ans.push_back(nums[i]);
        }
    }
    cout << ans.size() << " ";
    for(int i=0; i < min((int)ans.size(), 100); i++) cout << ans[i] << " ";
    cout << "\n";

}