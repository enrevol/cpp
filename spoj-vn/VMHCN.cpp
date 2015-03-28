#include <algorithm>
#include <bitset>
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
 
const int N = 2010;
 
int n, m;
char s[N][N];
bool mark[N][N];
 
int solve(int fx, int fy, int tx, int ty) {
  //fprintf(stderr, "[%d..%d][%d..%d]\n", fx, tx, fy, ty);
  int res = 0;
  if (tx - fx + 1 >= 5 && ty - fy + 1 >= 5) {
    for (int i = fx + 1; i < tx; ++i)
      for (int j = fy + 1; j < ty; ++j) {
        if (mark[i][j]) continue;
        mark[i][j] = 1;
        if (s[i][j] == 'o') {
          int xx = i, yy = j;
          while (yy + 1 < ty && s[xx][yy + 1] == 'o') ++yy;
          while (xx + 1 < tx && s[xx + 1][yy] == 'o') ++xx;
          int val = solve(i, j, xx, yy) + 1;
          if (val > res) res = val;
        }
      }
  }
  for (int i = fx; i <= tx; ++i) mark[i][fy] = mark[i][ty] = 1;
  for (int i = fy; i <= ty; ++i) mark[fx][i] = mark[tx][i] = 1;
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i) scanf("%s", s[i] + 1);
    memset(mark, 0, sizeof(mark));
    int ans = solve(0, 0, n + 1, m + 1);
    printf("%d\n", ans);
  }
}
