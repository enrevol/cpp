#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
int a[111][111], b[111][111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)  
      scanf("%d", a[i] + j);  
  for (int i = 1; i <= n; ++i)
    b[i][1] = a[i][1];
  for (int j = 2; j <= m; ++j) {
    for (int i = 1; i <= n; ++i) {
      int val = b[i][j - 1];
      if (i > 1) val = std::max(val, b[i - 1][j - 1]);
      if (i < n) val = std::max(val, b[i + 1][j - 1]);
      b[i][j] = val + a[i][j];
    }
  }
  int ans = b[1][m];
  for (int i = 2; i <= n; ++i)
    if (b[i][m] > ans) ans = b[i][m];
  printf("%d", ans);
} 