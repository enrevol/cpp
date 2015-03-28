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
 
const int N = 30010;
 
struct node {
  node* left;
  node* right;
  unsigned short key, cnt, sz, pri;
} p[N << 4];
 
node* stack[N << 4];
node* sz;
node** stsz;
 
class treap {
  node* root;
  
  inline void update(node* const& x) {
    x->sz = x->left->sz + x->right->sz + x->cnt;
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
      x = stsz != stack ? *(stsz--) : ++sz;
      x->left = x->right = p;
      x->sz = 1;
      x->key = key;
      x->cnt = 1;
      x->pri = rand();
      return;
    }
    if (key < x->key) {
      insert(x->left, key);
      if (x->left->pri > x->pri) rot_right(x);
    } else if (key > x->key) {
      insert(x->right, key);
      if (x->right->pri > x->pri) rot_left(x);
    } else {
      ++x->cnt;
    }
    update(x);
  }
  
  void remove(node*& x, int key) {
    if (key < x->key) {
      remove(x->left, key);
    } else if (key > x->key) {
      remove(x->right, key);
    } else {
      if (x->cnt > 1) {
        --x->cnt;
      } else {
        if (x->left == p && x->right == p) {
          ++stsz;
          *stsz = x;
          x = p;
        } else if (x->left == p) {
          ++stsz;
          *stsz = x;
          x = x->right;
        } else if (x->right == p) {
          ++stsz;
          *stsz = x;
          x = x->left;
        } else {
          if (x->left->pri > x->right->pri) {
            rot_right(x);
            remove(x->right, key);
          } else {
            rot_left(x);
            remove(x->left, key);
          }
        }
      }
    }
    update(x);
  }
  
  // less than or equal to key
  inline int count(node* x, int key) {
    int res = 0;
    while (x != p) {
      if (x->key <= key) {
        res += x->left->sz + x->cnt;
        x = x->right;
      } else {
        x = x->left;
      }
    }
    return res;
  }
 public:
  treap() {
    root = p;
  }
  
  inline void insert(int key) {
    insert(root, key);
  }
  
  inline void remove(int key) {
    remove(root, key);
  }
  
  inline void modify(int fkey, int tkey) {
    remove(root, fkey);
    insert(root, tkey);
  }
  
  inline int count(int key) {
    return root->sz - count(root, key);
  }
} tr[N << 2];
 
int n;
int a[N];
 
inline int query(int pos, int key) {
  int res = 0;
  for ( ; pos; pos -= pos & -pos)
    res += tr[pos].count(key);
  return res;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  srand(time(NULL));
  p->left = p->right = p;
  p->cnt = p->sz = 0;
  stsz = stack;
  sz = p;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    for (int j = i; j <= n; j += j & -j)
      tr[j].insert(a[i]);
  }
  int q;
  scanf("%d", &q);
  for (int k, x, y, z; q--; ) {
    scanf("%d %d %d", &k, &x, &y);
    if (k == 1) {
      scanf("%d", &z);
      printf("%d\n", query(y, z) - query(x - 1, z));
    } else {
      for (int i = x; i <= n; i += i & -i)
        tr[i].modify(a[x], y);
      a[x] = y;
    }
  }
}