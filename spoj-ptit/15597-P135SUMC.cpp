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
 
typedef std::pair<int, int> p2;
 
std::set<p2> st;
 
p2 ccw(const p2& a, const p2& b) {
  return std::make_pair(b.first + a.second - b.second, b.second + b.first - a.first);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  int x, y;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &x, &y);
    st.insert(std::make_pair(x, y));
  }
  int ans = 0;
  p2 k, l;
  for (__typeof(st.begin()) i = st.begin(); i != st.end(); ++i) {
    __typeof(i) j = i;
    ++j;
    for ( ; j != st.end(); ++j) {
      int area = (i->first - j->first) * (i->first - j->first) + (i->second - j->second) * (i->second - j->second);
      if (area > ans) {
        k = ccw(*i, *j);
        l = ccw(*j, k);
        if (st.count(k) && st.count(l)) ans = area;
        k = ccw(*j, *i);
        l = ccw(*i, k);
        if (st.count(k) && st.count(l)) ans = area;
      }
    }
  }
  printf("%d", ans);
}