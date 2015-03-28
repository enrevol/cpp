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
 
int a[1010][1010];
int s[1010][1010];
int r[1010][1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  int ans = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      scanf("%d", a[i] + j);
      r[i][j] = r[i][j - 1] + a[i][j];
      s[i][j] = s[i - 1][j] + r[i][j];
      if (i >= k && j >= k) {
        int tot = s[i][j] + s[i - k][j - k] - s[i - k][j] - s[i][j - k];
        if (tot > ans) ans = tot;          
      }
    }
  printf("%d", ans);
} 