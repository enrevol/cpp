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
 
#define m2 std::make_pair
 
typedef std::pair<int, long long> p2l;
typedef std::pair<int, int> p2;
 
std::vector<p2> e[1010];
std::vector<p2l> ee[22];
int s[22], k;
long long a[22][1010], dp[65656][22], ans = -1, cnt, cntt;
 
void bfs(const int& idx) {
  //printf("idx = %d\n", idx);
  std::queue<int> que;
  a[idx][s[idx]] = 0;
  que.push(s[idx]);
  while (!que.empty()) {
    //++cntt;
    int t = que.front();
    que.pop();
    for (int i = 0; i < e[t].size(); ++i) {
      p2 p = e[t][i];
      if (a[idx][p.first] == -1 || a[idx][p.first] > a[idx][t] + p.second) {
        a[idx][p.first] = a[idx][t] + p.second;
        que.push(p.first);
      }
    }
  }
}
 
void dfs(const int& idx, const int& mask, const long long& cost, const int& d) {
  //++cnt;
  //printf("idx = %d tot = %lld d = %d tot = %lld\n", idx, tot, d, dp[mask]);  
  long long val = dp[mask][idx];;
  if (val > cost || !val) {
    dp[mask][idx] = cost;
    for (int i = 0; i < ee[idx].size(); ++i) {
      p2l p = ee[idx][i];
      long long tot = p.second + cost;
      if (ans == -1 || ans > tot) {
        if (p.first == 0) {
          if (d == k) {
            //printf("aa %d\n", tot);
            ans = tot;
          }
        } else if (d < k) {
          if (!(mask & (1 << p.first))) {
            dfs(p.first, mask | (1 << p.first), tot, d + 1);
          }
        }
      }
    }
  }
}
 
bool ff(const p2& lhs, const p2& rhs) {
  return lhs.second < rhs.second;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= k; ++i)
    scanf("%d", s + i);
  int u, v, c;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d %d", &u, &v, &c);
    e[u].push_back(m2(v, c));
  }
  memset(a, -1, sizeof(a));
  s[0] = 1;
  bfs(0);
  for (int i = 1; i <= k; ++i)
    bfs(i);
  for (int i = 0; i <= k; ++i) {
    for (int j = 0; j <= k; ++j)
      if (i != j)
        if (a[i][s[j]] != -1)
          ee[i].push_back(m2(j, a[i][s[j]]));
    std::sort(ee[i].begin(), ee[i].end(), ff);
  }
  dfs(0, 1, 0, 0);
  //printf("cntt = %d\n", cntt);
  //printf("cnt = %d\n", cnt);
  printf("%lld", ans);
} 