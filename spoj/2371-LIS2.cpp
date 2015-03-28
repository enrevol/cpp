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
 
typedef std::pair<int, int> p2;
 
const int N = 100010;
const int inf = 1 << 30;
 
p2 p[N];
std::set<p2> st[N];
 
// increasing / decreasing
 
inline void add(int x, int v) {
  if (st[v].size() == 0) st[v].insert(p[x]);
  std::set<p2>::iterator it = st[v].lower_bound(p[x]);
  if (it != st[v].begin()) {
    std::set<p2>::iterator j = it;
    --j;
    if (j->first == p[x].first) return;
  }
  while (it != st[v].end() && it->second >= p[x].second)
    st[v].erase(it++);
  st[v].insert(p[x]);
}
 
inline bool check(int x, int v) {
  if (st[v].size() == 0) return 0;
  std::set<p2>::iterator it = st[v].lower_bound(p2(p[x].first, -inf));
  if (it == st[v].begin()) return 0;
  --it;
  return it->second < p[x].second;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &p[i].first, &p[i].second);
  int ans = 1;
  for (int i = 1; i <= n; ++i) {
    int val = 0;
    for (int lo = 1, hi = n - 1; lo <= hi; ) {
      int mi = (lo + hi) >> 1;
      if (check(i, mi)) {
        val = mi;
        lo = mi + 1;
      } else {
        hi = mi - 1;
      }
    }
    ++val;
    ans = std::max(ans, val);
    add(i, val);
  }
  printf("%d", ans);
}