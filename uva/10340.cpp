#include <iostream>
#include <string>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  string s1, s2;
  while (cin >> s1 >> s2) {
    int i = 0, j = 0;
    while (i < s1.size() && j < s2.size()) {
      if (s1[i] == s2[j]) i++;
      j++;
    }
    if (i == s1.size()) cout << "Yes\n";
    else cout << "No\n";
  }
}