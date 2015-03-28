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

const int N = 10010;
const int Q = 1000010;
const int P = 30;
const int MASK = (1 << P) - 1;

std::bitset<1 << P> mark[1 << (31 - P)];

struct ele {
  int s;
  short i, j;
  ele(int s = 0, short i = 0, short j = 0) : s(s), i(i), j(j) { }
  bool operator<(const ele& e) const {
    return s < e.s;
  }
} tmp[Q];

struct query {
  int x, id;
  bool operator<(const query& q) const {
    return x < q.x;
  }
} q[Q];

int a[N], ans_i[Q], ans_j[Q];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
  }
  int m;
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &q[i].x);
    q[i].id = i;
    mark[q[i].x >> P][q[i].x & MASK] = 1;
  }
  std::sort(q + 1, q + m + 1);
  int cnt = 0;
  for (int i = 1; i < n; ++i)
    for (int j = n; j > i; --j) {
      int s = a[i] + a[j];
      if (mark[s >> P][s & MASK]) {
        mark[s >> P][s & MASK] = 0;
        tmp[++cnt] = ele(s, i, j);
      }
    }  
  std::sort(tmp + 1, tmp + cnt + 1);
  fprintf(stderr, "cnt = %d\n", cnt);
  memset(ans_i + 1, -1, m * sizeof(int));
  memset(ans_j + 1, -1, m * sizeof(int));
  for (int i = 1, j = 1; i <= m; ++i) {
    while (j <= cnt && tmp[j].s < q[i].x) ++j;
    if (j <= cnt && tmp[j].s == q[i].x) {
      ans_i[q[i].id] = tmp[j].i;
      ans_j[q[i].id] = tmp[j].j;
    }
  }
  for (int i = 1; i <= m; ++i) {
    printf("%d %d\n", ans_i[i], ans_j[i]);
  }
}
