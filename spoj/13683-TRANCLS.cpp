#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::set<int> e[101];
int g[101], cnt;
 
void dfs(const int& idx) {
  for (std::set<int>::iterator i = e[idx].begin(); i != e[idx].end(); ++i)
    if (!g[*i]) {
      g[*i] = 1;
      ++cnt;
      dfs(*i);
    }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int u, v;
    for (int i = 0; i < n; ++i)
      e[i].clear();
    for (int i = 1; i <= n; ++i) {
      scanf("%d %d", &u, &v);
      e[u].insert(v);
    }
    int tot = 0;    
    cnt = 0;
    for (int i = 0; i < n; ++i) {
      tot += e[i].size();
      memset(g, 0, sizeof(g));
      dfs(i);
    }
    printf("Case #%d: %d\n", ++n_case, cnt - tot);
  }
} 