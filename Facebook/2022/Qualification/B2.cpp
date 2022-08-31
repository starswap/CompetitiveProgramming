//Alternatively use a BFS. We then don't need to repeat the search from all of the initially failing trees because they can all be added to the same queue.

#include <bits/stdc++.h>
using namespace std;

int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};
int R,C;

bool propagate(int r,int c, vector<vector<char>>& grid, vector<vector<int>> &failingNeighbours) {
  //returns possible?
  if (grid[r][c] == '#') return true;
  if (grid[r][c] == '^') return false; 

  bool result = true;
  grid[r][c] = '#';
  for (int i=0;i<4;++i) {
    int neighR = r+dy[i];
    int neighC = c+dx[i];

    if (neighR >= 0 && neighR < R && neighC >= 0 && neighC < C) {
      failingNeighbours[neighR][neighC]++;
      if (failingNeighbours[neighR][neighC] >= 3) {
        result = result && propagate(neighR,neighC,grid,failingNeighbours);
      }
    }
  }
  return result;
}

int main() {
  int T;
  scanf("%d",&T);
  for (int t=0;t<T;++t) {
    scanf("%d %d",&R,&C);

    vector<vector<char>> grid(R,vector<char>(C,'.'));

    for (int r=0;r<R;++r) {
      string row;
      cin >> row;      
      for (int c=0;c<C;++c) {
        grid[r][c] = row[c];
      }
    }

    vector<pair<int,int>> fails;

    vector<vector<char>> gridInit(grid);
    vector<vector<int>> failingNeighbours(R,vector<int>(C));
    
    for (int r=0;r<R;++r) {
      for (int c=0;c<C;++c) {
        int numFailingNeighbours = 0;
        for (int i=0;i<4;++i) {
          int neighR = r+dy[i];
          int neighC = c+dx[i];
          if (neighR < 0 || neighR >= R || neighC < 0 || neighC >= C || grid[neighR][neighC] == '#')
            numFailingNeighbours += 1;          
        }
        if (numFailingNeighbours >= 3)
          fails.emplace_back(r,c);
        failingNeighbours[r][c] = numFailingNeighbours;
      }
    }


    bool possible = true;
    for (auto [r,c] : fails) {
      possible = possible && propagate(r,c,grid,failingNeighbours);
    }

    printf("Case #%d: ",t+1); 
    if (possible) {
      printf("Possible\n");
      for (int r=0;r<R;++r) {
        for (int c=0;c<C;++c) {
          if (gridInit[r][c] == '#') printf("#");
          else if (gridInit[r][c] == '^') printf("^");
          else if (gridInit[r][c] == '.' && grid[r][c] == '#') printf(".");
          else if (gridInit[r][c] == '.' && grid[r][c] == '.') printf("^");
          else {} // should not occur.
        }
        printf("\n");
      }
    }
    else {
      printf("Impossible\n");
    }
    
  }
  return 0;
}
