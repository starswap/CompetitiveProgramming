#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
deque<int> ans;
int larger = 1;

void solve(ll N) {
    if (N > 1) {
        if (N % 2 == 0) {
            solve(N / 2);
            ans.push_back(larger++);
        } else {
            solve(N - 1);
            ans.push_front(larger++);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while (T--) {
        ll N; cin >> N;
        ans.clear();
        solve(N);
        cout << ans.size() << endl;
        while (!ans.empty()) {
            cout << ans.front() << " ";
            ans.pop_front();
        }
        cout << endl;
    }
    return 0;
}

/* Generate worst case for this algorithm */
// i = 0
// while i < 1000000000000000000:
//     i += 1
//     i *= 2
// print(i)

/* Check the number of increasing subsequences in a small array*/
// array = [*map(int, input().split())]
// def count(i, maxi):
//     ans = 1
//     for start in range(i, len(array)):
//         if array[start] > maxi:
//             ans += count(start + 1, array[start])
//     return ans
// print(count(0, -1000000000000000000000))
