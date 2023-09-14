#include <bits/stdc++.h>
using namespace std;

void advanceMyPointer(int& ptr, const string& str, char c, int start) {
    ptr = start;
    while (ptr < str.size() && str[ptr] != c) { ptr++; }
}

int get_score(int a, int b) { return (a + b) / 2; }

int main() {
    int N;
    cin >> N;
    string str1, str2;
    cin >> str1 >> str2;

    vector<pair<int, char>> str_1_set = { {0, 'A'}, {0, 'C'}, {0, 'G'}, {0, 'T'} };
    vector<pair<int, char>> str_2_set = { {0, 'A'}, {0, 'C'}, {0, 'G'}, {0, 'T'} };
    
    for (auto &[cnt, chr] : str_1_set) {
        advanceMyPointer(cnt, str1, chr, 0);
    }

    for (auto &[cnt, chr] : str_2_set) {
        advanceMyPointer(cnt, str2, chr, 0);
    }

    int s = 0;
    int t = 0;

    vector<char> substr;
    while (s < str1.size() && t < str2.size()) {
        int best_score = 1000000000;
        int best_i = 0; 
        
        for (int i = 0; i < 4; ++i) {
            int score = get_score(str_1_set[i].first, str_2_set[i].first);
            if (score < best_score) {
                best_score = score;
                best_i = i;
            }
        }

        if (str_1_set[best_i].first >= str1.size() || str_2_set[best_i].first >= str2.size()) {break;}

        substr.push_back(str_1_set[best_i].second);
        s = str_1_set[best_i].first;
        t = str_2_set[best_i].first;
        for (int i = 0; i < 4; ++i) {
            advanceMyPointer(str_1_set[i].first, str1, str_1_set[i].second, s + 1);
            advanceMyPointer(str_2_set[i].first, str2, str_2_set[i].second, t + 1);
        }
    }

    for (char c : substr) {
        cout << c;
    }
    cout << endl;


    return 0;
}