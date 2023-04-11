// On your local machine you may need to increase the stack size to run this program with large inputs.
// Most judging websites have this consideration sorted. For example Kattis gives unlimited stack space.

#include <bits/stdc++.h>
using namespace std;

int N;
int logN;
int nodes_cut = 0;

vector<vector<int>> AL;
vector<vector<int>> DP;

int logFloor(int x) {
    // Compute |_ log(n) _|
    int i = 0;
    while (x != 1) {
        i++;
        x >>= 1;
    }
    return i;
}

// Returns depth of tree and updates number of nodes robbed
int comp(int r, int p) {
    vector<int> ds; // depths of present children; allows for some children to be missing by using a vector
    vector<int> cs; // indices of present children; allows for variable number of children by using vector

    for (int c : AL[r]) {
        if (c == p) continue; // don't go back up tree
        else {
            ds.push_back(comp(c, r)); // find out depth of that subtree
            cs.push_back(c); // save child's name
        }
    }
    
    // Ensure we have two children depths - assume depth of -1 if not present.
    while (ds.size() < 2) {ds.push_back(-1);}

    // if left subtree is deeper than right subtree
    while (ds[0] - ds[1] >= 2) {
        // chop nodes from left subtree to match
        nodes_cut += DP[cs[0]][ds[0]];
        DP[cs[0]][ds[0]] = 0; // we only need to update it here (even though in principle it affects dp values of nodes between this node and the node cut), because only the dp values at one level below are copied up the stack.
        ds[0]--; // depths are closer to matching
    }

    // if right subtree is deeper than left subtree
    while (ds[1] - ds[0] >= 2) {
        // chop nodes
        nodes_cut += DP[cs[1]][ds[1]];
        DP[cs[1]][ds[1]] = 0;
        ds[1]--;
    }

    // Let 0 depth represent just a single node, i.e. depth is number of edges in path from root to leaf.
    int depth = 0;
    DP[r][0] = 1;

    // Copy up the DP table from the children to this node r.
    // O(log n) since the subtree is balanced.
    while (true) {
        // We are done iff we have copied up nodes up to the depth of both subtrees
        int shouldExit = true;
        for (int d : ds) {
            if (depth <= d) {shouldExit = false;} 
        }
        if (shouldExit) break;

        // otherwise we aren't done yet
        for (int i = 0; i < cs.size(); i++) { // for both children, propagate the DP (note that the DP table is initialised to 0, and so if one subtree is exhausted earlier then that is taken care of)
            DP[r][depth + 1] += DP[cs[i]][depth];
        }
        depth++;
    }
    
    // subtree at node r is 1 deeper than tallest child subtree, after balancing 
    return max(ds[0], ds[1]) + 1;
}


int main() {
    cin >> N;
    logN = logFloor(N) + 10;

    AL.assign(N, vector<int>());
    DP.assign(N, vector<int>(logN, 0));

    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        a--; b--;
        AL[a].push_back(b);
        AL[b].push_back(a);
    }

    comp(0, -1);
    cout << nodes_cut << endl;
    return 0;
}