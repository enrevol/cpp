#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int a[10101], b[10101];
int dp[1010][1010];
 
int solve(int x, int y) {
  if (x <= 0) return 0;
  if (y <= 0) return 0;
  int& res = dp[x][y];
  if (res != -1) return res;
  if (a[x] == b[y]) return res = solve(x - 2, y - 2) + 1;
  return res = std::max(solve(x - 1, y), solve(x, y - 1));
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  int m, n;
  scanf("%d %d", &m, &n);
  for (int i = 1; i <= m; ++i)
    scanf("%d", a + i);
  for (int i = 1; i <= n; ++i)
    scanf("%d", b + i);
  printf("%d", solve(m, n));
} 