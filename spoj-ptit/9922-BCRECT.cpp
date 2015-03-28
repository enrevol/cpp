#include <algorithm>
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
 
int n, m, h[1010101], pos_min[1010101], pos_max[1010101], st[1010101];
long long ans;
 
void solve() {
  int d = 0;
  st[++d] = 0;
  for (int i = 1; i <= m; ++i) {
    while (d && h[st[d]] >= h[i]) --d;
    if (h[i]) pos_min[i] = st[d] + 1;
    st[++d] = i;
  }
  d = 0;
  st[++d] = m + 1;
  for (int i = m; i >= 1; --i) {
    while (d && h[st[d]] >= h[i]) --d;
    if (h[i]) pos_max[i] = st[d] - 1;
    st[++d] = i;
  }
  for (int i = 1; i <= m; ++i)
    if (h[i]) {
      long long val = 1ll * h[i] * (pos_max[i] - pos_min[i] + 1);
      if (val > ans) ans = val;
    }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i)
    scanf("%d", h + i);
  solve();
  for (int i = 1; i <= m; ++i)
    h[i] = n - h[i];
  solve();
  printf("%lld", ans);
} 