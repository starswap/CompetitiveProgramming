#include <bits/stdc++.h>
using namespace std;


int rectangle(int R,int C,int H,int W,int Q[3001][3001]) {
	int lo = 0; int hi = R*C;
	
	while (lo != hi) {
		int X = (lo+hi)/2;
		
		
		vector<vector<int>> auxO(R,vector<int>(C,0));
		for (int r=0;r<R;++r) {
			for (int c=0;c<C;++c) {
				auxO[r][c] = Q[r][c] <= X;
			}
		}
		
		
		vector<vector<int>> auxI(R,vector<int>(C-W+1,0));
		

		for (int r=0;r<R;++r) {
			int total = 0;
			for (int c=0;c<W;++c)
				total += Q[r][c];
			
			auxI[r][W-1] = total;
			
			for (int c=W;c<C;++c) {
				total += Q[r][c];
				total -= Q[r][c-W];
				auxI[r][c] = total;
			}
		}

		vector<vector<int>> auxII(R-H+1,vector<int>(C-W+1,0));
		for (int c=0;c<C-W+1;++c) {
			int total = 0;
			for (int r=0;r<H;++r)
				total += auxI[r][c];
			
			auxII[H-1][c] = total;
			
			for (int r=H;r<R;++r) {
				total += auxI[r][c];
				total -= auxI[r-H][c];
				auxII[r][c] = total;
			}
		}
		
		bool condMet = false;
		int threshold = ceil(static_cast<double>(X)/2.0);
		for (int r=0;r<R-H+1;++r) {
			for (int c=0;c<C-W+1;++c) {
				if (auxII[r][c] >= threshold)
					condMet = true;
			}
		}

		(condMet) ? hi = X : lo = X+1;
	
	}
	
}






