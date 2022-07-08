#include <bits/stdc++.h>
using namespace std;

const double eps = 0.001;

inline double timeTaken(double vr, double vc, double r, double k) {
	return (r/vr) + (k/vc);
}

inline double getWinsBy(const vector<double> &vr, const vector<double> &vc, double r, double c,int n) {
	double minTime = 1e9;
	for (int i=0;i<n-1;++i) {
		minTime = min(minTime,timeTaken(vr[i],vc[i],r,c));
	}
	
	double cheatTime = timeTaken(vr[n-1],vc[n-1],r,c);
	double winsBy = minTime - cheatTime;
	
	return winsBy;
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
		
		//terary search on r.
		double lo = 0; double hi = t;
		while (hi-lo >= eps) {
			double delta = (hi-lo)/3;
			double rO = lo + delta;
			double rI = hi - delta;
			double cO = t-rO;
			double cI = t-rI;
			
			double L = getWinsBy(vr,vc,rO,cO,n);
			double R = getWinsBy(vr,vc,rI,cI,n);
			if (L > R)
				hi -= delta;
			else if (L == R) {
				lo += delta;
				hi -= delta;
			} else {				
				lo += delta;
			}

		}
		//cout << lo << endl;
		double maxWin = getWinsBy(vr,vc,round(lo*100)/100,t-round(lo*100)/100,n);
		maxWin *= 3600; // to seconds
		//cout << maxWin << endl;
		if (round(maxWin) < 0) {
			printf("The cheater cannot win.\n");
		} else {
			printf("The cheater can win by %d seconds with r = %.2fkm and k = %.2fkm.\n",static_cast<int>(round(maxWin)),lo,t-lo); 
		}
		
	}

}