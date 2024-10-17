#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

int seen[200005];
vi graph[300005];

int main(){
    int n,m;
    cin >> n >> m;
    int a,b;
    vi graph[n+1];
    for(int i=0; i < m; i++){
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    int ma = 1;
    for(int i=1; i <= n; i++){
        if(seen[i]) continue;
        int tot = 0;
        queue<int> q;
        q.push(i);
        while(q.size() > 0){
            int ne = q.front(); q.pop();
            if(seen[ne]) continue;
            seen[ne] = 1;
            tot++;
            for(auto x: graph[ne]){
                if(!seen[x]) q.push(x);
            }
        }
        ma = max(ma, tot);
    }
    cout << ma << "\n";
}
