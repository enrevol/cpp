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
 
struct node {
  int o, c, t;
} tr[1 << 18];
 
char s[1 << 16];
 
void modify(int i, int l, int r, int p, char b) {
  if (l == r) {
    tr[i].o = b == '(';
    tr[i].c = b == ')';
    s[l] = b;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    if (p <= m) modify(il, l, m, p, b);
    else modify(ir, m + 1, r, p, b);
    int t = std::min(tr[il].o, tr[ir].c);
    tr[i].t = tr[il].t + tr[ir].t + (t << 1);
    tr[i].o = tr[il].o - t + tr[ir].o;
    tr[i].c = tr[ir].c - t + tr[il].c;
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt = 0;
  while (tt < 10) {
    memset(tr, 0, sizeof(tr));
    printf("Test %d:\n", ++tt);
    int n;
    scanf("%d %s", &n, s + 1);
    for (int i = 1; i <= n; ++i)
      modify(1, 1, n, i, s[i]);
    int m, k;
    scanf("%d", &m);
    while (m--) {
      scanf("%d", &k);
      if (k) modify(1, 1, n, k, s[k] == '(' ? ')' : '(');
      else puts(tr[1].t == n ? "YES" : "NO");
    }
  }
} 