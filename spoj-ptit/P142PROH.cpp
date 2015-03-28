#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int w = 10;
 
bool a[w + 10][w + 10], x[w + 10], y[w + 10];
char s[w + 10][w + 10];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int r, c;
  scanf("%d %d", &r, &c);
  for (int i = 1; i <= r; ++i) {
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= c; ++j)
      if (s[i][j] == 'S')
        y[j] = x[i] = true;
  }
  for (int i = 1; i <= r; ++i)
    if (!x[i])
      for (int j = 1; j <= c; ++j)
        a[i][j] = true;
  for (int i = 1; i <= c; ++i)
    if (!y[i])
      for (int j = 1; j <= r; ++j)
        a[j][i] = true;
  int ans = 0;
  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= c; ++j)
      ans += a[i][j];
  printf("%d", ans);
} 