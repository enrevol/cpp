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
 
int dp[1010][1010];
int ar[1010][1010];
 
int a[1010];
int pos[1010];
 
int solve(int f, int t) {
  if (f == t) return pos[f];
  int& res = dp[f][t];
  if (res > 0) return res;
  int sz = t - f + 1;
  int v1 = solve(f + 1, t) + ar[f][t] * sz;
  int v2 = solve(f, t - 1) + ar[t][f] * sz;
  return res = std::min(v1, v2);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    pos[a[i]] = i;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = i + 1, v = pos[i]; j <= n; ++j) {
      if (pos[j] < pos[i]) --v;
      ar[i][j] = v;
    }
    for (int j = i - 1, v = pos[i]; j >= 1; --j) {
      if (pos[j] < pos[i]) --v;
      ar[i][j] = v;
    }
  }  
  printf("%d", solve(1, n));
}