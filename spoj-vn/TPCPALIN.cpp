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
 
const int N = 510;
const int MOD = 3210121;
 
int dp[2][N][N];
char s[N], t[N];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  scanf("%s %s", s + 1, t + 1);
  int sn = strlen(s + 1);
  int tn = strlen(t + 1);
  int h = (sn + tn) >> 1;
  for (int x = 0; x <= h; ++x)
    for (int y = 0; y <= h; ++y)
      dp[0][x][y] = 1;
  int f = 0;
  for (int L = h - 1; L >= 0; --L, f ^= 1) {
    for (int x = 0; x <= L; ++x) {
      int sf = x + 1;
      int tf = L - x + 1;
      for (int y = 0; y <= L; ++y) {
        int r = 0;        
        int st = sn - y;
        int tt = tn - (L - y);
        if (sf < st && s[sf] == s[st]) r += dp[f][x + 1][y + 1];
        if (tf < tt && t[tf] == t[tt]) r += dp[f][x][y];
        if (sf <= st && tf <= tt) {
          if (s[sf] == t[tt]) r += dp[f][x + 1][y];
          if (t[tf] == s[st]) r += dp[f][x][y + 1];
        }
        dp[f ^ 1][x][y] = r % MOD;
      }
    }
  }
  int ans = dp[f][0][0];
  printf("%d", ans);
}
