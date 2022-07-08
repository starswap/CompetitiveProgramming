// Google Kick Start Problem C Round A 2017 - "Two Cubes"

#include <bits/stdc++.h>
using namespace std;

int main() {
	
	int T; cin >> T;
		
	for (int c=1;c<T+1;++c){
		vector<tuple<int,int,int>> Cs;
		vector<int> Rs;
		int xMinMax[] = {1000000000,-1000000000};
		int yMinMax[] = {1000000000,-1000000000};
		int zMinMax[] = {1000000000,-1000000000};
		int N;
		cin >> N;
		for (int i=0;i<N;++i) {
			int x,y,z,r; cin >> x; cin >> y; cin >> z; cin >> r;
			Cs.emplace_back(x,y,z);
			Rs.push_back(r);
			xMinMax[0] = min(x-r,xMinMax[0]);
			xMinMax[1] = max(x+r,xMinMax[1]);
			yMinMax[0] = min(y-r,yMinMax[0]);
			yMinMax[1] = max(y+r,yMinMax[1]);
			zMinMax[0] = min(z-r,zMinMax[0]);
			zMinMax[1] = max(z+r,zMinMax[1]);			
		}
	
		int lo = 0;
		int hi = 400000000;
		
		/*cout << xMinMax[0] << endl;
		cout << yMinMax[0] << endl;
		cout << zMinMax[0] << endl;
		cout << xMinMax[1] << endl;
		cout << yMinMax[1] << endl;
		cout << zMinMax[1] << endl;*/
		
		
		while (lo != hi) { 
			int L = (lo+hi)/2;
			
		//	cout << "hi" << hi << "lo" << lo << endl;
		//	cout << "L" << L << endl;
		
			bool can = false;
			for (int i=0;i<=1;++i) {
				for (int j=0;j<=1;++j) {
					for (int k=0;k<=1;++k) {
						double Cx,Cy,Cz;
						if (i == 0) {
							Cx = static_cast<double>(xMinMax[i])+static_cast<double>(L)/2.0;
						} else {
							Cx = static_cast<double>(xMinMax[i])-static_cast<double>(L)/static_cast<double>(2);
						}
						if (j == 0) {
							Cy = static_cast<double>(yMinMax[j])+static_cast<double>(L)/static_cast<double>(2);
						} else {
							Cy = static_cast<double>(yMinMax[j])-static_cast<double>(L)/static_cast<double>(2);
						}					
						if (k == 0) {
							Cz = static_cast<double>(zMinMax[k])+static_cast<double>(L)/(2.0);
						} else {
							Cz = static_cast<double>(zMinMax[k])-static_cast<double>(L)/static_cast<double>(2);
						}
						
						int xSubMin = 1000000000;
						int xSubMax = -1000000000;
						int ySubMin = 1000000000;
						int ySubMax = -1000000000;
						int zSubMin = 1000000000;
						int zSubMax = -1000000000;
						bool unchanged = true;
						
						//cout << "C (" << Cx << "," << Cy << "," << Cz << ")" << endl;
					//	cout << "L" << L << endl; 
						
						for (int l=0;l<N;++l) {
							auto &[x,y,z] = Cs[l];
							int r = Rs[l];
							
							//cout << "x" << x << endl; 
							//cout << "P (" << x << "," << y << "," << z << ")" << " R: " << r << endl;
							//EPS?
							if (!(x+r <= static_cast<double>(Cx)+static_cast<double>(L)/2.0 && x-r >= static_cast<double>(Cx)-static_cast<double>(L)/2.0 && y+r <= static_cast<double>(Cy)+static_cast<double>(L)/2.0 && y-r >= static_cast<double>(Cy)-static_cast<double>(L)/2.0 && z+r <= static_cast<double>(Cz)+static_cast<double>(L)/2.0 && z-r >= static_cast<double>(Cz)-static_cast<double>(L)/2.0)) { //not bounded by this cube
					//			cout << "no" << endl;
								xSubMin = min(xSubMin,x-r);
								xSubMax = max(xSubMax,x+r);
								ySubMin = min(ySubMin,y-r);
								ySubMax = max(ySubMax,y+r);
								zSubMin = min(zSubMin,z-r);
								zSubMax = max(zSubMax,z+r);
								unchanged = false;
							}
							
						}
						
						if ((xSubMax - xSubMin <= L && ySubMax-ySubMin <= L && zSubMax - zSubMin <= L || unchanged) && can != true) {//can do : ) -> all in 1st cube or can find 2nd cube to make others work.
							can = true;
//							cout << "unc" << unchanged << endl;
						}

					}
				}
			}
			
			if (can)
				hi = L;
			else
				lo = L+1;
		
		}
		printf("Case #%d: %d\n",c,lo);	

	

	}


}