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
 
const int w = 4e2;
 
int a[w + 10][w + 10];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", a[i] + j);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int x = 0, y = 0;
      for (int k = 1; i - k >= 1 && j - k >= 1 && i + k <= n && j + k <= n; ++k) {
        x += a[i - k][j - k] + a[i + k][j + k];
        y += a[i - k][j + k] + a[i + k][j - k];
        if (x - y > ans) ans = x - y;
      }
    }
  for (int i = 1; i < n; ++i)
    for (int j = 1; j < n; ++j) {
      int x = 0, y = 0;
      for (int k = 0; i - k >= 1 && j - k >= 1 && i + k + 1 <= n && j + k + 1 <= n; ++k) {
        x += a[i - k][j - k] + a[i + k + 1][j + k + 1];
        y += a[i - k][j + k + 1] + a[i + k + 1][j - k];
        if (x - y > ans) ans = x - y;
      }
    }  
  printf("%d", ans);
} 