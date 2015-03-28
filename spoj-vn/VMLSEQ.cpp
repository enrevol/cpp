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
 
const int N = 200010;
 
struct query {
  int f, t, id;
  bool operator<(const query& q) const {
    return t < q.t;
  }
} q[N];

int a[N], id[N], pos[N], ans[N], tr[N << 2], s[N];
std::vector<int> e[N], ex;
std::map<int, int> map[N];
 
inline void push(int i, int f, int t) {
  if (tr[i] && f < t) {
    tr[i << 1] = std::max(tr[i << 1], tr[i]);
    tr[i << 1 | 1] = std::max(tr[i << 1 | 1], tr[i]);
    tr[i] = 0;
  }
}
 
void update(int i, int f, int t, int qf, int qt, int v) {  
  push(i, f, t);
  if (qf <= f && t <= qt) {
    tr[i] = std::max(tr[i], v);
  } else {
    int m = (f + t) >> 1;
    if (qf < m + 1) update(i << 1, f, m, qf, qt, v);
    if (qt > m) update(i << 1 | 1, m + 1, t, qf, qt, v);
  }  
}
 
inline int get(int f, int t, int p) {
  for (int i = 1; ; ) {
    push(i, f, t);
    if (f == t) return tr[i];
    int m = (f + t) >> 1;
    i <<= 1;
    if (p < m + 1) t = m;
    else ++i, f = m + 1;
  }  
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", a + i);
  int en = 1;
  id[n + 1] = 1;
  e[1].push_back(n + 1);
  for (int i = n; i >= 1; --i) {
    if (a[i] == -a[i + 1]) id[i] = id[i + 2];
    if (id[i] == 0) {
      std::map<int, int>::iterator it = map[id[i + 1]].find(-a[i]);
      if (it != map[id[i + 1]].end()) id[i] = id[it->second + 1];
    }
    if (id[i] == 0) id[i] = ++en;
    e[id[i]].push_back(i);
    map[id[i]][a[i]] = i;
  }
  const int sq = sqrt(1.0 * n) * 0.618;
  for (int i = 1; i <= en; ++i) {
    int sz = int(e[i].size());
    pos[i] = sz;
    if (sz > sq) ex.push_back(i);
  }
  fprintf(stderr, "en = %d\n", en);
  fprintf(stderr, "ex = %d\n", int(ex.size()));
  fprintf(stderr, "sq = %d\n", sq);
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &q[i].f, &q[i].t);
    q[i].id = i;
  }  
  std::sort(q + 1, q + m + 1);
  int t = 0;
  for (int i = 1; i <= m; ++i) {
    int qf = q[i].f;
    int qt = q[i].t;
    int vs = 0;
    while (t <= qt) {
      ++t;
      int k = id[t];
      --pos[k];
      s[++vs] = k;
    }
    std::sort(s + 1, s + vs + 1);
    for (int j = 1; j <= vs; ++j) {
      if (s[j] == s[j - 1]) continue;
      int k = s[j];
      int sz = int(e[k].size());
      if (sz <= sq) {
        int last = 1;
        for (int j = sz - 1; j > pos[k]; --j) {
          int v = e[k][j];
          update(1, 1, n, last, v, e[k][pos[k]] - v);
          last = v + 1;
        }
      }
    }
    int v = get(1, n, qf);
    for (int j = 0; j < int(ex.size()); ++j) {
      int k = ex[j];
      int sz = int(e[k].size());
      if (pos[k] < sz - 1 && e[k][pos[k] + 1] >= qf && e[k][pos[k]] - v >= qf) {
        int p = std::upper_bound(e[k].begin() + pos[k], e[k].end(), qf, std::greater<int>()) - e[k].begin() - 1;
        int z = e[k][pos[k]] - e[k][p];
        v = std::max(v, z);
      }
    }
    ans[q[i].id] = v;
  }
  for (int i = 1; i <= m; ++i) printf("%d\n", ans[i]);  
}
