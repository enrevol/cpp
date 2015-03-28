#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
int tr[202020], zz[202020];
 
void push(int i, int f, int t) {
  if (zz[i]) {
    tr[i] += zz[i];
    if (f < t) {
      zz[i << 1] += zz[i];
      zz[i << 1 | 1] += zz[i];
    }
    zz[i] = 0;
  }
}
 
void modify(int i, int f, int t, int qf, int qt, int v) {  
  if (qf <= f && t <= qt) {
    zz[i] += v;
    push(i, f, t);
  } else {
    push(i, f, t);
    int m = (f + t) >> 1;
    if (qf < m + 1) modify(i << 1, f, m, qf, qt, v);
    if (qt > m) modify(i << 1 | 1, m + 1, t, qf, qt, v);
    tr[i] = std::max(tr[i], tr[i << 1]);
    tr[i] = std::max(tr[i], tr[i << 1 | 1]);
  }
}
 
int query(int i, int f, int t, int qf, int qt) {
  push(i, f, t);
  if (qf <= f && t <= qt) {
    return tr[i];
  } else {
    int m = (f + t) >> 1;
    if (qt < m + 1) return query(i << 1, f, m, qf, qt);
    if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt);
    return std::max(query(i << 1, f, m, qf, qt), query(i << 1 | 1, m + 1, t, qf, qt));
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  int k, f, t, v;
  while (m--) {
    scanf("%d %d %d", &k, &f, &t);
    if (k == 0) {
      scanf("%d", &v);
      modify(1, 1, n, f, t, v);
    } else {
      printf("%d\n", query(1, 1, n, f, t));
    }
  }
} 