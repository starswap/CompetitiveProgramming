//G4G : https://practice.geeksforgeeks.org/problems/maximum-sum-rectangle2948/1
// (simply using the algorithm from CP Book, from memory).

//{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution {
  public:
    int maximumSumRectangle(int R, int C, vector<vector<int>> M) {
        vector<vector<int>> Pref(R,vector<int>(C,0));
        int maxEl = -1e9;
        for (int r=0;r<R;++r) {
            int total = 0;
            for (int c=0;c<C;++c) {
                total += M[r][c];
                Pref[r][c] = total;
                maxEl = max(maxEl,M[r][c]);
            }   
        }
        
        
        if (maxEl < 0)
            return maxEl;
            
        int bestOverall = -1e9;
        for (int l=0;l<C;++l) {
            for (int r=l;r<C;++r) {
                int bestContinue = 0;
                for (int row=0;row<R;++row) {
                    bestContinue += Pref[row][r] - ((l > 0) ? Pref[row][l-1] : 0);
                    if (bestContinue < 0) //Kadane's; reset if negative
                        bestContinue = 0;
                    else 
                        bestOverall = max(bestContinue,bestOverall);
                }
                
            }
         }
        return bestOverall;
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N, M;
        cin >> N >> M;
        vector<vector<int>> v(N, vector<int>(M));
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++) cin >> v[i][j];
        Solution ob;
        cout << ob.maximumSumRectangle(N, M, v) << "\n";
    }
}
// } Driver Code Ends