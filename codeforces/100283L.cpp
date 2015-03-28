#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
char nextc(char s, int index, int mul, int add) {
  return char(((s - 'a') * mul + index * add) % 26 + 'a');
}
string cons(string& s, int& mul, int& add) {
  mul %= 26;
  add %= 26;
  string res;
  int f = 1;
  for (int i = 1; i < 5555 && f; ++i) {
    s += nextc(s[i - 1], i, mul, add);
    for (int j = 26; i - j >= 0 && f; j += 26) {
      if (s[i] == s[i - j]) {        
        res = s.substr(i - j, j);
        s.resize(i - j);
        f = 0;
      }
    }
  }
  return res;
}
void cont(string& s, int& mul, int& add, int& len) {
  mul %= 26;
  add %= 26;
  for (int i = 1; i < len; ++i) s += nextc(s[i - 1], i, mul, add);
}
int main() {
  freopen("mahdi.in", "r", stdin);
  int T, nCase = 0;
  cin >> T;
  while (T--) {
    string ss, str;
    int sl, sm, sa;
    cin >> ss >> sl >> sm >> sa;
    str = cons(ss, sm, sa);
    int n;
    cin >> n;
    string ts;
    int tl, tm, ta;
    int res, si, ti, r1;
    int sll;
    cout << "Case " << ++nCase << ":\n";
    for (int i = 0; i < n; ++i) {
      cin >> ts >> tl >> tm >> ta;
      cont(ts, tm, ta, tl);
      si = 0, ti = 0;
      sll = sl, r1 = 0;
      res = 1;
      while (ti < tl && si < ss.length()) {
        if (sll == 0) {
          res = 0;
          break;
        }
        if (ts[ti] == ss[si]) ti++;
        si++;
        sll--;
      }
      while (ti < tl) {
        if (sll == 0) {
          res = 0;
          break;
        }
        if (si >= str.length()) {
          si = 0;
          if (!r1) r1 = 1;
          else {
            res = 0;
            break;
          }
        }
        if (ts[ti] == str[si]) {
          ti++;
          r1 = 0;
        }
        si++;
        sll--;
      }
      if (res) cout << "BRAVO\n";
      else cout << "REPEAT\n";
    }
  }
}