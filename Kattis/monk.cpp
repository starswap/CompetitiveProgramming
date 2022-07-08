#include <bits/stdc++.h>
using namespace std;


const double eps = 1e-7;

template <class T>
ostream& operator << (ostream& o,vector<T> v) {
	o << "[";
	for (auto u : v)
		o << u << ",";
	o << "]";
	return o;
}


double calcHeight(const double t,const vector<double> &H,const vector<double> &T) {
	int ind = lower_bound(T.begin(),T.end(),t) - T.begin();
	double height;
	if (T[ind] == t)
		height = H[ind];
	else
		height = H[ind-1]+(H[ind] - H[ind-1])/(T[ind] - T[ind-1])*(t - T[ind-1]); //interpolate
	
	return height;
} 

double calcDistDelta(const double t,const vector<double> &Ah,const vector<double> &At,const vector<double> &Dh,const vector<double> &Dt,const double H) {
	double ascHeight = calcHeight(t,Ah,At);
	double descHeight = H-calcHeight(t,Dh,Dt);
	return descHeight-ascHeight;
}

int main() {
	int a,d; cin >> a; cin >> d;
	vector<double> At(a+1,0);
	vector<double> Ah(a+1,0);
	vector<double> Dt(d+1,0);
	vector<double> Dh(d+1,0);
	
	double T = 0;
	double H = 0;
	for (int i=1;i<=a;++i) {		
		double h; double t;
		cin >> h; cin >> t;
		H += h;
		T += t;
		Ah[i] = H;
		At[i] = T;
	}

	T = 0;
	H = 0;	
	for (int j=1;j<=d;++j) {
		double h; double t;
		cin >> h; cin >> t;
		H += h;
		T += t;
		Dh[j] = H;
		Dt[j] = T;
	}
	
	double lo = 0;
	double hi = T;
	double delta;
	
	
	//cout << Ah << endl;
	//cout << At << endl;
	//cout << Dh << endl;
	//cout << Dt << endl;	
	
	do {
		double m = (lo+hi)/2;
		//cout << m << endl;
		delta = calcDistDelta(m,Ah,At,Dh,Dt,H);
		(delta > 0) ? lo = m : hi = m;
	} while (hi-lo >= eps);
	
	printf("%.6f",lo);
	return 0;
}