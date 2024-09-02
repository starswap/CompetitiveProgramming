#include <bits/stdc++.h>

using namespace std;



bool impossible = false;

int removing[100005];
bool state[100005];

set<pair<int, int>> ans;
map<pair<int, int>, int> ind_look;
map<pair<int, int>, int> freqs;

vector<int> graph[100005];


void bfs(int u){
    if(state[u] == 1){
        return;
    }
    // if(state[u]){
    //     return;
    // }
    // cout << u << " " << remove << "\n";
    // state[u] = 1;
    // for(auto child: graph[u]){
    //     if(remove){
    //         cout << "REMOVING " << u << " " << child << "\n";
    //         ans.insert(make_pair(u, child));
    //     }
    //     dfs(child, 1-remove);

    // }
    queue<pair<int, int>> q;
    q.push(make_pair(u, true));
    state[u] = 1;
    removing[u] = true;
    while(q.size() > 0){
        auto &[node, remove] = q.front();
        q.pop();

        for(auto child: graph[node]){
            if(removing[child] != -1 && remove != removing[child]){
                impossible = true;
                cout << "NO\n";
                exit(0);
            }
            removing[child] = remove;
            if(remove && removing[child]){
                //cout << "REMOVING " << node << " " << child << "\n";
                ans.insert(make_pair(node, child));
            }

            if(!state[child]){
                state[child] = 1;
                q.emplace(child, 1-remove);
            }
        }

    }
}



int main(){


    int n,m;
    cin >> n >>m;
    fill(state, state+n+1, 0);
    fill(removing, removing+n+1, -1);

    int a,b;
    vector<pair<int, int>> edges;
    for(int i=0; i < m; i++){
        cin >> a >> b;
        ind_look[make_pair(a,b)] = i;
        freqs[make_pair(a,b)]++;
        graph[a].push_back(b);
        edges.push_back(make_pair(a,b));
    }



    if(2 < n && n <= 1000){

        bool can = false;
        for(int i=1; i <= n; i++){
            for(int j=1; j <= n; j++){
                if(i == j) continue;
                if(freqs[make_pair(i,j)] < 1){
                    can = true;
                    break;
                }
            }
        }

        if(!can){
            cout << "NO\n";
            exit(0);
        }
    }
    for(int i=1; i <= n; i++){
        bfs(i);
    }
    //cout << "\n\n";
    int tot = 0;
    for(auto p: ans){
        tot += freqs[p];
        //cout << p.first << " " << p.second << "\n";
    }

    cout << "YES\n";

    if(tot >= m/2){
        // Need to  take the other one;
        assert(tot >= m/2);
        cout << tot << "\n";
        for(int i=0; i < m; i++){
            if(ans.count(edges[i])){
                cout << i+1 << " ";
            }
        }
    }else{
        assert(m-tot >= m/2);
        cout << m-tot << "\n";
        for(int i=0; i < m; i++){
            if(ans.count(edges[i])==0){
                cout << i+1 << " ";
            }
        }
    }
    cout << "\n";



    return 0;
}