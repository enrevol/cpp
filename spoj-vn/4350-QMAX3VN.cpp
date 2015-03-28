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
 
const int mx = 1e5;
const int inf = 1e9;
 
struct node {
  int left;
  int right;
  int sz;
  int height;
  int best;
  int pri;
} p[mx + 10];
 
inline int max(int x, int y) {
  return x - ((x - y) & ((x - y) >> 31));
}
 
class treap {
  int root;
  int seed;
  int sz;
  
  inline void update(int x) {
    p[x].sz = p[p[x].left].sz + p[p[x].right].sz + 1;
    p[x].best = max(p[x].height, max(p[p[x].left].best, p[p[x].right].best));
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
  
  inline int gen() {
    seed += seed << 1;
    return seed;
  }
  
  void insert(int& x, int h, int k) {
    if (x == 0) {
      x = ++sz;
      p[x].pri = gen();
      p[x].height = p[x].best = h;
      p[x].sz = 1;
      return;
    }
    if (k - 1 <= p[p[x].left].sz) {
      int& y = p[x].left;
      insert(y, h, k);
      if (p[y].pri < p[x].pri) rot_right(x);
    } else {
      int& y = p[x].right;
      insert(y, h, k - p[p[x].left].sz - 1);
      if (p[y].pri < p[x].pri) rot_left(x);
    }
    update(x);
  }
  
  int query(int x, int f, int t, int qf, int qt) {
    if (x == 0) return -inf;
    if (qf <= f && t <= qt) return p[x].best;
    int res = -inf;
    int pos = f + p[p[x].left].sz;
    if (qf <= pos && pos <= qt) res = p[x].height;
    if (qf < pos) res = max(res, query(p[x].left, f, pos - 1, qf, qt));
    if (qt > pos) res = max(res, query(p[x].right, pos + 1, t, qf, qt));
    return res;
  }
      
 public:
  treap() {
    srand(time(NULL));
    seed = rand();
    root = sz = 0;
    p[0].height = p[0].best = -inf;
  }
  
  inline void insert(int h, int k) {
    insert(root, h, k);
  }
  
  inline int query(int f, int t) {
    return query(root, 1, p[root].sz, f, t);
  }
  
} tr;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  for (scanf("%d", &n); n--; ) {
    char s[2];
    int x, y;
    scanf("%s %d %d", s, &x, &y);
    if (*s == 'A') tr.insert(x, y);
    else printf("%d\n", tr.query(x, y));
  }
}