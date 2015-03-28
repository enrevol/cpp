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
 
struct intervals {
  int end, cnt;
} a[N << 1];
 
struct node {
  node* left;
  node* right;
  int pri;  // priority
  int f, t; // range [f..t]
  int sz;   // subtree size
} p[N << 1];
 
node* stack[N << 1];
node* next;
node** stnext;
 
inline void update(node*& x) {
  if (x == p) return;
  x->sz = x->left->sz + x->right->sz + x->t - x->f + 1;
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
 
// [1.....pos-1][pos....n]
// =>
// [1.....pos-1][f..t][pos+t-f+1......n+t-f+1]
void insert(node*& x, int pos, int f, int t) {
  if (x == p) {
    if (stnext == stack) {
      x = ++next;
    } else {
      x = *stnext;
      --stnext;
    }
    x->left = x->right = p;
    x->f = f;
    x->t = t;
    x->sz = t - f + 1;
    x->pri = rand();
    return;
  }
  if (pos - 1 <= x->left->sz) {
    insert(x->left, pos, f, t);
    if (x->left->pri > x->pri) rot_right(x);
  } else {
    //assert(pos - 1 >= x->left->sz + x->cnt);
    insert(x->right, pos - x->left->sz - (x->t - x->f + 1), f, t);
    if (x->right->pri > x->pri) rot_left(x);
  }
  update(x);
}
 
void remove(node*& x) {
  if (x->left != p && x->right != p) {
    if (x->left > x->right) {
      rot_right(x);
      remove(x->right);
    } else {
      rot_left(x);
      remove(x->left);
    }
  } else {
    ++stnext;
    *stnext = x;
    if (x->left == p && x->right == p) {
      x = p;
    } else if (x->left == p) {
      x = x->right;
    } else if (x->right == p) {
      x = x->left;
    }
  }
  update(x);
}
 
// [1....][f.......t][.....n]
//         f<=pos<=t
// =>
// [1...][....n]
void remove(node*& x, int pos) {
  if (pos <= x->left->sz) {
    remove(x->left, pos);
  } else if (pos > x->left->sz + x->t - x->f + 1) {
    remove(x->right, pos - x->left->sz - (x->t - x->f + 1));
  } else {
    remove(x);
  }
  update(x);
}  
 
inline node* find(node* x, int& pos) {
  while (1) {
    if (pos <= x->left->sz) {
      x = x->left;
    } else if (pos > x->left->sz + x->t - x->f + 1) {
      pos = pos - x->left->sz - (x->t - x->f + 1);
      x = x->right;
    } else {
      break;
    }
  }
  pos = pos - x->left->sz;
  return x;
}
 
void inorder(node* x, int& sz) {
  if (x->left != p) inorder(x->left, sz);
  if (sz > 1 && a[sz - 1].end + 1 == x->f) {
    a[sz - 1].end = x->t;
    a[sz - 1].cnt += x->t - x->f + 1;
  } else {
    ++sz;
    a[sz].end = x->t;
    a[sz].cnt = x->t - x->f + 1;
  }
  if (x->right != p) inorder(x->right, sz);
}
   
// [1.....n]
// =>
// [1....pos-1][pos....n]
void split(node* x, int pos, node*& left, node*& right) {
  if (x == p) {
    left = right = p;
  } else {    
    if (pos <= x->left->sz) {
      right = x;
      split(x->left, pos, left, right->left);
    } else if (x->left->sz + x->t - x->f + 1 < pos) {
      left = x;
      split(x->right, pos - x->left->sz - (x->t - x->f + 1), left->right, right);
    } else {
      assert(pos == x->left->sz + 1);
      right = x;
      left = x->left;
      x->left = p;
    }
    update(left);
    update(right);
  }
}
 
// x = left + right
void merge(node*& x, node* left, node* right) {
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
 
typedef std::map<int, int>::iterator ite;
 
std::map<int, int> lis;
std::map<int, int> pos;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  node* root = p;
  next = p;
  stnext = stack;
  int n, m;
  scanf("%d %d", &n, &m);
  insert(root, 1, 1, n << 1);
  for (int k; m--; ) {
    scanf("%d", &k);
    int v = std::abs(k);
    if (v == n) continue;
    int lb = n - v + 1;
    int rb = n + v;
    {
      int tmp = lb;
      node* x = find(root, tmp); // contains lb
      if (tmp > 1) { // [1...tmp-1][tmp...t-f+1]
        int f = x->f;
        int t = x->t;
        remove(root, lb);
        insert(root, lb - tmp + 1, f + tmp - 1, t);
        insert(root, lb - tmp + 1, f, f + tmp - 2);
      }
    }
    {
      int tmp = rb;
      node* x = find(root, tmp); // contains rb
      if (tmp < x->t - x->f + 1) { // [1..tmp][tmp+1...t-f+1]
        int f = x->f;
        int t = x->t;
        remove(root, rb);
        insert(root, rb - tmp + 1, f + tmp, t);
        insert(root, rb - tmp + 1, f, f + tmp - 1);
      }
    }
    // root ->     a    +  b
    // root -> [1..lb-1][lb..n]
    node* a;
    node* b;
    split(root, lb, a, b);
    // b ->      c      +     d
    // b -> [1..rb-lb+1][rb-lb+2...n]
    node* c;
    node* d;
    split(b, rb - lb + 2, c, d);
    node* e;
    merge(e, a, d);
    if (k > 0) {
      merge(root, c, e);
    } else {
      merge(root, e, c);
    }
  }
  int sz = 0;
  inorder(root, sz);
  //fprintf(stderr, "sz = %d\n", sz);
  //fprintf(stderr, "next = %d\n", next - p);
  //fprintf(stderr, "stnext = %d\n", stnext - stack);
  lis[0] = 0;
  pos[0] = 0;
  for (int i = 1; i <= sz; ++i) {
    int v = a[i].end;
    ite it = --pos.upper_bound(v);
    int x = it->second;
    int nx = x + a[i].cnt;
    it = lis.upper_bound(nx);
    if (it == lis.end() || it->second > v) {
      --it;
      while (it != lis.begin() && it->second > v) {
        pos.erase(it->second);
        lis.erase(it--);
      }
      lis[nx] = v;
      pos[v] = nx;
    }
  }
  ite it = --lis.end();  
  printf("%d", (n << 1) - it->first);
}