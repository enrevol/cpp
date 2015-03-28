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
 
std::vector<int> ed[10101];
int sz;
int s[10101];
int c[10101];
 
void dfs(int u, bool& f) {
  if (c[u] == 1) f = 1;
  if (f == 1) return;
  if (c[u] > 0) return;
  c[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i)
    dfs(ed[u][i], f);
  c[u] = 2;
  s[++sz] = u;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  for (scanf("%d", &tt); tt--; ) {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      ed[i].clear();
    for (int i = 1, u, v; i <= m; ++i) {
      scanf("%d %d", &u, &v);
      ed[u].push_back(v);
    }
    memset(c, 0, sizeof(c));    
    sz = 0;
    bool f = 0;
    for (int i = 1; i <= n && !f; ++i)
      dfs(i, f);
    if (f) {
      puts("recheck hints");
    } else {
      for (int i = 1; i <= n; ++i)
        std::sort(ed[i].begin(), ed[i].end());
      for (int i = sz; i > 1 && !f; --i) {
        f = !std::binary_search(ed[s[i]].begin(), ed[s[i]].end(), s[i - 1]);
      }
      if (f) {
        puts("missing hints");
      } else {
        for (int i = sz; i >= 1; --i)
          printf("%d ", s[i]);
        putchar('\n');
      }
    }
  }
}