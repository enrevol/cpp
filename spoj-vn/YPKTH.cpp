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
 
struct ss {
  int val, idx;
} m[101010];
 
bool ff(const ss& lhs, const ss& rhs) {
  return lhs.val < rhs.val;
}
 
int a[101010], b[101010], seg[22][101010], cnt[22][101010];
 
void build(int d, int l, int r) {
  if (l == r) {
    seg[d][l] = b[l];
  } else {
    int m = (l + r) >> 1;
    build(d + 1, l, m);
    build(d + 1, m + 1, r);
    int i = l, il = l, ir = m + 1, k = 0;
    while (il <= m && ir <= r) {
      cnt[d][i] = k;
      if (seg[d + 1][il] < seg[d + 1][ir]) {
        seg[d][i++] = seg[d + 1][il++];
        ++k;
      } else {
        seg[d][i++] = seg[d + 1][ir++];
      }
    }
    while (il <= m) {
      cnt[d][i] = k++;
      seg[d][i++] = seg[d + 1][il++];
    }
    while (ir <= r) {
      cnt[d][i] = k;
      seg[d][i++] = seg[d + 1][ir++];
    }
  }
}
 
int n;
 
int query(int f, int t, int k) {
  int l = 1, r = n, d = 1;
  while (l < r) {
    int m = (l + r) >> 1;
    int nf = cnt[d][f];
    int nt = t == r ? (m - l + 1) : cnt[d][t + 1];
    int tot = nt - nf;
    if (tot >= k) {
      f = l + nf;
      t = l + nt - 1;
      r = m;
    } else {
      f = m + 1 + f - l - nf;
      t = m + 1 + t - l - nt;
      l = m + 1;
      k -= tot;
    }
    ++d;
  }
  return l;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    m[i].val = a[i];
    m[i].idx = i;
  }
  std::sort(m + 1, m + n + 1, ff);
  for (int i = 1; i <= n; ++i)
    m[i].val = i;
  for (int i = 1; i <= n; ++i)
    b[m[i].val] = m[i].idx;
  build(1, 1, n);
  int q;
  scanf("%d", &q);
  int l, r, k;
  while (q--) {
    scanf("%d %d %d", &l, &r, &k);
    printf("%d\n", a[b[query(l, r, k)]]);
  }
} 