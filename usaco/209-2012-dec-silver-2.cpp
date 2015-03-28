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

int x[2020], y[2020];

int main() {
  freopen("wifi.in", "r", stdin);
  freopen("wifi.out", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, a, b;
  scanf("%d %d %d", &n, &a, &b);
  for (int i = 1; i <= n; ++i)
    scanf("%d", x + i);
  std::sort(x + 1, x + n + 1);
  for (int i = 1; i < n; ++i)
    y[i] = x[i + 1] - x[i];
  std::sort(y + 1, y + n, std::greater<int>());
  for (int i = 1; i < n; ++i)
    y[i] += y[i - 1];
  int ans = 1e9;
  int d = x[n] - x[1];
  for (int i = 1; i <= n; ++i) {
    int v = (i * a * 2) + (d - y[i - 1]) * b;
    if (v < ans) ans = v;
  }
  if (ans & 1) {
    printf("%d.5", ans >> 1);
  } else {
    printf("%d", ans >> 1);
  }
}
