#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int mx = 250;
 
struct ss {
  unsigned char s[mx + 5];
  ss() {
    for (int i = 1; i <= mx; ++i)
      s[i] = '0';
  }
  ss(int v) {
    int sz = 0;
    while (v) {
      s[++sz] = v % 10 + '0';
      v /= 10;
    }
    for (int i = sz + 1; i <= mx; ++i)
      s[i] = '0';
  }
} dp[2][111][111];
 
ss operator + (const ss& lhs, const ss& rhs) {
  ss res;
  unsigned char c = 0;
  for (int i = 1; i <= mx; ++i) {
    unsigned char v = c + lhs.s[i] + rhs.s[i] - ('0' << 1);
    c = 0;
    if (v >= 10) {
      v -= 10;
      c = 1;
    }
    res.s[i] = v + '0';
  }
  return res;
}
 
ss operator * (const ss& lhs, const ss& rhs) {
  ss res;
  unsigned char c = 0;  
  for (int i = 1; i <= mx >> 1; ++i) {
    c = 0;
    for (int j = 1; j <= mx >> 1; ++j) {
      unsigned char v = c + (res.s[i + j - 1] - '0') + (lhs.s[j] - '0') * (rhs.s[i] - '0');
      c = v / 10;
      res.s[i + j - 1] = v % 10 + '0';
    }
  }
  return res;
}
 
int sz[2][111];
int num[2];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i < n; ++i) {
    sz[i & 1][++num[i & 1]] = i;
    sz[i & 1][++num[i & 1]] = i;
  }
  sz[n & 1][++num[n & 1]] = n;
  std::sort(sz[0] + 1, sz[0] + num[0] + 1);
  std::sort(sz[1] + 1, sz[1] + num[1] + 1);
  for (int a = 0; a < 2; ++a) {
    for (int i = 0; i <= num[a]; ++i)
      dp[a][i][0] = ss(1);
    for (int i = 1; i <= num[a]; ++i)
      for (int j = 1; j <= i; ++j)
        dp[a][i][j] = dp[a][i - 1][j] + dp[a][i - 1][j - 1] * (sz[a][i] - (j - 1));
  }
  ss ans = 0;
  for (int i = 0; i <= k; ++i)
    if (i <= num[0] && k - i <= num[1])
      ans = ans + dp[0][num[0]][i] * dp[1][num[1]][k - i];
  int t = mx;
  while (t >= 2 && ans.s[t] == '0') --t;
  //printf("t = %d\n", t);
  for (int i = t; i >= 1; --i)
    putchar(ans.s[i]);
} 