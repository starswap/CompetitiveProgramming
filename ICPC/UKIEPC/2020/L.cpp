#include <bits/stdc++.h>
using namespace std;

typedef complex<double> C;
typedef vector<double> vd;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void fft(vector<C>& a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vector<complex<long double>> R(2, 1);
	static vector<C> rt(2, 1);  // (^ 10% faster if double)
	for (static int k = 2; k < n; k *= 2) {
		R.resize(n); rt.resize(n);
		auto x = polar(1.0L, acos(-1.0L) / k);
		rep(i,k,2*k) rt[i] = R[i] = i&1 ? R[i/2] * x : R[i/2];
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			// C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
			auto x = (double *)&rt[j+k], y = (double *)&a[i+j+k];        /// exclude-line
			C z(x[0]*y[0] - x[1]*y[1], x[0]*y[1] + x[1]*y[0]);           /// exclude-line
			a[i + j + k] = a[i + j] - z;
			a[i + j] += z;
		}
}

vd conv(const vd& a, const vd& b) {
	if (a.empty() || b.empty()) return {};
	vd res(sz(a) + sz(b) - 1);
	int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
	vector<C> in(n), out(n);
	copy(all(a), begin(in));
	rep(i,0,sz(b)) in[i].imag(b[i]);
	fft(in);
	for (C& x : in) x *= x;
	rep(i,0,n) out[i] = in[-i & (n - 1)] - conj(in[i]);
	fft(out);
	rep(i,0,sz(res)) res[i] = imag(out[i]) / (4 * n);
	return res;
}

vd all_dot_products(const vd&a, const vd& b) {
	vd c(b.rbegin(), b.rend());
	vd res = conv(a, c);
	int n_dps = max(a.size(), b.size()) - min(a.size(), b.size()) + 1;
	int n_not = res.size() - n_dps;
	vd dps(res.begin() + n_not/2, res.begin() + res.size()-n_not / 2);
	return dps;
}

const double RANDOM_NUMBER = 0.879;
const int MAX_STEPS = 7;

inline int serialise(char d, int s) {
	int c;
	switch (d) {
		case 'n': c = 0; break;
		case 'e': c = 1; break;
		case 's': c = 2; break;
		case 'w': c = 3; break;
		default: exit(1000);
	}
	return (MAX_STEPS) * c + s;
}

const double EPS = 1e-8;
int get_answer(const vd& big_map, const vd& small_map) {
	vd res = all_dot_products(big_map, small_map);
	int ans = 0;
	for (double dp : res) {
		ans += (fabs(round(dp) - dp) < EPS);
	}
	return ans;
}

int main() {
	int N, M;
	cin >> N >> M;

	vd big_map(N);	
	for (int n = 0; n < N; ++n) {
		char d; int s;
		cin >> d;
		if (d == '?') {
			big_map[n] = 0;
		} else {
			cin >> s;
			big_map[n] = pow(RANDOM_NUMBER, serialise(d, s));
		}
	}
	
	vd small_map(M);
	for (int m = 0; m < M; ++m) {
		char d; int s;
		cin >> d;
		if (d == '?') {
			small_map[m] = 0;
		} else {
			cin >> s;
			small_map[m] = pow(RANDOM_NUMBER, -serialise(d, s));
		}
	}

	cout << get_answer(big_map, small_map) << endl;
}