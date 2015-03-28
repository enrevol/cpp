#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
 
std::vector<int> e[101010];
 
int a[10][101010];
int dp[1 << 8][8];
 
void bfs(int p) {
  std::queue<int> que;
  que.push(p);
  a[p][p] = 0;
  while (!que.empty()) {
    int t = que.front();
    que.pop();
    for (size_t i = 0; i < e[t].size(); ++i) {
      int k = e[t][i];
      if (a[p][k] == -1) {
        a[p][k] = a[p][t] + 1;
        que.push(k);
      }
    }
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k, m;
  scanf("%d %d %d", &n, &k, &m);
  int u, v;  
  for (int i = 0; i < m; ++i) {
    scanf("%d %d", &u, &v);
    e[u].push_back(v);
  }
  memset(a, -1, sizeof(a));
  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < k; ++i)
    bfs(i);
  for (int i = 0; i < k; ++i)
    dp[1 << i][i] = a[0][i];
  for (int mask = 0; mask < 1 << k; ++mask) {
    int cnt = 0;
    int t = mask;
    while (t) {
      t -= t & -t;
      ++cnt;
    }
    if (cnt > 1)
      for (int i = 0; i < k; ++i)
        if (mask & (1 << i)) {
          int nmask = mask ^ (1 << i);
          for (int j = 0; j < k; ++j)
            if (nmask & (1 << j))
              if (a[j][i] != -1) {
                int& v = dp[mask][i];
                int tot = dp[nmask][j] + a[j][i];            
                if (v == -1 || v > tot)
                  v = tot;
              }
        }
  }
  int ans = -1;
  for (int i = 1; i < k; ++i)
    if (a[i][0] != -1) {
      int tot = dp[(1 << k) - 1][i] + a[i][0];
      if (ans == -1 || ans > tot)
        ans = tot;
    }
  printf("%d", ans);
} 