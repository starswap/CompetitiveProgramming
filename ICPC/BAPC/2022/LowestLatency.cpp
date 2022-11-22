#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x;
    double y;
    double z;

    Point(double x, double y, double z):x(x),y(y),z(z) {};

};

double dist(Point a, Point b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z - b.z)*(a.z - b.z));
}

const int BOX_SIZE = 10000000;
const int X_MAX = 1000000000;
const int DIM = X_MAX/BOX_SIZE;
const double INF = 1e9;

int dx[] = {-1,-1,-1,-1,-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int dy[] = {-1,-1,-1, 0, 0, 0, 1, 1, 1,-1,-1,-1, 0, 0, 0, 1, 1, 1,-1,-1,-1, 0, 0, 0, 1, 1, 1};
int dz[] = {-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1,-1, 0, 1};

int main() {
    int n;
    scanf("%d",&n);

    vector<vector<vector<vector<Point>>>> gridCells(DIM,vector<vector<vector<Point>>>(DIM,vector<vector<Point>>(DIM,vector<Point>())));

    for (int i=0;i<n;++i) {
        double x,y,z;
        scanf("%lf %lf %lf",&x,&y,&z);
        gridCells[x/BOX_SIZE][y/BOX_SIZE][z/BOX_SIZE].push_back(Point(x,y,z));
    }

    double bestDist = INF;
    for (int gx=0;gx<DIM;gx++) {
        for (int gy=0;gy<DIM;gy++) {
            for (int gz=0;gz<DIM;gz++) {
                for (int i=0;i<27;++i) {
                    
                    if (gx + dx[i] >= 0 && gx + dx[i] < DIM && gy + dy[i] >= 0 && gy + dy[i] < DIM && gz + dz[i] >= 0 && gz + dz[i] < DIM) {
                        for (int p1I=0;p1I<gridCells[gx+dx[i]][gy+dy[i]][gz+dz[i]].size();p1I++) {
                            for (int p2I=0;p2I<gridCells[gx][gy][gz].size();p2I++) {
                                if (p1I == p2I && i == 13) continue;
                                // cout << dist(gridCells[gx+dx[i]][gy+dy[i]][gz+dz[i]][p1I],gridCells[gx][gy][gz][p2I]) << endl;
                                bestDist = min(bestDist,dist(gridCells[gx+dx[i]][gy+dy[i]][gz+dz[i]][p1I],gridCells[gx][gy][gz][p2I]));
                            }
                        }
                    }
                }
            }
        }
    }

    cout << setprecision(10) << endl;
    cout << bestDist << endl;

    return 0;
}