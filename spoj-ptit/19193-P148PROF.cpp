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
 
const int mod = 1e9 + 7;
 
int dp[101][101];
 
int solve(int n, int h) {
  int& res = dp[n][h];
  if (res != -1) return res;
  if (h == 0) return res = n;
  if (n == 0) return res = 0;
  return res = (solve(n - 1, h - 1) + solve(n - 1, h) + 1) % mod;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  int n, h;
  while(~scanf("%d %d", &n, &h))
    if (n | h) printf("%d\n", (solve(n, h > n ? n : h) + 1) % mod);
} 