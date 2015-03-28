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
 
int a[22];
bool b[2020][2020];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int s = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    s += a[i];
  }
  b[0][0] = 1;
  for (int i = 1; i <= n; ++i)
    for (int j = s; j >= 0; --j)
      for (int k = s; k >= 0; --k)
        if (b[j][k]) {
          b[j + a[i]][k] = 1;
          b[j][k + a[i]] = 1;
        }
  int ans = s;
  for (int i = 0; i <= s; ++i)
    for (int j = 0; j <= s; ++j)
      if (b[i][j]) {
        int k = s - i - j;
        int x = std::max(i, std::max(j, k));
        //fprintf(stderr, "%d %d %d\n", i, j, k);
        ans = std::min(ans, x);
      }
  printf("%d", ans);
}