#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[1010][1010];
int ans[1010][1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  for (int i = 1; i <= n; ++i) {
    for (int j = 1, x = 0; j <= m; ++j)
      if (s[i][j] == '#') x = 0; else ans[i][j] += ++x;    
    for (int j = m, x=  0; j >= 1; --j)
      if (s[i][j] == '#') x = 0; else ans[i][j] += ++x;
  }
  for (int j = 1; j <= m; ++j) {
    for (int i = 1, x = 0; i <= n; ++i)
      if (s[i][j] == '#') x = 0; else ans[i][j] += ++x;
    for (int i = n, x = 0; i >= 1; --i)
      if (s[i][j] == '#') x = 0; else ans[i][j] += ++x;
  }
  for (int j = 1; j <= m; ++j) {
    for (int k = 0, x = 0; 1 + k <= n && j + k <= m; ++k)
      if (s[1 + k][j + k] == '#') x = 0; else ans[1 + k][j + k] += ++x;
    for (int k = 0, x = 0; 1 + k <= n && j - k >= 1; ++k)
      if (s[1 + k][j - k] == '#') x = 0; else ans[1 + k][j - k] += ++x;    
    for (int k = 0, x = 0; n - k >= 1 && j + k <= m; ++k)
      if (s[n - k][j + k] == '#') x = 0; else ans[n - k][j + k] += ++x;
    for (int k = 0, x = 0; n - k >= 1 && j - k >= 1; ++k)
      if (s[n - k][j - k] == '#') x = 0; else ans[n - k][j - k] += ++x;
  }
  for (int i = 2; i <= n; ++i) {
    for (int k = 0, x = 0; i + k <= n && 1 + k <= m; ++k)
      if (s[i + k][1 + k] == '#') x = 0; else ans[i + k][1 + k] += ++x;
    for (int k = 0, x = 0; i + k <= n && m - k >= 1; ++k)
      if (s[i + k][m - k] == '#') x = 0; else ans[i + k][m - k] += ++x;    
  }
  for (int i = 1; i < n; ++i) {
    for (int k = 0, x = 0; i - k >= 1 && 1 + k <= m; ++k)
      if (s[i - k][1 + k] == '#') x = 0; else ans[i - k][1 + k] += ++x;
    for (int k = 0, x = 0; i - k >= 1 && m - k >= 1; ++k)
      if (s[i - k][m - k] == '#') x = 0; else ans[i - k][m - k] += ++x;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      if (s[i][j] == '#') printf("0 ");
      else printf("%d ", ans[i][j] - 7);
    putchar('\n');
  }
}