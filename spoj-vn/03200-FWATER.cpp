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
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::set<p2> st;
int a[303], p[303][303];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);  
  int n, t;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    st.insert(m2(t, i));
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      scanf("%d", p[i] + j);
  int ans = 0;
  while (!st.empty()) {
    while (st.size() && a[st.begin()->second])
      st.erase(st.begin());
    if (st.size()) {
      p2 t = *st.begin();
      ans += t.first;
      a[t.second] = 1;
      st.erase(st.begin());
      for (int i = 1; i <= n; ++i)
        if (i != t.second)
          st.insert(m2(p[t.second][i], i));
    }
  }
  printf("%d", ans);
} 