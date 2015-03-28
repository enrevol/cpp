#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
int ss[26];
int main() {
#ifdef ONLINE_JUDGE
  freopen("arrange.in", "r", stdin);
  freopen("arrange.out", "w", stdout);
#endif
  int n;
  cin >> n;
  string s;
  for (int i = 0; i < n; ++i) {
    cin >> s;
    ss[s[0] - 'A']++;
  }
  int ans = 0;
  for (int i = 0; i < 26; ++i) {
    if (ss[i]) ans++;
    else break;
  }
  cout << ans;
}