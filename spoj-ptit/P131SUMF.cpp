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
 
char s[1010][1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  int lo = 1, hi = n - 1, ans = 0;
  while (lo <= hi) {
    int mi = (lo + hi) >> 1;
    std::set<std::string> st;
    int f = 1;
    for (int i = 1; i <= m && f; ++i) {
      std::string str;
      str.reserve(n - mi);
      for (int j = mi + 1; j <= n; ++j)
        str += s[j][i];
      if (st.count(str)) {
        f = 0;
      } else {
        st.insert(str);
      }
    }
    if (f) {
      ans = mi;
      lo = mi + 1;
    } else {
      hi = mi - 1;
    }
  }
  printf("%d", ans);
} 