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
 
struct node {
  int left, right;
  int sz;
  int key, pri;
} p[101010];
 
int st[101010];
int ssz;
 
int root, sz;
 
inline void update(int x) {
  p[x].sz = p[p[x].left].sz + p[p[x].right].sz + 1;
}
 
inline void rot_left(int& x) {
  int y = p[x].right;
  p[x].right = p[y].left;
  p[y].left = x;
  update(x);
  update(y);
  x = y;
}
 
inline void rot_right(int& x) {
  int y = p[x].left;
  p[x].left = p[y].right;
  p[y].right = x;
  update(x);
  update(y);
  x = y;
}
 
void insert(int& x, int pos, int key) {
  if (x == 0) {
    x = st[ssz--];
    p[x].left = p[x].right = 0;
    p[x].sz = 1;
    p[x].pri = rand() * rand();
    p[x].key = key;
    return;
  }
  if (pos - 1 <= p[p[x].left].sz) {
    insert(p[x].left, pos, key);
    if (p[p[x].left].pri > p[x].pri) rot_right(x);    
  } else {
    insert(p[x].right, pos - p[p[x].left].sz - 1, key);
    if (p[p[x].right].pri > p[x].pri) rot_left(x);
  }
  update(x);
}
 
void remove(int& x) {
  if (p[x].left == 0 && p[x].right == 0) {
    st[++ssz] = x;
    x = 0;
    return;
  }
  if (p[x].left == 0) {
    st[++ssz] = x;
    x = p[x].right;
  } else if (p[x].right == 0) {
    st[++ssz] = x;
    x = p[x].left;
  } else {
    if (p[p[x].left].pri > p[p[x].right].pri) {
      rot_right(x);
      remove(p[x].right);
    } else {
      rot_left(x);
      remove(p[x].left);
    }
  }
  update(x);
}
 
void remove(int& x, int pos, int& res) {
  if (p[p[x].left].sz + 1 == pos) {
    res = p[x].key;
    remove(x);
    return;    
  } else if (pos <= p[p[x].left].sz) {
    remove(p[x].left, pos, res);
  } else {
    remove(p[x].right, pos - p[p[x].left].sz - 1, res);
  }
  update(x);
}
 
int arr[101010];
int lis[101010];
 
void inorder(int x, int& sz) {
  if (x == 0) return;
  inorder(p[x].left, sz);
  arr[++sz] = p[x].key;
  inorder(p[x].right, sz);
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  int n, q;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) st[++ssz] = i;
  for (int i = 1; i <= n; ++i) insert(root, i, i);
  scanf("%d", &q);
  for (int x, y; q--; ) {
    scanf("%d %d", &x, &y);
    int card = 0;
    remove(root, x, card);
    insert(root, y, card);
  }
  int sz = 0;
  inorder(root, sz);
  int best = 0;
  for (int i = 1; i <= n; ++i) {
    int pos = std::upper_bound(lis + 1, lis + best + 1, arr[i]) - lis - 1;
    if (lis[pos + 1] == 0 || lis[pos + 1] > arr[i])
      lis[pos + 1] = arr[i];
    if (pos + 1 > best) best = pos + 1;
  }
  printf("%d", n - best);
}