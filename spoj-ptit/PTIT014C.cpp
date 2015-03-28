#include <algorithm>
#include <cassert>
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
 
char s[1010][33];
int dp[33][33];
 
int solve(int i, int j, int x, int y) {  
  if (x < 0) return 0;
  if (y < 0) return 0;
  int& res = dp[x][y];
  if (res != -1) return res;
  if (s[i][x] == s[j][y]) return res = solve(i, j, x - 1, y - 1) + 1;
  return res = std::max(solve(i, j, x - 1, y), solve(i, j, x, y - 1));
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i]);
    int ans = -1;
    for (int i = 1; i < n; ++i)
      for (int j = i + 1; j <= n; ++j) {
        memset(dp, -1, sizeof(dp));
        int x = strlen(s[i]);
        int y = strlen(s[j]);        
        int v = solve(i, j, x - 1, y - 1);
        if (ans == -1 || ans < v)
          ans = v;
      }
    assert(ans != -1);
    printf("%d\n", ans);
  }
} 