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
 
const int N = 4e5;
 
int a[N + 5];
int v[N + 5];
int p[N + 5];
int c[N + 5];
 
std::vector<int> pos[N + 5];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  int vn = 0;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    v[++vn] = a[i];
  }
  std::sort(v + 1, v + vn + 1);
  vn = std::unique(v + 1, v + vn + 1) - v - 1;
  for (int i = 1; i <= n; ++i) {
    a[i] = std::lower_bound(v + 1, v + vn + 1, a[i]) - v;
    pos[a[i]].push_back(i);
  }
  memset(p, -1, sizeof(p));
  long long ans = 0;
  int left = 0;
  for (int i = 1; i <= n; ++i) {
    int x = a[i];
    ++c[x];
    while (c[x] - p[x] > k) ++p[x];
    if (p[x] >= 0)
      left = std::max(left, pos[x][p[x]]);
    ans += left;
  }
  printf("%lld", ans);
}