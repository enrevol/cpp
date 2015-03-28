#include <cctype>
#include <cstdio>
#include <iostream>
#include <string>
typedef long long LL;
using namespace std;
int main() {
#ifdef ONLINE_JUDGE
  freopen("java_c.in", "r", stdin);
  freopen("java_c.out", "w", stdout);
#endif
  string s, ans = "";
  cin >> s;
  int f = 1;
  int cpp = 0;
  int up = 0;  
  for (int i = 0; i < s.size(); ++i) {
    if (s[i] == '_') cpp = 1;
    if (isupper(s[i])) up = 1;
    if (i > 0 && s[i] == '_' && s[i - 1] == '_') f = 0;
  }
  if (!f) {
    cout << "Error!";
  } else {    
    if (cpp) {
      if (s[0] == '_' || s[s.size() - 1] == '_') {
        cout << "Error!";
      } else {
        if (up) {
          cout << "Error!";
        } else {
          cout << s[0];
          for (int i = 1; i < s.size(); ++i) {
            if (s[i] == '_') {
              cout << char(toupper(s[i + 1]));
              i++;
            } else {
              cout << s[i];
            }
          }
        }
      }
    } else {
      if (isupper(s[0])) {
        cout << "Error!";
      } else {
        cout << s[0];
        for (int i = 1; i < s.size(); ++i) {
          if (isupper(s[i])) {
            cout << '_' << char(tolower(s[i]));
          } else {
            cout << s[i];
          }
        }
      }
    }
  }
}