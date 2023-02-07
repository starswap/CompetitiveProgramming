#include <bits/stdc++.h>
using namespace std;

// Fast enough because on every check we move someone, except when we decrement the stuck pointer
// In that case we might not be moving someone, but it's fine because the stuck pointer can only go from N down to 0.
// This is a small constant number of "useless moves", and in total the useless moves can't exceed this. Then, either:
//    - we later go back from the stuck pointer with i (and hence we took 2 moves only to get this output)
//    - we don't later go back along the stuck pointer so we wasted 1 move (to a total maximum of N).
// Then the number of iterations is definitely bounded by output * 2 + N, and likely much less. This is O(N^2) which passes 
// comfortably.

vector<int> A, V, D;
vector<int> ans;
int B, P, K;
int done = 0;

bool move(int i) {
    int targ = D[V[i] + 1];
    if (i > 0 && targ - D[V[i - 1]] > B) { // moving would put us too far away.
        return false;
    }
    else if (i < K - 1 - done && (D[V[i + 1]] - targ < A[i + 1] || D[V[i + 1]] - targ < A[i])) { // moving would break the personal space requirement.
        return false;
    }
    else { // we can move
        V[i]++;
        ans.push_back(i + 1);
        if (V[i] == P - 1) { // this person reached the end
            done += 1;
            return false;
        }
        return true;
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> B;
    cin >> P;
    D.assign(P, 0);
    for (int p = 0; p < P; ++p) {
        cin >> D[p];
    }

    cin >> K;
    A.assign(K, 0);
    V.assign(K, 0);
    for (int k = 0; k < K; ++k) {
        cin >> A[k];
        cin >> V[k];
        V[k]--;
        if (V[k] == P - 1) done++;
    }

    int stuck = K - done; // Stuck pointer
    bool poss = true;     // Can be done
    while (done < K) {
  
        while (stuck > 0 && !move(stuck - 1)) {stuck--;} // decrement stuck pointer until unstuck
        if (stuck == 0) { // if everyone get stuck, the problem must be impossible. 
            poss = false;
            break;
        }
        while (move(stuck - 1)) {}; // advance next person until they are now stuck.

        // Shuffle everyone else up, if they have been freed by the latest shuffle to the left of them.
        int i; 
        for (i = stuck; i < K - done; ++i) { // go through all the people who haven't finished yet and were stuck
            if (!move(i)) // until the current person is still stuck
                break;
            else // and get them stuck again
                while (move(i)) {};
        }
        stuck = min(i, K - done); // we pushed everyone forward so the person before the person we just pushed might be free to move again.
    }

    // output the answer
    if (poss) {
        for (int i = 0; i < ((int) ans.size()) - 1; ++i)
            cout << ans[i] << " ";
        if (ans.size() > 0)
            cout << *ans.rbegin() << endl;
    }
    else {
        cout << "impossible" << endl;
    }

    return 0;
}