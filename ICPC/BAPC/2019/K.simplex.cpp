#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef double T; // long double, Rational, double + mod<P>...
typedef vector<T> vd;
typedef vector<vd> vvd;

const T eps = 1e-8, inf = 1/.0;
#define MP make_pair
#define ltj(X) if(s == -1 || MP(X[j],N[j]) < MP(X[s],N[s])) s=j

struct LPSolver {
	int m, n;
	vi N, B;
	vvd D;

	LPSolver(const vvd& A, const vd& b, const vd& c) :
		m(sz(b)), n(sz(c)), N(n+1), B(m), D(m+2, vd(n+2)) {
			rep(i,0,m) rep(j,0,n) D[i][j] = A[i][j];
			rep(i,0,m) { B[i] = n+i; D[i][n] = -1; D[i][n+1] = b[i];}
			rep(j,0,n) { N[j] = j; D[m][j] = -c[j]; }
			N[n] = -1; D[m+1][n] = 1;
		}

	void pivot(int r, int s) {
		T *a = D[r].data(), inv = 1 / a[s];
		rep(i,0,m+2) if (i != r && abs(D[i][s]) > eps) {
			T *b = D[i].data(), inv2 = b[s] * inv;
			rep(j,0,n+2) b[j] -= a[j] * inv2;
			b[s] = a[s] * inv2;
		}
		rep(j,0,n+2) if (j != s) D[r][j] *= inv;
		rep(i,0,m+2) if (i != r) D[i][s] *= -inv;
		D[r][s] = inv;
		swap(B[r], N[s]);
	}

	bool simplex(int phase) {
		int x = m + phase - 1;
		for (;;) {
			int s = -1;
			rep(j,0,n+1) if (N[j] != -phase) ltj(D[x]);
			if (D[x][s] >= -eps) return true;
			int r = -1;
			rep(i,0,m) {
				if (D[i][s] <= eps) continue;
				if (r == -1 || MP(D[i][n+1] / D[i][s], B[i])
				             < MP(D[r][n+1] / D[r][s], B[r])) r = i;
			}
			if (r == -1) return false;
			pivot(r, s);
		}
	}

	T solve(vd &x) {
		int r = 0;
		rep(i,1,m) if (D[i][n+1] < D[r][n+1]) r = i;
		if (D[r][n+1] < -eps) {
			pivot(r, n);
			if (!simplex(2) || D[m+1][n+1] < -eps) return -inf;
			rep(i,0,m) if (B[i] == -1) {
				int s = 0;
				rep(j,1,n+1) ltj(D[i]);
				pivot(i, s);
			}
		}
		bool ok = simplex(1); x = vd(n);
		rep(i,0,m) if (B[i] < n) x[B[i]] = D[i][n+1];
		return ok ? D[m][n+1] : inf;
	}
};



// f1 * G1x + .... + fn * Gnx = Px
// f1 * G1y + .... + fn * Gny = Py
// Convert to a pair of <= and >= 
// also f1 + f2 + f3 + ... + fn = 1
// Constraints fa <= 1 and fa >= 0
// the latter constraint is given in this code
// A = [
//   G1x .... Gnx
//   -G1x .... -Gnx
//   G1y ... Gny
//   -G1y ... -Gny
//  1 1 1 1 1 1 1 1 1 1
//   -1 -1 -1 -1 -1 -1
//   1 0 0 0 0 0 0 0 
//   0 1 0 0 0 0 0 0 
//      ....
//   0 0 0 0 0 0 0 1
//]
// b = [Px, -Px, Py, -Py, 1, -1, 1, 1, 1, 1, 1, 1, 1, 1]
// We can take any solution so just let c = all 0s.

int main() {
    int n;
    double Px, Py;
    cin >> n >> Px >> Py;
    vvd A(n + 6, vd(n, 0));
    vd b(n + 6, 0);
    vd c(n, 0);
    vd f(n, 0);

    b[0] = Px;
    b[1] = -Px;
    b[2] = Py;
    b[3] = -Py;
    b[4] = 1;
    b[5] = -1;

    for (int i = 0; i < n; ++i) {
        double Gix, Giy;
        cin >> Gix >> Giy;
        A[0][i] = Gix;
        A[1][i] = -Gix;
        A[2][i] = Giy;
        A[3][i] = -Giy;
    }

    for (int i = 0; i < n; ++i) {
        A[4][i] = 1;
        A[5][i] = -1;
        A[6 + i][i] = 1;
        b[6 + i] = 1;
    }

    LPSolver l(A, b, c);
    T res = l.solve(f);
    for (double fi : f) {
        cout << fixed << setprecision(10) << fi << endl;
    }    
    return 0;
}
