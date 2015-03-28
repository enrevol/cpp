#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct ss {
  int a, b, i;
  long long h;
} a[202020], best, t;
 
bool ff(const ss& lhs, const ss& rhs) {
  return lhs.b > rhs.b;
}
 
struct cmp {
  bool operator() (const ss& lhs, const ss& rhs) {
    return lhs.a < rhs.a;
  }
};
 
std::priority_queue<ss, std::vector<ss>, cmp> que;
int pre[202020], ans[202020];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d %lld", &a[i].a, &a[i].b, &a[i].h);
    a[i].i = i;
  }
  std::sort(a + 1, a + n + 1, ff);
  //for (int i = 1; i <= n; ++i)
  //  printf("%d %d %lld i = %d\n", a[i].a, a[i].b, a[i].h, a[i].i);
  best.a = 1010101;
  for (int i = 1; i <= n; ++i) {
    while (que.size() && a[i].b <= que.top().a) {
      if (best.h < que.top().h) best = que.top();
      que.pop();
    }
    pre[i] = best.i;
    t.a = a[i].a;
    t.h = a[i].h + best.h;
    t.i = i;
    que.push(t);
  }
  while (que.size()) {
    if (best.h < que.top().h) best = que.top();
    que.pop();
  }
  int idx = best.i;
  int sz = 0;
  while (idx) {
    ans[++sz] = a[idx].i;
    idx = pre[idx];
  }
  printf("%lld\n", best.h);
  for (int i = sz; i >= 1; --i)
    printf("%d ", ans[i]);
} 