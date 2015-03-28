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
 
const int N = 200010;
 
struct node {
  node* left;
  node* right;
  int sz, key, pri;
} p[N];
 
node* stack[N];
node* sz;
node** stsz;
 
inline void update(node*& x) {
  if (x != p) x->sz = x->left->sz + x->right->sz + 1;
}
 
inline void rot_left(node*& x) {
  node* y = x->right;
  x->right = y->left;
  y->left = x;
  update(x);
  update(y);
  x = y;
}
 
inline void rot_right(node*& x) {
  node* y = x->left;
  x->left = y->right;
  y->right = x;
  update(x);
  update(y);
  x = y;
}
 
void insert(node*& x, int key) {
  if (x == p) {
    if (stsz == stack) {
      x = ++sz;
    } else {
      x = *stsz;
      --stsz;
    }
    x->left = x->right = p;
    x->pri = rand() * rand();
    x->key = key;
    x->sz = 1;
    return;
  }
  if (key == x->key) return;
  if (key < x->key) {
    insert(x->left, key);
    if (x->left->pri > x->pri) rot_right(x);
  } else {
    insert(x->right, key);
    if (x->right->pri > x->pri) rot_left(x);
  }
  update(x);
}
 
void remove(node*& x, int key) {
  if (x == p) return;
  if (key < x->key) {
    remove(x->left, key);
  } else if (key > x->key) {
    remove(x->right, key);
  } else {
    if (x->left != p && x->right != p) {
      if (x->left->pri > x->right->pri) {
        rot_right(x);
        remove(x->right, key);
      } else {
        rot_left(x);
        remove(x->left, key);
      }
    } else {
      ++stsz;
      *stsz = x;      
      if (x->left == p && x->right == p) {
        x = p;
      } else if (x->left == p) {
        x = x->right;
      } else {
        x = x->left;
      }
    }
  }
  update(x);
}  
 
inline int kth(node* x, int k) {
  while (x != p && k != x->left->sz + 1) {
    if (k < x->left->sz + 1) x = x->left;
    else k = k - x->left->sz - 1, x = x->right;
  }
  return x->key;
}
 
inline int count(node* x, int key) {
  int res = 0;
  while (x != p) {
    if (key >= x->key) {
      res += x->left->sz;
      if (key == x->key) break;
      ++res;
      x = x->right;
    } else {
      x = x->left;
    }
  }
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  node* root = p;
  sz = p;
  stsz = stack;
  int n;
  for (scanf("%d", &n); n--; ) {
    char s[3];
    int v;
    scanf("%s %d", s, &v);
    switch (*s) {
      case 'I': insert(root, v); break;
      case 'D': remove(root, v); break;
      case 'C': printf("%d\n", count(root, v)); break;
      case 'K': v > root->sz ? puts("invalid") : printf("%d\n", kth(root, v)); break;
    }
  }
}