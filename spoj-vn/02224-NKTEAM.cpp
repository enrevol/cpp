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
 
const int inf = 1e9;
 
p2 p[101010];
p2 tmp[101010];
 
std::set<p2> st;
 
inline bool check(int x) {
  if (st.size() == 0) return 1;
  std::set<p2>::iterator it = st.lower_bound(p2(p[x].first, -inf));
  if (it == st.begin()) return 1;
  --it;
  return it->second > p[x].second;
}
 
inline void add(int x) {
  if (st.size() == 0) {
    st.insert(p[x]);
    return;
  }
  std::set<p2>::iterator it = st.lower_bound(p[x]);
  if (it != st.begin()) {
    std::set<p2>::iterator j = it;
    --j;
    if (j->first < p[x].first && j->second < p[x].second)
      return;
  }
  while (it != st.end() && it->second > p[x].second)
    st.erase(it++);
  st.insert(p[x]);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1, v; i <= n; ++i)
    scanf("%d", &v), tmp[v].first = i;
  for (int i = 1, v; i <= n; ++i)
    scanf("%d", &v), tmp[v].second = i;
  for (int i = 1, v; i <= n; ++i)
    scanf("%d", &v), p[i] = tmp[v];
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += check(i);
    add(i);
  }
  printf("%d", ans);
}