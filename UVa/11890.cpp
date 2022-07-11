#include <bits/stdc++.h>
using namespace std;

int main() {
  int T; cin >> T;
  while (T--) {
    string expression; cin >> expression;
    int N; cin >> N;
    multiset<int> values;
    for (int n=0;n<N;++n) {
      int value;
      cin >> value;
      values.insert(value);
    }
    vector<char> withoutBrackets;
    stack<bool> minusStack;
    minusStack.push(false);
    for (int i=0;i<expression.size();++i) {
      if (expression[i] == '(') {
        if (i > 0 && expression[i-1] == '-'){
          minusStack.push(!minusStack.top());  
        } else {
          minusStack.push(minusStack.top());
        }
      }
      else if (expression[i] == ')') {
        minusStack.pop();
      }
      else if (expression[i] == '-') {
        withoutBrackets.push_back((!minusStack.top()) ? '-' : '+');
      }
      else if (expression[i] == '+') {
        withoutBrackets.push_back((minusStack.top()) ? '-' : '+');
      }
      else if (expression[i] == 'x') {
        withoutBrackets.push_back('x');
      }
      else {
        cout << "Malformed Expression" << endl;
      }
    }

    int total = 0;
    for (int i=0;i<withoutBrackets.size();i+=2) {
      if (withoutBrackets[i] == '+') {
        total += *prev(values.end());
        values.erase(prev(values.end()));
      } else if (withoutBrackets[i] == '-') {
        total -= *values.begin();
        values.erase(values.begin());
      }
      else if (withoutBrackets[i] == 'x') {
        total += *prev(values.end());
        values.erase(prev(values.end()));        
        i -= 1;
      }
      else {
        cout << "Mistake in program" << endl;
      }
    }

    cout << total << endl;

  }

  
  
  return 0;
}