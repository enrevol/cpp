#include <algorithm>
#include <bitset>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <vector>
 
struct ss {
  int max, pre, suf, all;
} seg[202020];
 
int a[50505];
 
void make(ss& m, const ss& l, const ss& r) {
  m.all = l.all + r.all;
  m.max = std::max(l.max, r.max);
  m.max = std::max(m.max, l.suf + r.pre);
  m.pre = std::max(l.pre, l.all + r.pre);
  m.suf = std::max(r.suf, r.all + l.suf);  
}
 
void build(const int& idx, const int& l, const int& r) {
  if (l == r) {
    seg[idx].max = seg[idx].pre = seg[idx].suf = seg[idx].all = a[l];
  } else {
    int idx_l = idx << 1;
    int idx_r = idx_l + 1;
    int m = (l + r) >> 1;
    build(idx_l, l, m);
    build(idx_r, m + 1, r);
    make(seg[idx], seg[idx_l], seg[idx_r]);
  }
}
 
ss query(const int& idx, const int& l, const int& r, const int& from, const int& to) {
  if (from <= l && r <= to) return seg[idx];
  int idx_l = idx << 1;
  int idx_r = idx_l + 1;
  int m = (l + r) >> 1;
  if (to <= m) return query(idx_l, l, m, from, to);
  if (from > m) return query(idx_r, m + 1, r, from, to);
  ss seg_l = query(idx_l, l, m, from, to);
  ss seg_r = query(idx_r, m + 1, r, from, to);
  ss res;
  make(res, seg_l, seg_r);
  return res;
}
 
int main() {
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  build(1, 1, n);
  int m;
  scanf("%d", &m);
  while (m--) {
    int x, y;
    scanf("%d %d", &x, &y);
    printf("%d\n", query(1, 1, n, x, y).max);
  }
} 