#include <bits/stdc++.h>
using namespace std;

typedef array<array<double,2>,2> Mat;
const Mat transitions = {0.5,0.5,1,0};


Mat matMul(Mat a, Mat b) {
    double x = a[0][0] * b[0][0] + a[0][1] * b[1][0];
    double y = a[0][0] * b[0][1] + a[0][1] * b[1][1];
    double z = a[1][0] * b[0][0] + a[1][1] * b[1][0];
    double w = a[1][0] * b[0][1] + a[1][1] * b[1][1];
    return array<array<double,2>,2>({array<double,2>({x,y}),array<double,2>({z,w})});
}

Mat matrixPower(const Mat matrix, int power) {
    if (power == 1) {
        return matrix;
    }
    else {
        if (power % 2 == 0)
            return matrixPower(matMul(matrix,matrix),power/2); 
        else 
            return matMul(matrix, matrixPower(matrix,power-1));
    }
}


int main() {
    int n;
    scanf("%d",&n);
    if (n == 1) {
        cout << "100 0" << endl;
    }
    else if (n == 2) {
        cout << "0 100" << endl;
    }
    else {
        double piTato = 1-matrixPower(transitions,n-2)[0][0];
        double tauMato = 1-piTato;
        cout << setprecision(10) << piTato*100 << " " << tauMato*100 << endl; 
    }

    return 0;
}