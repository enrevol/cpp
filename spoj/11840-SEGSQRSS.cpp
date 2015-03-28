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
 
const int mx = 1e5;
 
struct node {
  long long sum;
  long long sq;
} tr[(mx << 2) + 10];
 
long long query(int i, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) {
    return tr[i].sq;
  } else {
    int m = (f + t) >> 1;
    int x = i << 1;
    int y = x | 1;
    if (qt < m + 1) return query(x, f, m, qf, qt);
    if (qf > m) return query(y, m + 1, t, qf, qt);
    return query(x, f, m, qf, qt) + query(y, m + 1, t, qf, qt);
  }
}
 
void set(int i, int f, int t, int qf, int qt, int v) {
  if (qf <= f && t <= qt) {
    tr[i].sum = 1ll * v * (t - f + 1);
    tr[i].sq = 1ll * v * v * (t - f + 1);
  } else {
    int m = (f + t) >> 1;
    int x = i << 1;
    int y = x | 1;
    if (qf < m + 1) set(x, f, m, qf, qt, v);
    if (qt > m) set(y, m + 1, t, qf, qt, v);
    tr[i].sq = tr[x].sq + tr[y].sq;
  }
}
 
void add(int i, int f, int t, int qf, int qt, int v) {
  if (qf <= f && t <= qt) {    
    tr[i].sq += 1ll * v * v + 2ll * tr[i].sum * v;
    tr[i].sum += 1ll * v * v * (t - f + 1);
  } else {
    int m = (f + t) >> 1;
    int x = i << 1;
    int y = x | 1;
    if (qf < m + 1) add(x, f, m, qf, qt, v);
    if (qt > m) add(y, m + 1, t, qf, qt, v);
    tr[i].sq = tr[x].sq + tr[y].sq;
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  for (int tn = 1; tn <= tt; ++tn) {
    int n, q;
    scanf("%d %d", &n, &q);
    for (int i = 1, v; i <= n; ++i) {
      scanf("%d", &v);
      set(1, 1, n, i, i, v);
    }
    printf("Case %d:\n", tn);
    while (q--) {
      int k, f, t, v;
      scanf("%d %d %d", &k, &f, &t);
      if (k == 2) {
        printf("%lld\n", query(1, 1, n, f, t));
      } else {
        scanf("%d", &v);
        if (k == 0) {
          set(1, 1, n, f, t, v);
        } else {
          add(1, 1, n, f, t, v);
        }
      }
    }
  }
}