#include <bits/stdc++.h>
using namespace std;

const double PI  = 3.14159265358979323846264338327950288419;
const double EPS = 1e-9;

int main() {
    long long a,b;
    cin >> a >> b;
    a--;
    b--;

    long long numWays = (a == b) ? 1 : 2;

    unordered_set<long long> squares;
    // vector<pair<int,int>> triplesA;
    vector<double> anglesA;
    for (long long i=1;i<a;++i) {
        squares.insert(i*i);   
    }
    for (long long i=1;i<a;++i) {
        if (i * i > (a * a) / 2) {break;}
        if (squares.contains(a * a - i * i)) {
            // triplesA.emplace_back(i,static_cast<int>(sqrt(a * a - i * i)));
            int x1 = i;
            int x2 = static_cast<long long>(sqrt(a * a - i * i));
            // cout << x1 << "," << x2 << "=" << a << endl;

            anglesA.emplace_back(atan(static_cast<double>(x1)/static_cast<double>(x2)));
            anglesA.emplace_back(atan(static_cast<double>(x2)/static_cast<double>(x1)));
        }
    }


    squares.clear();
    // vector<pair<int,int>> triplesB;
    vector<double> anglesB;

    for (long long i=1;i<b;++i) {
        squares.insert(i*i);   
    }
    for (long long i=1;i<b;++i) {
        if (i * i > (b * b) / 2) {break;}
        if (squares.contains(b*b - i*i)) {
            int x1 = i;
            int x2 = static_cast<int>(sqrt(b * b - i * i));
            // cout << x1 << "," << x2 << "=" << b << endl;
            anglesB.emplace_back(atan(static_cast<double>(x1)/static_cast<double>(x2)));
            anglesB.emplace_back(atan(static_cast<double>(x2)/static_cast<double>(x1)));
        }
    }

    sort(anglesA.begin(),anglesA.end());
    sort(anglesB.begin(),anglesB.end());

    long long ai = 0;
    long long bi = anglesB.size()-1;

    while (!(bi < 0 || ai >= anglesA.size())) {
        if (anglesA[ai] + anglesB[bi] > PI/2 + EPS) {
            bi--;
        }
        else if (anglesA[ai] + anglesB[bi] < PI/2 - EPS) {
            ai++;
        }
        else {
            bi--;
            ai++;
            if (a != b) {
                numWays += 2;
            }
            else {
                // cout << "[a" << endl;
                numWays += 1;
            }
        }
    }

    cout << numWays << endl;
    

}