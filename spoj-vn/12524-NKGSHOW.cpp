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
 
const int N = 100010;
 
struct node {
  node* left;
  node* right;
  int key, pri;
  int sz, lazy;
} p[N];
 
int sz;
 
void update(node* const& x) {
  if (x == p) return;
  x->sz = x->left->sz + x->right->sz + 1;
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
 
// insert key at pos
void insert(node*& x, int pos, int key) {
  if (x == p) {
    ++sz;
    x = p + sz;
    x->left = x->right = p;
    x->key = key;
    x->pri = rand() * rand();
    x->sz = 1;
    return;
  }
  if (pos - 1 <= x->left->sz) {    
    insert(x->left, pos, key);
    if (x->left->pri > x->pri) rot_right(x);
  } else {
    insert(x->right, pos - x->left->sz - 1, key);
    if (x->right->pri > x->pri) rot_left(x);
  }
  update(x);
}
 
void push(node*& x) {
  if (x == p) return;
  if (x->lazy) {
    std::swap(x->left->left, x->left->right);
    std::swap(x->right->left, x->right->right);
    x->left->lazy ^= 1;
    x->right->lazy ^= 1;
    x->lazy = 0;
  }
}
 
// split x into left and right at pos
// left  : 1..pos-1
// right : pos..N
void split(node* x, int pos, node*& left, node*& right) {
  if (x == p) {
    left = right = p;
    return;
  }
  push(x);
  if (x->left->sz + 1 < pos) {
    left = x;
    split(x->right, pos - x->left->sz - 1, left->right, right);
  } else {
    right = x;
    split(x->left, pos, left, right->left);
  }
  update(left);
  update(right);
}
 
// merge left and right into x
// all elements in left < all elements in right
void merge(node*& x, node* left, node* right) {
  push(left);
  push(right);
  if (left == p) {
    x = right;
  } else if (right == p) {
    x = left;
  } else {
    if (left->pri > right->pri) {
      x = left;
      merge(x->right, left->right, right);
    } else {
      x = right;
      merge(x->left, left, right->left);
    }
    update(x);
  }
}
 
int query(node* x, int pos) {
  while (pos != x->left->sz + 1) {
    push(x);
    if (pos <= x->left->sz) x = x->left;
    else pos -= x->left->sz + 1, x = x->right;
  }
  return x->key;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  node* root = p;
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    int v;
    scanf("%d", &v);
    insert(root, i, v);
  }
  for (int k, x, y; m--; ) {
    scanf("%d %d", &k, &x);
    if (k == 1) {
      scanf("%d", &y);
      node* a;
      node* b;
      split(root, x, a, b);
      node* c;
      node* d;
      split(b, y - x + 2, c, d);
      std::swap(c->left, c->right);
      c->lazy = 1;
      node* e;
      merge(e, a, c);
      merge(root, e, d);
    } else {
      printf("%d\n", query(root, x));
    }
  }
}