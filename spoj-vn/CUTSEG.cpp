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

const int N = 201;
const int MAX = 10;

bool b[N][N];
char s[N];
int a[N], head[N], next[N];
int** dp[N];
int cnt[N][MAX];

void solve(int f, int t) {
  if (f > t || b[f][t]) return;
  b[f][t] = 1;
  if (head[f] == head[t]) {
    memset(dp[f][t - f], 0, (t - f + 2) << 2);
    return;
  }
  for (int i = f; i < t; ++i) {
    i = next[i] - 1;
    solve(f, i);
    solve(i + 1, t);
    int xj = cnt[i][a[f]] - cnt[f - 1][a[f]];
    int xk = cnt[t][a[i + 1]] - cnt[i][a[i + 1]];
    if (a[f] == a[i + 1]) {
      for (int j = 1; j <= xj; ++j) {
        for (int k = 1; k <= xk; ++k) {
          int val = dp[f][i - f][j] + dp[i + 1][t - i - 1][k];
          int& ref = dp[f][t - f][j + k];
          if (ref == -1 || ref < val) ref = val;
        }
      }
    } else {
      int best = 0;
      for (int k = 1; k <= xk; ++k) {
        int val = dp[i + 1][t - i - 1][k] + k * k;
        if (val > best) best = val;
      }
      for (int j = 1; j <= xj; ++j) {
        int val = dp[f][i - f][j] + best;
        int& ref = dp[f][t - f][j];
        if (ref == -1 || ref < val) ref = val;
      }
    }
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  scanf("%s", s + 1);
  for (int i = 1; i <= n; ++i) {
    a[i] = s[i] - '0';
    for (int j = 0; j <= 9; ++j) cnt[i][j] = cnt[i - 1][j];
    ++cnt[i][a[i]];
  }
  for (int i = 1; i <= n; ++i) {
    dp[i] = new int*[n - i + 1];
    for (int j = i; j <= n; ++j) {
      int v = cnt[j][a[i]] - cnt[i - 1][a[i]];
      dp[i][j - i] = new int[v + 1];
      memset(dp[i][j - i], -1, (v + 1) << 2);
    }
  }
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j + 1 <= n && a[i] == a[j + 1]) ++j;
    for (int k = i; k <= j; ++k) head[k] = i;
    i = next[i] = j + 1;
  }
  solve(1, n);
  int ans = 0;
  int k = cnt[n][a[1]];
  for (int i = 1; i <= k; ++i) {
    int v = dp[1][n - 1][i] + i * i;
    if (ans < v) ans = v;
  }
  printf("%d\n", ans);
}
