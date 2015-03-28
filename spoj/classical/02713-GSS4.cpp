#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
long long tr[1 << 20], a[101010];
 
void push_up(int i) {
  tr[i] = tr[i << 1] + tr[i << 1 | 1];
}
void build(int i, int l, int r) {
  if (l == r) {
    tr[i] = a[l];
  } else {
    int m = (l + r) >> 1;
    build(i << 1, l, m);
    build(i << 1 | 1, m + 1, r);
    push_up(i);
  }
}
 
void modify(int i, int l, int r, int f, int t) {
  if (r - l + 1 == tr[i]) return;
  if (l == r) {
    tr[i] = (long long)sqrt(tr[i]);
  } else {
    int m = (l + r) >> 1;
    if (f <= m) modify(i << 1, l, m, f, t);
    if (t >= m + 1) modify(i << 1 | 1, m + 1, r, f, t);
    push_up(i);
  }
}
 
long long query(int i, int l, int r, int f, int t) {
  if (f <= l && r <= t) return tr[i];
  int m = (l + r) >> 1;
  long long res = 0;
  if (f <= m) res += query(i << 1, l, m, f, t);
  if (t >= m + 1) res += query(i << 1 | 1, m + 1, r, f, t);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, n_case = 0;
  while (~scanf("%d", &n)) {
    printf("Case #%d:\n", ++n_case);
    for (int i = 1; i <= n; ++i)
      scanf("%lld", a + i);
    build(1, 1, n);
    int q, f, t, k;
    scanf("%d", &q);
    while(q--) {
      scanf("%d %d %d", &k, &f, &t);
      if (f > t) std::swap(f, t);
      if (k) printf("%lld\n", query(1, 1, n, f, t));
      else modify(1, 1, n, f, t);
    }
    printf("\n");
  }
} 