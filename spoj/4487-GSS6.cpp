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
 
const int inf = 1e9;
 
struct node {
  int left, right;
  int sz, pri;
  int key;
  int all, best;
  int pref, suff;
} p[202020];
 
inline node merge(const node& x, const node& y, int key) {
  node res;
  res.sz = x.sz + y.sz + 1;
  if (x.sz == 0 && y.sz == 0) {
    res.all = res.best = res.pref = res.suff = key;
  } else if (x.sz == 0) {
    res.all = y.all + key;
    res.pref = std::max(key, key + y.pref);
    res.suff = std::max(y.suff, res.all);
    res.best = y.best;
  } else if (y.sz == 0) {
    res.all = x.all + key;
    res.pref = std::max(x.pref, res.all);
    res.suff = std::max(key, key + x.suff);
    res.best = x.best;
  } else {    
    res.all = x.all + y.all + key;
    res.pref = std::max(x.pref, x.all + y.pref + key);
    res.pref = std::max(res.pref, x.all + key);    
    res.suff = std::max(y.suff, y.all + x.suff + key);
    res.suff = std::max(res.suff, y.all + key);
    res.best = std::max(x.best, y.best);
    res.best = std::max(res.best, x.suff + y.pref + key);
    res.best = std::max(res.best, x.suff);
    res.best = std::max(res.best, x.suff + key);
    res.best = std::max(res.best, y.pref);
    res.best = std::max(res.best, y.pref + key);
    res.best = std::max(res.best, key);
  }
  res.best = std::max(res.best, res.all);
  res.best = std::max(res.best, res.pref);
  res.best = std::max(res.best, res.suff);
  return res;
}
 
int root, sz, seed;
 
inline void update(int x) {
  node tmp = merge(p[p[x].left], p[p[x].right], p[x].key);
  p[x].sz = tmp.sz;
  p[x].all = tmp.all;
  p[x].pref = tmp.pref;
  p[x].suff = tmp.suff;
  p[x].best = tmp.best;
}
 
inline int gen() {
  seed = ((seed << 5) + seed) & ((1 << 22) - 1);
  return seed;
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
    x = ++sz;
    p[x].pri = rand();
    p[x].sz = 1;
    p[x].key = p[x].all = p[x].best = p[x].pref = p[x].suff = key;
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
 
void remove(int& x, int pos) {
  if (pos == p[p[x].left].sz + 1 || pos == -1) {
    if (p[x].left == 0 && p[x].right == 0) {
      x = 0;
      return;
    }
    if (p[x].left == 0) {
      x = p[x].right;
    } else if (p[x].right == 0) {
      x = p[x].left;
    } else {
      if (p[p[x].left].pri > p[p[x].right].pri) {
        rot_right(x);
        remove(p[x].right, -1);
      } else {
        rot_left(x);
        remove(p[x].left, -1);
      }
    }
  } else if (pos <= p[p[x].left].sz) remove(p[x].left, pos);
  else remove(p[x].right, pos - p[p[x].left].sz - 1);
  update(x);
}
 
void modify(int& x, int pos, int key) {
  if (pos <= p[p[x].left].sz) modify(p[x].left, pos, key);
  else if (pos == p[p[x].left].sz + 1) p[x].key = key;
  else modify(p[x].right, pos - p[p[x].left].sz - 1, key);
  update(x);
}
 
node query(int& x, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) {
    return p[x];
  } else {
    int pos = f + p[p[x].left].sz;
    if (qf == pos && qt == pos) return merge(p[0], p[0], p[x].key);
    if (qt < pos) return query(p[x].left, f, pos - 1, qf, qt);
    if (qf > pos) return query(p[x].right, pos + 1, t, qf, qt);
    if (qt == pos) return merge(query(p[x].left, f, pos - 1, qf, qt), p[0], p[x].key);
    if (qf == pos) return merge(p[0], query(p[x].right, pos + 1, t, qf, qt), p[x].key);
    return merge(query(p[x].left, f, pos - 1, qf, qt), query(p[x].right, pos + 1, t, qf, qt), p[x].key);
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  seed = rand();
  int n;
  scanf("%d", &n);
  for (int i = 1, v; i <= n; ++i) {
    scanf("%d", &v);
    insert(root, i, v);
  }
  int q;
  scanf("%d", &q);
  for (int x, y; q--; ) {
    char s[5];
    scanf("%s %d", s, &x);
    if (*s == 'D') {
      remove(root, x);
    } else {
      scanf("%d", &y);
      if (*s == 'I') insert(root, x, y);
      else if (*s == 'R') modify(root, x, y);
      else printf("%d\n", query(root, 1, p[root].sz, x, y).best);
    }
  }
}