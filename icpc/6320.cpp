#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[101010], t[101010];
int ds[101010][26], dt[26];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s %s", s + 1, t + 1);
    int ns = strlen(s + 1);
    int nt = strlen(t + 1);
    for (int i = 1; i <= ns; ++i) {
      for (int j = 0; j < 26; ++j)
        ds[i][j] = ds[i - 1][j];
      ++ds[i][s[i] - 'a'];
    }
    memset(dt, 0, sizeof(dt));
    for (int i = 1; i <= nt; ++i)
      ++dt[t[i] - 'a'];
    bool f = false;
    for (int i = nt; i <= ns && !f; ++i) {
      f = true;
      for (int j = 0; j < 26 && f; ++j)
        f = ds[i][j] - ds[i - nt][j] == dt[j];
    }
    puts(f ? "YES" : "NO");
  }
}