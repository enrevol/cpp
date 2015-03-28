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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }
 
using namespace std;
 
const int N = 110;
const int INF = 0x3C3C3C3C;

char s[N];
int n, m, p, r[N][N], b[N][N], rr[N][N], bb[N][N], dp[N][N], best1[N][N], best2[N][N];
 
inline int calc(int a[N][N], int x1, int y1, int x2, int y2) {
  return a[x2][y2] + a[x1 - 1][y1 - 1] - a[x1 - 1][y2] - a[x2][y1 - 1];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d %d %d", &n, &m, &p);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + 1);
    for (int j = 1; j <= m; ++j) {
      r[i][j] = r[i - 1][j] + r[i][j - 1] - r[i - 1][j - 1] + (s[j] == '2');
      b[i][j] = b[i - 1][j] + b[i][j - 1] - b[i - 1][j - 1] + (s[j] == '1');
    }    
  }
  for (int i = 1; i <= n - p + 1; ++i)
    for (int j = 1; j <= m - p + 1; ++j) {
      bb[i][j] = calc(b, i, j, i + p - 1, j + p - 1);
      rr[i][j] = calc(r, i, j, i + p - 1, j + p - 1);
    }
  memset(best1, 0x3C, sizeof(best1));
  memset(best2, 0x3C, sizeof(best2));
  for (int i = 1; i <= n - p + 1; ++i)
    for (int j = 1; j <= m - p + 1; ++j)
      best1[i][j] = min(rr[i][j] - bb[i][j], min(best1[i - 1][j], best1[i][j - 1]));
  for (int i = n - p + 1; i >= 1; --i)
    for (int j = m - p + 1; j >= 1; --j)
      best2[i][j] = min(rr[i][j] - bb[i][j], min(best2[i + 1][j], best2[i][j + 1]));
  memset(dp, 0x3C, sizeof(dp));
  for (int i = 1; i <= n - p + 1; ++i) {
    for (int j = 1; j <= m - p + 1; ++j) {
      int r1 = rr[i][j];
      int b1 = bb[i][j];
      int best = min(best2[1][j + p], best2[i + p][1]);
      if (i - p >= 1) best = min(best, best1[i - p][m - p + 1]);
      if (j - p >= 1) best = min(best, best1[n - p + 1][j - p]);
      dp[i][j] = min(dp[i][j], b[n][m] + r1 - b1 + best);
      for (int ii = i; ii <= i + p - 1 && ii <= n - p + 1; ++ii)
        for (int jj = max(1, j - p + 1); jj <= m - p + 1 && jj <= j + p - 1; ++jj) {
          int r2 = rr[ii][jj];
          int b2 = bb[ii][jj];
          int b3 = 0, r3 = 0;
          if (ii <= i + p - 1) {
            if (j <= jj + p - 1 && jj + p - 1 <= j + p - 1) {
              b3 = calc(b, ii, j, i + p - 1, jj + p - 1);
              r3 = calc(r, ii, j, i + p - 1, jj + p - 1);
            } else if (j <= jj && jj <= j + p - 1) {
              b3 = calc(b, ii, jj, i + p - 1, j + p - 1);
              r3 = calc(r, ii, jj, i + p - 1, j + p - 1);
            }
          }
          int v = b3 + b[n][m] - (b1 + b2 - b3) + r1 + r2 - (r3 << 1);
//          printf("%d %d %d %d = %d\n", i, j, ii, jj, v);
          dp[i][j] = min(dp[i][j], v);
          dp[ii][jj] = min(dp[ii][jj], v);
        }
      printf("%d ", dp[i][j]);
    }
    putchar('\n');
  }
}
