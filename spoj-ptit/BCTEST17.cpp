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
 
int a[505050], st[505050], l[505050], r[505050], s[505050];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  int sz = 0;
  st[0] = 1;
  for (int i = 1; i <= n; ++i) {
    while (sz && a[st[sz]] <= a[i]) --sz;
    l[i] = st[sz];
    st[++sz] = i;
  }
  sz = 0;
  st[0] = n;
  for (int i = n; i >= 1; --i) {
    while (sz && a[st[sz]] <= a[i]) --sz;
    r[i] = st[sz];
    st[++sz] = i;
  }
  long long ans = 0;
  for (int i = 1; i <= n; ++i) {
    ans += i - l[i] - (s[i - 1] - s[l[i]]);
    s[i] += s[i - 1];
    ++s[r[i]];
  }
  printf("%lld\n", ans);
} 