#include <bits/stdc++.h>
using namespace std;

using ll = __int128;
template <class T>
class Rational { // May need to use __int128 if doing multiple calculation steps
                 // on 10^9 size numbers.
  public:
    T num, den;
    Rational(T _num):num(_num), den(1) {}
    Rational(T _num, T _den):num(_num / __gcd(_num, _den)), den(_den / __gcd(_num, _den)) {}
    Rational operator * (const Rational& other) const {
      T new_num = num * other.num;
      T new_den = den * other.den;
      return Rational(new_num, new_den);
    }
    Rational operator / (const Rational& other) const {
      return *this * Rational(other.den, other.num); 
    }
    Rational operator + (const Rational& other) const {
      T new_den = den * other.den;
      T new_num = (other.den * num + den * other.num);
      return Rational(new_num, new_den);
    }
    Rational operator - (const Rational& other) const {
      T new_den = den * other.den;
      T new_num = (other.den * num - den * other.num);
      return Rational(new_num, new_den);
    }
    bool operator == (const Rational& other) const {
        return den == other.den && num == other.num;
    }
};

int main() {
    srand(time(0));
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N; cin >> N;
        vector<pair<ll, ll>> ants(N);
        for (int n = 0; n < N; ++n) {
            int x, y; cin >> x >> y;
            ants[n].first = x;
            ants[n].second = y;
        }

        const int TRIALS = 70;
        int maxi = 0;
        for (int tri = 0; tri < TRIALS; ++tri) {
            int i = rand() % N;
            int j = rand() % N; while (j == i) j = rand() % N;

            int on_line = 0;
            if (ants[i].first == ants[j].first) {
                for (const auto &[x, y] : ants) {
                    on_line += x == ants[i].first;
                }
            } else {
                const Rational<ll> m{(ants[i].second - ants[j].second), (ants[i].first - ants[j].first)};
                const Rational<ll> c = Rational<ll>{(ants[i].second)} - m * Rational<ll>{ants[i].first};

                for (const auto &[x, y] : ants) {
                    on_line += (Rational<ll>{y} == (m * x + c));
                }
            }
            
            maxi = max(maxi, on_line);
        }
        
        int ans = N - maxi;
        cout << "Case #" << t << ": " << ans << endl; 
    }
    return 0;
}
