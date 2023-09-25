#include <bits/stdc++.h>
using namespace std;

struct point {
    int r, c;
};

struct rectangle {
    int left, right, top, bottom;
    bool contains(point p) {
        return (p.r >= top && p.r <= bottom && p.c >= left && p.c <= right);
    }
};

int main() {
    int r, c, k;
    cin >> r >> c >> k;
    vector<rectangle> rects;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            char curr;
            cin >> curr;
            if (curr == '#') {
                rects.push_back(rectangle{j - k, j + k, i - k, i + k});
            }
        }
    }

    if (k <= 20) { // brute force small cases where the mushroom might not be contiguous
        int ans = 0;
        for (int r = -21; r <= 41; ++r) {
            for (int c = -21; c <= 41; ++c) {
                for (rectangle rect : rects) {
                    if (rect.contains(point{r, c})) {ans++; break;}
                }
            }
        }
        cout << ans << endl;
    } else { // we know it's contiguous and so we can use sweep-line
        sort(rects.begin(), rects.end(), [] (rectangle a, rectangle b) {return a.left < b.left;});
        
        int out_ptr = 0;
        int in_ptr = 0;
        
        auto comp = [] (rectangle a, rectangle b) {if (a.top == b.top) return a.left > b.left; else return a.top > b.top;};
        set<rectangle, decltype(comp)> internal(comp);

        long long ans = 0;
        for (int c = -k - 1; c < k + 20 + 1; ++c) {
            while (out_ptr < rects.size() && rects[out_ptr].left == c) { internal.insert(rects[out_ptr]); out_ptr++; }
            if (internal.size() >= 1) {
                rectangle top = *internal.rbegin();
                rectangle bottom = *internal.begin();
                ans += bottom.bottom - top.top + 1;
            }
            while (in_ptr < rects.size() && rects[in_ptr].right == c) { internal.erase(rects[in_ptr]); in_ptr++; }
        }

        cout << ans << endl;
    }

    return 0;
}