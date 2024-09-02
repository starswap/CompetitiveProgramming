#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fori(i,a,b) for(int i=a;i<=b;i++)
#define ford(i,a,b) for(int i=a;i>=b;i--)
#define f first
#define s second
#define pb push_back
const int ma = 1000005;
int n,c, sum_d[ma], d[ma], p[20][ma], end_d[ma], visited[ma];
int depth[ma];
int distance;

int next_ad(int i) {
    int l = i + 1;
    int r = 2 * n;
    int ret = 2 * n + 1;
    while ( l <= r) {
        int m = (l + r)/ 2;
        if (sum_d[m] - sum_d[i] >= c) {
            ret = m;
            r = m - 1;
        } else l = m + 1;
    }
    if (ret > n) return ret - n;
    return ret;
}

int visit(int i) {
    if (visited[i]) {
        return depth[i];
    }
    else {
        visited[i] = true;
        int next_ad_i = next_ad(i);
        if (next_ad_i <= i) {
            end_d[i] = i;
            depth[i] = 0;
            return 0;
        }
        depth[i] = visit(next_ad_i) + 1;
        end_d[i] = end_d[next_ad_i];
        p[0][i] = next_ad_i;
        return depth[i];
    }
}

int find_path_to_nearest_parent_smaller_than(int ma, int child) {
    int parent = child;
    int ret = 0;
    ford(i,19,0) {
        if (p[i][parent] < ma) {
            parent = p[i][parent];
            ret += pow(2, i);
        }
    }
    return ret;
}
signed main() {
    cin>>n>>c;
    sum_d[0] = 0;
    fori(i,1,n) {
        depth[i]=0;
        cin>>d[i];
        sum_d[i] = sum_d[i - 1] + d[i];
    }

    fori(i,n+1,2*n) {
        d[i] = d[i-n];
        sum_d[i] = sum_d[i - 1] + d[i];
    }

    for (int i = 1; i <= n; ++i) {
        visit(i);
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 1; j <= n; ++j) {
            p[i][j] = 3*n;
        }
    }

    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j <= n; ++j) {
            p[i][j] = p[i-1][p[i-1][j]];
        }
    }

    for (int i = 1; i <= n; ++i) {
        int ans = depth[i];
        int ne = next_ad(ans);
        if (ne < i) {
            ans += 1 + find_path_to_nearest_parent_smaller_than(i, ne);
        }
        cout<<ans<<' ';
    }
    cout << endl;
}