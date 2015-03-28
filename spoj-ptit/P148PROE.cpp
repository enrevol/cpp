#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
std::set<std::string> st;
 
std::string s, t, u;
int n;
 
std::string ff(const std::string& a, const std::string& b) {
  std::string res;
  for (int i = 0; i < n; ++i) {
    res += b[i];
    res += a[i];
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  while (std::cin >> n) {
    if (n) {
      st.clear();
      std::cin >> s >> t >> u;
      int ans = 0;
      bool f = false;
      while (!f) {
        ++ans;
        std::string m = ff(s, t);
        if (st.count(m)) {
          break;
        } else {
          st.insert(m);
        }
        if (m == u) {
          f = true;
        } else {
          s = m.substr(0, n);
          t = m.substr(n, n);                 
        }
      }
      if (f) {
        printf("%d\n", ans);
      } else {
        puts("-1");
      }
    }
  }
} 