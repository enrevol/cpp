#include <cstdio>
#include <vector>
 
std::vector<int> e[1010];
int a[111], b[111][1010];
 
void dfs(int k, int u) {
  if (b[k][u]) return;
  b[k][u] = 1;
  for (size_t i = 0; i < e[u].size(); ++i)
  	dfs(k, e[u][i]);
}
 
int main() {
  int k, n, m;
  scanf("%d %d %d", &k, &n, &m);
  for (int i = 1; i <= k; ++i)
  	scanf("%d", a + i);
  int u, v;
  for (int i = 1; i <= m; ++i) {
  	scanf("%d %d", &u, &v);
  	e[u].push_back(v);
  }
  for (int i = 1; i <= k; ++i)
  	dfs(i, a[i]);
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
  	int cnt = 0;
  	for (int j = 1; j <= k; ++j)
      cnt += b[j][i];
    ans += cnt == k;
  }
  printf("%d", ans);
} 