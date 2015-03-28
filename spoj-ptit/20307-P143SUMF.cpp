#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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
 
const int N = 55;
 
int a[N][N], sum[N][N];
std::map<int, int> map;
 
inline int get(int x1, int y1, int x2, int y2) {
  return sum[x2][y2] - sum[x1 - 1][y2] - sum[x2][y1 - 1] + sum[x1 - 1][y1 - 1];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%d", a[i] + j);
      sum[i][j] = a[i][j] + sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
    }
  int ans = 0;
  for (int i = 1; i < n; ++i)
    for (int j = 1; j < n; ++j) {      
      map.clear();
      for (int x = 1; x <= i; ++x)
        for (int y = 1; y <= j; ++y)
          ++map[get(x, y, i, j)];
      for (int x = i + 1; x <= n; ++x)
        for (int y = j + 1; y <= n; ++y)
          ans += map[get(i + 1, j + 1, x, y)];
      map.clear();
      for (int x = 1; x <= i; ++x)
        for (int y = j + 1; y <= n; ++y)
          ++map[get(x, j + 1, i, y)];
      for (int x = i + 1; x <= n; ++x)
        for (int y = 1; y <= j; ++y)
          ans += map[get(i + 1, y, x, j)];
    }
  printf("%d", ans);
}