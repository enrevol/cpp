#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
struct node {
  int v, c;
} tr[1 << 22];
 
p2 b[303030];
int a[303030];
 
node merge(const node& lhs, const node& rhs) {
  node res;
  if (lhs.v == rhs.v) {
    res.v = lhs.v;
    res.c = lhs.c + rhs.c;
  } else {
    if (lhs.c > rhs.c) {
      res.v = lhs.v;
      res.c = lhs.c - rhs.c;
    } else {
      res.v = rhs.v;
      res.c = rhs.c - lhs.c;
    }
  }
  return res;
}
 
void build(int i, int l, int r) {
  if (l == r) {
    tr[i].v = a[l];
    tr[i].c = 1;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    build(il, l, m);
    build(ir, m + 1, r);
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
  int n, c;
  scanf("%d %d", &n, &c);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    b[i] = p2(a[i], i);
  }
  std::sort(b + 1, b + n + 1);
  build(1, 1, n);
  int m, f, t;
  scanf("%d", &m);
  while (m--) {
    scanf("%d %d", &f, &t);
    node k = query(1, 1, n, f, t);
    if (k.c) {
      int cnt = std::upper_bound(b + 1, b + n + 1, p2(k.v, t)) - std::lower_bound(b + 1, b + n + 1, p2(k.v, f));
      if ((cnt << 1) > t - f + 1) {
        printf("yes %d\n", k.v);
      } else {
        printf("no\n");
      }
    } else {
      printf("no\n");
    }
  }
} 