#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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

const int N = 100010;
const int MOD = 1e9;

struct node {
  node* left;
  node* right;
  int max;
} arr[N * 20];

node* next = arr;
node* ver[N];

struct query {
  int k, a, b, c, d;
} q[N];

int a[N];

node* build(int f, int t) {
  node* res = ++next;
  if (f == t) {
    res->max = a[f];
  } else {
    int m = (f + t) >> 1;
    res->left = build(f, m);
    res->right = build(m + 1, t);
    res->max = std::max(res->left->max, res->right->max);
  }
  return res;
}

node* update(node* x, int f, int t, int p, int v) {  
  node* res = ++next;
  res->left = x->left;
  res->right = x->right;
  if (f == t) {
    res->max = v;
  } else {
    int m = (f + t) >> 1;
    if (p < m + 1) res->left = update(x->left, f, m, p, v);
    else res->right = update(x->right, m + 1, t, p, v);
    res->max = std::max(res->left->max, res->right->max);
  }
  return res;
}

int query(node* x, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) return x->max;
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(x->left, f, m, qf, qt);
  if (qf > m) return query(x->right, m + 1, t, qf, qt);
  return std::max(query(x->left, f, m, qf, qt), query(x->right, m + 1, t, qf, qt));    
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  int r, m;
  scanf("%d %d", &r, &m);
  for (int i = 1; i <= m; ++i)
    scanf("%d %d %d %d %d", &q[i].k, &q[i].a, &q[i].b, &q[i].c, &q[i].d);
  int ans = 0;
  int vn = 0;
  ver[vn] = build(1, n);
  for (int i = 1; i <= r; ++i)
    for (int j = 1; j <= m; ++j) {
      int k = q[j].k;
      int a = q[j].a;
      int b = q[j].b;
      int c = q[j].c;
      int d = q[j].d;
      if (k == 1) {
        int p = (1ll * ans * a + c) % n + 1;
        int v = (1ll * ans * b + d) % MOD + 1;
        ver[++vn] = update(ver[vn - 1], 1, n, p, v);
      } else if (k == 2) {
        int f = (1ll * ans * a + c) % n + 1;
        int t = (1ll * ans * b + d) % n + 1;
        if (f > t) std::swap(f, t);
        ans = query(ver[vn], 1, n, f, t);
        printf("%d\n", ans);
      } else {
        int x = (1ll * ans * a + c) % (vn + 1);
        ver[++vn] = ver[x];
      }
    }
}
