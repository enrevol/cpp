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
  int a, b;
} tr[1 << 20];
 
int a[1 << 18];
 
bool ff(const int& lhs, const int& rhs) {
  return a[lhs] > a[rhs];
}
 
node merge(const node& lhs, const node& rhs) {
  node res;
  int arr[] = { lhs.a, lhs.b, rhs.a, rhs.b };
  std::sort(arr, arr + 4, ff);
  res.a = arr[0];
  res.b = arr[1];
  return res;
}
 
void modify(int i, int l, int r, int p, int v) {
  if (l == r) {
    tr[i].a = l;
    a[p] = v;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    if (p < m + 1) modify(il, l, m, p, v);
    if (p > m) modify(ir, m + 1, r, p ,v);
    tr[i] = merge(tr[il], tr[ir]);
  }
}
 
node query(int i, int l, int r, int f, int t) {
  if (f <= l && r <= t) {
    return tr[i];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    if (t < m + 1) return query(il, l, m, f, t);
    if (f > m) return query(ir, m + 1, r, f, t);
    return merge(query(il, l, m, f, t), query(ir, m + 1, r, f, t));
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, t;
  scanf("%d", &n);
  a[0] = -1;
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    modify(1, 1, n, i, t);
  }
  int q;
  scanf("%d", &q);
  char s[22];
  int x, y;
  while (q--) {
    scanf("%s %d %d", s, &x, &y);
    if (*s == 'U') {
      modify(1, 1, n, x, y);
    } else {
      node t = query(1, 1, n, x, y);
      printf("%d\n", a[t.a] + a[t.b]);
    }
  }
} 