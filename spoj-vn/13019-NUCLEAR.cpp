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
 
typedef std::pair<int, int> p2;
 
std::vector<int> tree[1010101];
p2 p[202020], d[202020];
int in_a[202020], in_b[202020], r_a, r_b;
 
double dist(const p2& lhs, const p2& rhs) {
  return ceil(sqrt(1ll * (lhs.first - rhs.first) * (lhs.first - rhs.first) + 1ll * (lhs.second - rhs.second) * (lhs.second - rhs.second)));
}
 
void build(const int& idx, const int& l, const int& r) {
  if (l == r) {
    tree[idx].push_back(d[l].second);
  } else {
    int idx_l = idx << 1;
    int idx_r = idx_l | 1;
    int m = (l + r) >> 1;
    build(idx_l, l, m);
    build(idx_r, m + 1, r);
    size_t it_l = 0, it_r = 0;
    size_t sz_l = tree[idx_l].size();
    size_t sz_r = tree[idx_r].size();
    tree[idx].reserve(sz_l + sz_r);
    while (it_l < sz_l && it_r < sz_r) {
      if (tree[idx_l][it_l] < tree[idx_r][it_r]) tree[idx].push_back(tree[idx_l][it_l++]);
      else                                       tree[idx].push_back(tree[idx_r][it_r++]);
    }
    while (it_l < sz_l) tree[idx].push_back(tree[idx_l][it_l++]);
    while (it_r < sz_r) tree[idx].push_back(tree[idx_r][it_r++]);
  }
}
 
int query(const int& idx, const int& l, const int& r) {
  if (d[r].first <= r_a) return std::upper_bound(tree[idx].begin(), tree[idx].end(), r_b) - tree[idx].begin();
  int idx_l = idx << 1;
  int idx_r = idx_l | 1;
  int m = (l + r) >> 1;
  int res = query(idx_l, l, m);
  if (d[m + 1].first <= r_a) res += query(idx_r, m + 1, r);
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &p[i].first, &p[i].second);
  p2 p_a, p_b;
  scanf("%d %d %d %d %d", &p_a.first, &p_a.second, &p_b.first, &p_b.second, &q);
  for (int i = 1; i <= n; ++i) {
    d[i].first = dist(p[i], p_a);
    d[i].second = dist(p[i], p_b);
    if (d[i].first <= 200000) ++in_a[d[i].first];
    if (d[i].second <= 200000) ++in_b[d[i].second];
  }
  std::sort(d + 1, d + n + 1);
  build(1, 1, n);
  for (int i = 1; i <= 200000; ++i) {
    in_a[i] += in_a[i - 1];
    in_b[i] += in_b[i - 1];
  }
  while (q--) {
    scanf("%d %d", &r_a, &r_b);
    int k;
    if (r_a < d[1].first) k = 0;
    else k = query(1, 1, n);
    printf("%d\n", in_a[r_a] + in_b[r_b] - k);
  }
} 