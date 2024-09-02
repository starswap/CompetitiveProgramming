#include <bits/stdc++.h>
using namespace std;

int n_berries = 0;
int N; 

vector<set<int>> scores;
vector<int> node_score;
vector<bool> berry;
vector<int> erik_scores(2, 0);

void process_guess(int GG, bool granpad) {
    int total_encountered = 0;
    int i;
    for (i = min(N - 1, GG + 3); i >= GG; --i) {
        n_berries -= berry[i];
        total_encountered += berry[i];
        berry[i] = false;
        scores[node_score[i]].erase(i);
        node_score[i] -= total_encountered;
        scores[node_score[i]].insert(i);
    }
    erik_scores[granpad] += total_encountered;

    for (;i >= 0 && i >= GG - 3; --i) {
        total_encountered -= berry[i + 4];
        scores[node_score[i]].erase(i);
        node_score[i] -= total_encountered;
        scores[node_score[i]].insert(i);
    }
}

// for stage in range(4, 0, -1):
//      while can_get_i_berries:
//          for each set with no gap of 4 
//          compute grundy number
//          xor grundy numbers
//          tells us which pile we need to play on
//          

int main() {
    cin >> N;
    string s; cin >> s;
    berry.assign(N, false);

    for (int i = 0; i < N; ++i) {
        berry[i] = (s[i] == 'b');
        n_berries += (s[i] == 'b');
    }

    scores.assign(5, set<int>());
    node_score.assign(N, 0);
    int in_window = 0;
    for (int i = 0; i < 4; ++i) {
        in_window += berry[i];
    }

    for (int i = 0; i < N; ++i) {
        scores[in_window].insert(i);
        node_score[i] = in_window;
        in_window -= berry[i];
        if (i + 4 < N) in_window += berry[i + 4]; 
    }


    while (n_berries > 0) {
        int GG;
        cin >> GG;
        GG--;

        process_guess(GG, true);
        if (n_berries <= 0) break;
        
        int amt = 3;
        while (scores[amt].size() <= 0) {amt--;}
        int guess = *scores[amt].begin();
        cout << guess + 1 << endl;
        process_guess(guess, false);
    }
    
    assert(erik_scores[false] >= erik_scores[true]);
    
    return 0;
} x