#include <bits/stdc++.h>
using namespace std;


inline double timeTaken(double vr, double vc, double r, double k) {
	return (r/vr) + (k/vc);
}

int main() {
	
	int t; 
	while (scanf("%d",&t) != EOF) {
//cout << t << endl;
		int n; cin >> n;
		vector<double> vr(n);
		vector<double> vc(n);
		for (int i=0;i<n;++i) {
			cin >> vr[i]; cin >> vc[i];
		}
		
		double maxWin = -1e9;
		double occursAtR; double occursAtC;
		for (double r=0;r<=t;r = r+0.001) {
			double c = t-r;
			double minTime = 1e9;
			for (int i=0;i<n-1;++i) {
				minTime = min(minTime,timeTaken(vr[i],vc[i],r,c));
			}
			
			double cheatTime = timeTaken(vr[n-1],vc[n-1],r,c);
			double winsBy = minTime - cheatTime;
			//cout << winsBy << endl;
			if (winsBy > maxWin){
				
				maxWin = winsBy;
				occursAtC = c; occursAtR = r;
			}
		}
		maxWin *= 3600; // to seconds
		if (round(maxWin) < 0) {
			printf("The cheater cannot win.\n");
		} else {
			printf("The cheater can win by %d seconds with r = %.2fkm and k = %.2fkm.\n",static_cast<int>(round(maxWin)),occursAtR,occursAtC); 
		}
		
	}

}