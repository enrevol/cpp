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
 
const int MAXN = 40000;
const int MAXLGN = 16;
 
int n, q;
int tree[MAXN];
int cant;
std::map<int, int> pos;
 
struct node {
  int val, L, R, size;
} buff[2 * MAXN * MAXLGN];
 
int build(int f, int t) {
  if (f > t) return 0; 
  int idx = ++cant;
  int m = (f + t) >> 1;
  buff[idx] = (node){ m, build(f, m - 1), build(m + 1, t), 0 };
  return idx;
}
 
int update(int x, int val, int amount) { 
  if (x == 0) return 0;
  int idx = ++cant;
  int L = buff[x].L;
  int R = buff[x].R;
  if (val < buff[x].val) L = update(L, val, amount);
  if (val > buff[x].val) R = update(R, val, amount);
  buff[idx] = (node){ buff[x].val, L, R, buff[x].size + amount };
  return idx;
}
 
int query(int x, int val) {
  if (val < buff[x].val)
    return query(buff[x].L, val) + buff[x].size -  buff[buff[x].L].size; 
  if (val > buff[x].val)
    return query(buff[x].R, val);
  return buff[x].size - buff[buff[x].L].size;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d", &n);
  tree[0] = build(1, n);
  for (int i = 1; i <= n; i++ ) {
    int x, posx;
    scanf("%d", &x);
    posx = pos[x];
    if (posx != 0 ) {
      tree[i] = update(update(tree[i - 1], posx, -1), i, +1);
    } else {
      tree[i] = update(tree[i - 1], i, +1);
    }
    pos[x] = i;
  } 
  scanf("%d", &q);
  while (q--) {
    int f, t;
    scanf("%d %d", &f, &t);
    printf("%d\n", query(tree[t], f));
  }
}