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
const int inf = 1e9;
 
struct node {
  node* left;
  node* right;
  int key, best;
  int pri, sz;
} p[N];
 
node** sz;
node* stack[N];
 
void update(node*& x) {
  if (x == p) return;
  x->sz = x->left->sz + x->right->sz + 1;
  x->best = std::max(x->key, std::max(x->left->best, x->right->best));
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
 
void insert(node*& x, int pos, int key) {
  if (x == p) {
    x = *sz;
    --sz;
    x->left = x->right = p;
    x->sz = 1;
    x->key = x->best = key;
    x->pri = rand() * rand();
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
 
void remove(node*& x) {
  if (x->left != p && x->right != p) {
    if (x->left->pri > x->right->pri) {
      rot_right(x);
      remove(x->right);
    } else {
      rot_left(x);
      remove(x->left);
    }
  } else {
    ++sz;
    *sz = x;
    if (x->left == p && x->right == p) x = p;
    else if (x->left == p) x = x->right;
    else x = x->left;
  }
  update(x);
}
 
void remove(node*& x, int pos) {
  if (pos == x->left->sz + 1) remove(x);
  else if (pos <= x->left->sz) remove(x->left, pos);
  else remove(x->right, pos - x->left->sz - 1);
  update(x);
}
 
int query(node*& x, int f, int t, int qf, int qt) {
  if (x == p) return -inf;
  if (qf <= f && t <= qt) return x->best;
  int pos = f + x->left->sz;
  int res = -inf;
  if (qf <= pos && pos <= qt) res = x->key;
  if (qf < pos) res = std::max(res, query(x->left, f, pos - 1, qf, qt));
  if (qt > pos) res = std::max(res, query(x->right, pos + 1, t, qf, qt));
  return res;
}
 
int find(node* x, int pos) {
  if (pos == x->left->sz + 1) return x->key;
  if (pos <= x->left->sz) return find(x->left, pos);
  return find(x->right, pos - x->left->sz - 1);
}
 
void modify(node*& x, int pos, int key) {
  if (pos == x->left->sz + 1) x->key = key;
  else if (pos <= x->left->sz) modify(x->left, pos, key);
  else modify(x->right, pos - x->left->sz - 1, key);
  update(x);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  node* root = p;  
  p->best = p->key = -inf;
  sz = stack;
  for (int i = N - 1; i >= 1; --i) {
    ++sz;
    *sz = p + i;
  }
  int n;
  for (scanf("%d", &n); n--; ) {
    char s[3];
    int x, y;
    scanf("%s %d", s, &x);
    if (*s == 'D') {
      remove(root, x);
    } else {
      scanf("%d", &y);
      switch (*s) {
       case 'I':
        insert(root, y, x);
        break;
       case 'S':
        if (x != y) {
          int vx = find(root, x);
          int vy = find(root, y);
          modify(root, x, vy);
          modify(root, y, vx);
        }
        break;
       case 'Q':
        printf("%d\n", query(root, 1, root->sz, x, y));
        break;
      }
    }
  }
}