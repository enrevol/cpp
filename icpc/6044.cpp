#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::vector<int> e[10101], p;
int cycle[10101], reach[10101], pos[10101], it;
 
int dfs(const int& cur, const int& pre) {
  if (!pos[cur]) {
    pos[cur] = ++it;
    reach[cur] = pos[pre];
    for (int i = 0; i < e[cur].size(); ++i)
      if (e[cur][i] != pre)
        reach[cur] = std::min(reach[cur], dfs(e[cur][i], cur));
    if (reach[cur] < pos[pre])
      cycle[cur] = 1;
  } else {
    cycle[cur] = 1;
  }
  return reach[cur];
}
 
void bfs(const int& idx) {
  cycle[idx] = 1;
  std::queue<int> que;
  que.push(idx);
  int tot = 1;
  while (!que.empty()) {
    int t = que.front();
    que.pop();
    for (int i = 0; i < e[t].size(); ++i)
      if (!cycle[e[t][i]]) {
        ++tot;
        que.push(e[t][i]);
        cycle[e[t][i]] = 1;
      }
  }
  p.push_back(tot);
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {    
    memset(cycle, 0, sizeof(cycle));
    memset(reach, 0, sizeof(reach));
    memset(pos, 0, sizeof(pos));
    int n, m;
    scanf("%d %d", &n, &m);
    int u, v;
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d", &u, &v);
      e[u].push_back(v);
      e[v].push_back(u);
    }
    it = 0;
    for (int i = 1; i <= n; ++i)
      if (!pos[i]) dfs(i, 0);
    p.clear();
    for (int i = 1; i <= n; ++i)
      if (!cycle[i]) bfs(i);
    int ans = 0;
    for (int i = 0; i < p.size(); ++i)
      ans += p[i] * (p[i] - 1);
    ans >>= 1;
    printf("Case #%d: %d\n", ++n_case, ans);
  }
}