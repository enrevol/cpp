#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
 
std::vector<int> e[10101];
int a[10101];
 
int bfs(const int& idx) {
  memset(a, -1, sizeof(a));
  std::queue<int> que;
  a[idx] = 0;
  que.push(idx);
  int res = idx;
  while (!que.empty()) {
    int t = que.front();
    que.pop();
    for (int i = 0; i < e[t].size(); ++i) {
      int x = e[t][i];
      int val = a[t] + 1;
      if (a[x] == -1 || a[x] > val) {
        a[x] = val;
        que.push(x);
        if (val > a[res]) res = x;
      }
    }
  }
  return res;
}
 
int main() {
  int n;
  scanf("%d", &n);
  int u, v;
  for (int i = 1; i < n; ++i) {
    scanf("%d %d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
  int x = bfs(1);
  printf("%d", a[bfs(x)]);
} 