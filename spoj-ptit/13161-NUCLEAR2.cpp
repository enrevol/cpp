#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
p2 p[202020];
int in_a[13131], in_b[13131];
 
int dist(const p2& lhs, const p2& rhs) {
  return ceil(sqrt(1ll * (lhs.first - rhs.first) * (lhs.first - rhs.first) + 1ll * (lhs.second - rhs.second) * (lhs.second - rhs.second)));
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n_case = 0;
  while (1) {
    int n, q;
    scanf("%d", &n);
    if (n == 0) break;
    for (int i = 1; i <= n; ++i)
      scanf("%d %d", &p[i].first, &p[i].second);
    p2 p_a, p_b;
    scanf("%d %d %d %d %d", &p_a.first, &p_a.second, &p_b.first, &p_b.second, &q);
    memset(in_a, 0, sizeof(in_a));
    memset(in_b, 0, sizeof(in_b));
    int t;
    for (int i = 1; i <= n; ++i) {
      t = dist(p[i], p_a);
      if (t <= 13000) ++in_a[t];
      t = dist(p[i], p_b);
      if (t <= 13000) ++in_b[t];
    }
    for (int i = 1; i <= 13000; ++i) {
      in_a[i] += in_a[i - 1];
      in_b[i] += in_b[i - 1];
    }
    printf("Case %d:\n", ++n_case);
    int r_a, r_b;
    while (q--) {
      scanf("%d %d", &r_a, &r_b);
      int ans = n - in_a[r_a] - in_b[r_b];
      if (ans < 0) ans = 0;
      printf("%d\n", ans);
    }
  }
} 