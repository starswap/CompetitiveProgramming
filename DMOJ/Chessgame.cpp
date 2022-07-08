#include <bits/stdc++.h>
using namespace std;

int main() {
	int M,N; scanf("%d %d",&N,&M);
	
	vector<string> board(N);
	vector<int> rowTotals(N,0);
	for (int i=0;i<N;++i) {
		cin >> board[i];
		for (int j=0;j<M;++j)
			if (board[i][j] == '*') ++rowTotals[i];
	}

	vector<vector<bool>> places(N,vector<bool>(M));
	vector<int> rowTotals2(rowTotals);

	for (int i=0;i<N;++i) {
		for (int j=0;j<M;++j) {
			if (rowTotals[i] >= 2 && board[i][j] == '.') {
				places[i][j] = true;
			} else if (board[i][j] == '*') {
				rowTotals[i]--;
			}
		}
	}
	for (int i=0;i<N;++i) {
		for (int j=M-1;j>=0;--j) {
			if (rowTotals2[i] >= 2 && board[i][j] == '.') {
				places[i][j] = true;
			} else if (board[i][j] == '*') {
				rowTotals2[i]--;
			}
		}
	}
	
	
	vector<int> colTotals(M,0);
	for (int j=0;j<M;++j)
		for (int i=0;i<N;++i)
			if (board[i][j] == '*') ++colTotals[j];
	
	vector<int> colTotals2(colTotals);
	
	for (int j=0;j<M;++j) {
	 	for (int i=0;i<N;++i) {
			if (colTotals[j] >= 2 && board[i][j] == '.')
				places[i][j] = true;
			else if (board[i][j] == '*')
				colTotals[j]--;
		}
	}
	for (int j=0;j<M;++j) {
	 	for (int i=N-1;i>=0;--i) {
			if (colTotals2[j] >= 2 && board[i][j] == '.')
				places[i][j] = true;
			else if (board[i][j] == '*')
				colTotals2[j]--;
		}
	}
	
	
	int sumT = 0;
	for (int i=0;i<N;++i) {
		for (int j=0;j<M;++j) {
			sumT += places[i][j];
		}
	}
	
	cout << sumT << endl;	
}