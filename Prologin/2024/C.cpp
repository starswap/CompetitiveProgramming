#include <bits/stdc++.h>
using namespace std;

deque<string> ouro;
stack<string> villes_mangees;
bool renverse = false;

void agir(char action) {
    if (action == 'A') {
        if (!renverse) {
            ouro.push_back(ouro.front());
            ouro.pop_front();
        } else {
            ouro.push_front(ouro.back());
            ouro.pop_back();
        }
    } else if (action == 'M') {
        if (!renverse) {
            villes_mangees.push(ouro.front());
            ouro.pop_front();
        } else {
            villes_mangees.push(ouro.back());
            ouro.pop_back();
        }
    } else if (action == 'R') {
        renverse = !renverse;
    } else if (action == 'C') {
        if (!renverse) {
            ouro.push_front(villes_mangees.top());
            villes_mangees.pop();
        } else {
            ouro.push_back(villes_mangees.top());
            villes_mangees.pop();
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    for (int n = 0; n < N; ++n) {
        string ville; cin >> ville;
        ouro.push_back(ville);
    }
    vector<char> actions(M);
    for (int m = 0; m < M; ++m) {
        cin >> actions[m];
    }

    for (int m = 0; m < M; ++m) {
        agir(actions[m]);
    }

    if (renverse) {
        while (!ouro.empty()) {
            cout << ouro.back() << endl;
            ouro.pop_back();
        }
    } else {
        while (!ouro.empty()) {
            cout << ouro.front() << endl;
            ouro.pop_front();
        }
    }
    return 0;
}