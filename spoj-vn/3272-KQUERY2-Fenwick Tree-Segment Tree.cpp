#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int a[30303];
std::vector<int> tr[70707];
std::vector<int> fw[70707];
std::vector<int> left[70707], right[70707];
 
int t[202020];
int x[202020];
int y[202020];
int z[202020];
 
inline void update(int k, int i, int v) {
  for (++i; i; i -= i & -i)
    fw[k][i - 1] += v;
}
 
inline int query(int k, int i) {
  int sz = int(fw[k].size());
  int res = 0;
  for (++i; i <= sz; i += i & -i)
    res += fw[k][i - 1];
  return res;
}
 
void add(int i, int f, int t, int p, int v) {
  if (f == t) {
    tr[i].push_back(v);
  } else {
    int m = (f + t) >> 1;
    if (p < m + 1) add(i << 1, f, m, p, v);
    else add(i << 1 | 1, m + 1, t, p, v);    
  }
}
 
void build(int i, int f, int t) {
  if (f == t) {
    std::sort(tr[i].begin(), tr[i].end());
    tr[i].resize(std::unique(tr[i].begin(), tr[i].end()) - tr[i].begin());
    fw[i].resize(tr[i].size());
  } else {
    int m = (f + t) >> 1;
    int l = i << 1;
    int r = i << 1 | 1;
    build(l, f, m);
    build(r, m + 1, t);
    int szl = tr[l].size();
    int szr = tr[r].size();
    if (i > 1) {
      tr[i].resize(szl + szr);
      std::merge(tr[l].begin(), tr[l].end(), tr[r].begin(), tr[r].end(), tr[i].begin());
      tr[i].resize(std::unique(tr[i].begin(), tr[i].end()) - tr[i].begin());
    } else {
      tr[i].reserve(10000);
      for (int j = 1; j <= 10000; ++j)
        tr[i].push_back(j);
    }
    int sz = int(tr[i].size());
    left[i].reserve(sz);
    right[i].reserve(sz);
    for (int j = 0, x = 0, y = 0; j < sz; ++j) {
      while (x < szl && tr[l][x] < tr[i][j]) ++x;
      while (y < szr && tr[r][y] < tr[i][j]) ++y;
      left[i].push_back(x);
      right[i].push_back(y);
    }
    fw[i].resize(sz);
  }
}
 
void update(int i, int f, int t, int p, int v, int k, int c) {
  if (c >= fw[i].size()) return;
  if (f < t) {
    int m = (f + t) >> 1;
    if (p < m + 1) update(i << 1, f, m, p, v, k, left[i][c]);
    else update(i << 1 | 1, m + 1, t, p, v, k, right[i][c]);
  }
  update(i, c, k);
}
 
int query(int i, int f, int t, int qf, int qt, int k, int c) {
  if (c >= tr[i].size()) return 0;
  if (qf <= f && t <= qt) {
    return query(i, c);
  } else {
    int m = (f + t) >> 1;
    if (qt < m + 1) return query(i << 1, f, m, qf, qt, k, left[i][c]);
    if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt, k, right[i][c]);
    return query(i << 1, f, m, qf, qt, k, left[i][c]) + query(i << 1 | 1, m + 1, t, qf, qt, k, right[i][c]);
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    add(1, 1, n, i, a[i]);
  }
  int q;
  scanf("%d", &q);
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d %d", t + i, x + i, y + i);
    if (t[i] == 1) scanf("%d", z + i);
    else add(1, 1, n, x[i], y[i]);
  }
  build(1, 1, n);
  for (int i = 1; i <= n; ++i)
    update(1, 1, n, i, a[i], 1, a[i] - 1);
  for (int i = 1; i <= q; ++i) {
    if (t[i] == 1) {
      int ans = query(1, 1, n, x[i], y[i], z[i], z[i]);
      printf("%d\n", ans);
    } else {
      update(1, 1, n, x[i], a[x[i]], -1, a[x[i]] - 1);
      update(1, 1, n, x[i], y[i], 1, y[i] - 1);
      a[x[i]] = y[i];
    }
  }
}