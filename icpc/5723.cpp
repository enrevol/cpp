#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
typedef std::map<long long, long long>::iterator m_p2;
 
std::map<long long, long long> m, t_m;
p2 a[22];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].first, &a[i].second);
  m[0] = 0;
  for (int i = 1; i <= n; ++i) {
    t_m = m;
    for (m_p2 it = t_m.begin(); it != t_m.end(); ++it) {
      long long key = it->first + a[i].first;
      long long val = it->second + a[i].second;
      if (!m.count(key)) m[key] = val;
      else m[key] = std::min(m[key], val);
    }
  }
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int v, t;
    scanf("%d %d", &v, &t);
    long long best = -1;
    m_p2 it = m.lower_bound(v / t);
    while (it != m.end()) {
      if (it->second < best || best == -1)
        best = it->second;
      ++it;
    }
    printf("Case %d: ", ++n_case);
    if (best == -1) puts("IMPOSSIBLE");
    else printf("%lld\n", best);
  }
}