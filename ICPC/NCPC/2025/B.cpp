#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100;
const int MAX_H = 350;
const int MAX_W = 900;
int N, H, W;
int T;
vector<pair<int, int>> books; // (h, t)
int dp[MAX_W + 10][MAX_H + 10][MAX_N + 10];

// w = width of stack lying down
// h = height of stack vertically
// i = book index
int doDP(int w, int h, int i) {

    if (w > W) return false;
    else if (h > H) return false;
    else if (dp[w][h][i] != -1) return dp[w][h][i];
    else if (i == N) { // assigned all books
        int remaining_thickness = T - h;
        bool at_least_one_book_vert = (remaining_thickness > 0);
        bool at_least_one_book_horiz = h > 0;

        return at_least_one_book_horiz && at_least_one_book_vert && (remaining_thickness + w <= W);
    } else {
        if (books[i].first <= H) {
            dp[w][h][i] = doDP(max(w, books[i].first), h + books[i].second, i + 1) || doDP(w, h, i + 1);
        } else {
            dp[w][h][i] = doDP(max(w, books[i].first), h + books[i].second, i + 1); // only allowed flat
        }
        return dp[w][h][i];
    }
}

vector<int> upright;
vector<int> stacked;
void collectDP(int w, int h, int i) {
    if (i < N) {
        assert(dp[w][h][i]);

        if (doDP(max(w, books[i].first), h + books[i].second, i + 1)) {
            stacked.push_back(i + 1);
            collectDP(max(w, books[i].first), h + books[i].second, i + 1);
        } else {
            upright.push_back(i + 1);
            collectDP(w, h, i + 1);
        }
    }
}

int main() {
    cin >> N >> H >> W;

    books.resize(N);

    for (int n = 0; n < N; ++n) {
        cin >> books[n].first >> books[n].second;
        T += books[n].second;
    }

    fill(&dp[0][0][0], &dp[0][0][0] + sizeof(dp)/sizeof(dp[0][0][0]), -1);

    if (!doDP(0, 0, 0)) {
        cout << "impossible" << endl;
    } else {
        collectDP(0, 0, 0);
        assert(upright.size() >= 1 && stacked.size() >= 1);

        cout << "upright ";
        for (unsigned int i = 0; i < upright.size() - 1; ++i) {
            cout << upright[i] << " ";
        }
        cout << upright[upright.size() - 1] << endl;
        
        sort(stacked.begin(), stacked.end(), [](int i, int j) {
            return books[i - 1].first > books[j - 1].first;
        });

        cout << "stacked ";
        for (unsigned int i = 0; i < stacked.size() - 1; ++i) {
            cout << stacked[i] << " ";
        }
        cout << stacked[stacked.size() - 1] << endl;
    }

    return 0;
}

// 12:17
