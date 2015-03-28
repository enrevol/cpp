#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
struct ss {
  char s[55];
  int sz;
} a[22];
 
bool operator < (const ss& lhs, const ss& rhs) {
  if (lhs.sz == rhs.sz) {
    for (int i = lhs.sz; i >= 1; --i)
      if (lhs.s[i] < rhs.s[i]) return true;
    return false;
  }
  return lhs.sz < rhs.sz;
}
 
bool operator == (const ss& lhs, const ss& rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, nc = 0;
  while (1) {
    scanf("%d", &n);
    if (n == 0) break;
    for (int i = 1; i <= n; ++i) {
      scanf("%s", a[i].s + 1);
      a[i].sz = strlen(a[i].s + 1);
      std::reverse(a[i].s + 1, a[i].s + a[i].sz + 1);
      while (a[i].sz > 1) {
        if (a[i].s[a[i].sz] == '0') --a[i].sz;
        else break;
      }
      a[i].s[a[i].sz + 1] = 0;
    }
    std::sort(a + 1, a + n + 1);
    char buffer[55];
    printf("Case %d:", ++nc);
    if (a[1] == a[n]) {
      printf(" There is a row of trees having equal height.\n");
    } else {
      std::reverse(a[1].s + 1, a[1].s + a[1].sz + 1);
      std::reverse(a[n].s + 1, a[n].s + a[n].sz + 1);
      printf(" %s %s\n", a[1].s + 1, a[n].s + 1);
    }
  }
} 