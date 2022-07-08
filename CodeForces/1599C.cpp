// doesn't work - WA

#include <bits/stdc++.h>

using namespace std;

double calcProb(int nI,int mI) {
	double N = static_cast<double>(nI);
	double M = static_cast<double>(mI);
	
	return (
		(M/N)*((M-1)/(N-1))*((M-2)/(N-2)) + //3 known maps are selected
		(M/N)*((M-1)/(N-1))*(1-(M-2)/(N-2)) + //2 known maps are selected
		(M/N)*(1-(M-1)/(N-1))*((M-1)/(N-2)) + //2 known maps are selected
		((M/N)*((N-M)/(N-1))*(1-(M-1)/(N-2)))/2 + //1 known map is selected and the game chooses a known
		(1-(M/N))*(M/(N-1))*(M-1)/(N-2) + //2 known maps are selected
		(1-(M/N))*(M/(N-1))*(1-((M-1)/(N-2)))/2 + //1 known map is selected and the game chooses a known
		(1-(M/N))*(1-(M/(N-1)))*(M/(N-2))/2 //1 known map is selected and the game chooses a known
	);
}


int main() {
	int N; double P; 
	cin >> N; cin >> P;
	int M;
	cout << P << endl;
	for (M=0;M<=N;++M) {
		float prob = calcProb(N,M);
		cout << prob << endl;
		if (prob >= P)
			break;
	}
	printf("%d\n",M);
}
