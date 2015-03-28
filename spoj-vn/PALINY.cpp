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

const int N = 50010;

char s[N], t[N << 1];
int f[N << 1], c[N << 1];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d %s", &n, s + 1);
  int _n = 0;
  for (int i = 1; i <= n; ++i) {
    t[++_n] = s[i];
    c[_n] = c[_n - 1];
    t[++_n] = '#';
    c[_n] = c[_n - 1] + 1;
  }
  t[_n] = 0;
  n = _n - 1;
  int p = 0;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    if (p + f[p] >= i) {
      int r = p - (i - p);
      f[i] = std::min(f[r], p + f[p] - i);
    }
    while (1 <= i - f[i] - 1 && i + f[i] + 1 <= n && t[i - f[i] - 1] == t[i + f[i] + 1]) {
      ++f[i];
    }
//    fprintf(stderr, "i = %d f = %d\n", i, f[i]);
    int v = (f[i] << 1) + 1 - c[i + f[i]] + c[i - f[i] - 1];
    if (v > ans) {
      ans = v;
    }
    if (p + f[p] < i + f[i]) {
      p = i;
    }
  }
  printf("%d", ans);
}