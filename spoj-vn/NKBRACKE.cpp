#include <algorithm>
#include <bitset>
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

char s[N], ans[N << 1];

struct node {
  int open, close, all;  
} tr[N << 2];

int pos[N];

inline node merge(const node& x, const node& y) {
  node res;
  res.all = x.all + y.all;
  int v = std::min(x.open, y.close);
  res.all += v;
  res.open = x.open + y.open - v;
  res.close = x.close + y.close - v;
  return res;
}

void build(int i, int f, int t) {
  if (f == t) {
    tr[i].open = s[f] == '(';
    tr[i].close = s[f] == ')';
    pos[f] = i;
  } else {
    int m = (f + t) >> 1;
    build(i << 1, f, m);
    build(i << 1 | 1, m + 1, t);
    tr[i] = merge(tr[i << 1], tr[i << 1 | 1]);
  }
}

inline void update(int p, char c) {
  int i = pos[p];
  tr[i].open = c == '(';
  tr[i].close = c == ')';
  for (i >>= 1; i; i >>= 1) {
    tr[i] = merge(tr[i << 1], tr[i << 1 | 1]);
  }  
}

node query(int i, int f, int t, int qf, int qt) {
  if (qf <= f && t <= qt) return tr[i];
  int m = (f + t) >> 1;
  if (qt < m + 1) return query(i << 1, f, m, qf, qt);
  if (qf > m) return query(i << 1 | 1, m + 1, t, qf, qt);
  return merge(query(i << 1, f, m, qf, qt), query(i << 1 | 1, m + 1, t, qf, qt));
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  scanf("%s", s + 1);
  build(1, 1, n);  
  int sz = 0;
  while (m--) {
    int k;
    scanf("%d", &k);
    if (k == 0) {
      int p;
      char c;
      scanf("%d %c", &p, &c);
      update(p, c);
    } else {
      int f, t;
      scanf("%d %d", &f, &t);
      node r = query(1, 1, n, f, t);
      ans[++sz] = ((r.all << 1) == (t - f + 1)) + '0';
    }
  }
  puts(ans + 1);
}
