#include <bits/stdc++.h>
using namespace std;

int N, K;
int solve(const set<vector<int>>& cards) {
    int total = 0; 
    for (const vector<int>& card : cards) {
        int middle = 0;
        for (const vector<int>& card2 : cards) {
            if (card != card2) {
                vector<int> card3(K);
                for (int k=0;k<K;++k) {
                    card3[k] = (card[k] == card2[k]) ? card[k] : (3 - card[k] - card2[k]);
                }
                middle += cards.count(card3);
            }
        }
        // cout << middle << endl;
        middle /= 2; // we counted each one twice.
        total += (middle*(middle - 1)/2);
    }
    return total;
}


int main() {
    cin >> N >> K;
    set<vector<int>> cards;

    for (int n=0;n<N;++n) {
        vector<int> thisCard(K);
        for (int k=0;k<K;++k) {
            cin >> thisCard[k];
        }
        cards.insert(thisCard);
    }
    cout << solve(cards) << endl;        
}