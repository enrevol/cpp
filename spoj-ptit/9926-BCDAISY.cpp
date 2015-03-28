#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
std::vector<int> e[252];
bool a[252];
 
void dfs(int u) {
  if (a[u]) return;
  a[u] = true;
  for (size_t i = 0; i < e[u].size(); ++i)
    dfs(e[u][i]);  
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  int u, v;
  for (int i = 1; i <= m; ++i) {
    scanf("%d %d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  dfs(1);
  int cnt = 0;
  for (int i = 1; i <= n; ++i) {
    cnt += !a[i];
    if (!a[i]) printf("%d\n", i);
  }
  if (!cnt) printf("0");
} 