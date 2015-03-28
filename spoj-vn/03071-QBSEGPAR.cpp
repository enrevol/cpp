#include <algorithm>
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
 
const int N = 15010;
const int MAX = 15000 * 30000;
 
typedef std::pair<int, int> p2;
 
int a[N], sum[N];
 
struct node {
  node* left;
  node* right;
  int pri;
  int key; // sum  
  p2 val, best;  
} p[N];
 
int sz;
p2 dummy;
 
void update(node*& x) {
  if (x == p) return;
  x->best.first = std::min(x->val.first, std::min(x->left->best.first, x->right->best.first));
  x->best.second = std::max(x->val.second, std::max(x->left->best.second, x->right->best.second));
}
 
void rot_left(node*& x) {
  node* y = x->right;
  x->right = y->left;
  y->left = x;
  update(x);
  update(y);
  x = y;
}
 
void rot_right(node*& x) {
  node* y = x->left;
  x->left = y->right;
  y->right = x;
  update(x);
  update(y);
  x = y;
}
 
void insert(node*& x, int key, const p2& val) {
  if (x == p) {
    x = &p[++sz];
    x->left = x->right = p;
    x->pri = rand();
    x->key = key;
    x->val = val;
  } else {
    if (key == x->key) {
      x->val.first = std::min(x->val.first, val.first);
      x->val.second = std::max(x->val.second, val.second);
    } else if (key < x->key) {
      insert(x->left, key, val);
      if (x->left->pri > x->pri) rot_right(x);
    } else {
      insert(x->right, key, val);
      if (x->right->pri > x->pri) rot_left(x);
    }
  }
  update(x);
}
 
p2 merge(const p2& x, const p2& y) {
  return p2(std::min(x.first, y.first), std::max(x.second, y.second));
}
 
p2 query(node* x, int key) {
  p2 res(dummy);
  while (x != p) {
    if (key > x->key) {
      x = x->right;
    } else {
      res = merge(res, x->val);
      if (x->right != p)
        res = merge(res, x->right->best);
      if (key == x->key) break;
      x = x->left;
    }
  }
  return res;
}
 
bool possible(int m, int n, int k) {
  sz = 0;
  node* root = p;
  insert(root, 0, p2(0, 0));
  for (int i = 1; i < n; ++i) {
    p2 val = query(root, sum[i] - m);
    if (val != dummy) ++val.first, ++val.second;
    insert(root, sum[i], val);
  }
  p2 res = query(root, sum[n] - m);
  return res.first + 1 <= k && k <= res.second + 1;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum[i] = sum[i - 1] + a[i];
  }
  dummy = p2(N, -N);
  p->best = p->val = dummy;
  int ans = 0;
  for (int f = -MAX, t = MAX; f <= t; ) {
    int m = (f + t) >> 1;
    if (possible(m, n, k)) {
      ans = m;
      t = m - 1;
    } else {
      f = m + 1;
    }
  }
  printf("%d", ans);
}