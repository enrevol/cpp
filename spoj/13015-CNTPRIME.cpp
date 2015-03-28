#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
 
std::bitset<1010101> is_prime;
int seg[50505], lazy[50505], a[10101];
 
void build(int idx, int l, int r) {
  lazy[idx] = 0;
  if (l == r) {
    seg[idx] = is_prime[a[l]];
  } else {
    int l_idx = idx << 1;
    int r_idx = l_idx + 1;
    int m = (l + r) >> 1;
    build(l_idx, l, m);
    build(r_idx, m + 1, r);
    seg[idx] = seg[l_idx] + seg[r_idx];
  }
}
 
void update(int idx, int l, int r, int from, int to, int val) {
  int l_idx = idx << 1;
  int r_idx = l_idx + 1;
  if (to < l || r < from) {
    if (lazy[idx]) {
      seg[idx] = is_prime[lazy[idx]] * (r - l + 1);
      if (l < r) lazy[l_idx] = lazy[r_idx] = lazy[idx];
      lazy[idx] = 0;
    }
    return;
  }
  if (from <= l && r <= to) {
    seg[idx] = is_prime[val] * (r - l + 1);
    if (l < r) lazy[l_idx] = lazy[r_idx] = val;
    lazy[idx] = 0;
  } else {
    if (lazy[idx]) {
      seg[idx] = is_prime[lazy[idx]] * (r - l + 1);
      lazy[l_idx] = lazy[r_idx] = lazy[idx];
      lazy[idx] = 0;
    }
    int m = (l + r) >> 1;
    update(l_idx, l, m, from, to, val);
    update(r_idx, m + 1, r, from, to, val);
    seg[idx] = seg[l_idx] + seg[r_idx];
  }
}
 
int query(int idx, int l, int r, int from, int to) {
  if (to < l || r < from) return 0;
  int l_idx = idx << 1;
  int r_idx = l_idx + 1;
  if (lazy[idx]) {
    seg[idx] = is_prime[lazy[idx]] * (r - l + 1);
    if (l < r) lazy[l_idx] = lazy[r_idx] = lazy[idx];
    lazy[idx] = 0;
  }
  if (from <= l && r <= to) {
    return seg[idx];
  } else {
    int m = (l + r) >> 1;
    return query(l_idx, l, m, from, to) + query(r_idx, m + 1, r, from, to);
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  for (int i = 2; i <= 1000000; ++i)
    is_prime[i] = 1;
  for (int i = 2; i <= 1000; ++i)
    if (is_prime[i])
      for (int j = i * i; j <= 1000000; j += i)
        is_prime[j] = 0;
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    printf("Case %d:\n", ++n_case);
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    build(1, 1, n);
    int t, l, r, val;
    while (q--) {
      scanf("%d %d %d", &t, &l, &r);
      if (t) {
        printf("%d\n", query(1, 1, n, l, r));
      } else {
        scanf("%d", &val);
        update(1, 1, n, l, r, val);
      }
    }
  }
} 