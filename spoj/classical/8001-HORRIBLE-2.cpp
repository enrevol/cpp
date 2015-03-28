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
 
long long tr[1 << 20], zz[1 << 20];
 
inline void push(int i, int l, int r) {
  if (zz[i]) {
    tr[i] += zz[i] * (r - l + 1);
    zz[i << 1] += zz[i];
    zz[i << 1 | 1] += zz[i];
    zz[i] = 0;
  }
}
 
void modify(int i, int l, int r, int f, int t, int v) {
  push(i, l, r);
  if (f <= l && r <= t) {
    zz[i] += v;
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    int bl = std::max(f, l);
    int br = std::min(t, r);
    tr[i] += std::max(br - bl + 1, 0) * 1ll * v;
    if (f <= m) modify(il, l, m, f, t, v);
    if (m < t) modify(ir, m + 1, r, f, t, v);
  }
}
 
long long query(int i, int l, int r, int f, int t) {
  push(i, l, r);
  if (f <= l && r <= t) {
    return tr[i];
  } else {
    int il = i << 1;
    int ir = i << 1 | 1;
    int m = (l + r) >> 1;
    long long res = 0;
    if (f <= m) res += query(il, l, m, f, t);
    if (t >= m + 1) res += query(ir, m + 1, r, f, t);
    return res;
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(tr, 0, sizeof(tr));
    memset(zz, 0, sizeof(zz));
    int n, q;
    scanf("%d %d", &n, &q);
    int k, f, t, v;
    while (q--) {
      scanf("%d %d %d", &k, &f, &t);
      if (k) {
        printf("%lld\n", query(1, 1, n, f, t));
      } else {
        scanf("%d", &v);
        modify(1, 1, n, f, t, v);
      }
    }
  }
} 