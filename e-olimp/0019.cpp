#include <iostream>
#include <string>
using namespace std;
int main() {
 string s;
 cin >> s;
 int ans = 0;
 for (int i = 0; i < (s.length() / 2 + (s.length() % 2)); ++i)
   ans += s[i] == s[s.length() - 1 - i];
 cout << ans << '\n';
}