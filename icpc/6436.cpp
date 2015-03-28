#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
std::vector<p2> e[20202];
int a[20202], n;
 
int dfs(const int& idx, const int& pre) {
  if (a[idx] == -1) {
    a[idx] = 0;
    int tot = 0, f = -1;
    for (int i = 0; i < e[idx].size(); ++i) {
      if (e[idx][i].first != pre) {
        e[idx][i].second = dfs(e[idx][i].first, idx);
        tot += e[idx][i].second;
      } else {
        f = i;
      }
    }
    if (f != -1) e[idx][f].second = n - tot - 1;
  }
  for (int i = 0; i < e[idx].size(); ++i)
    if (e[idx][i].first == pre)
      return n - e[idx][i].second;  
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    memset(a, -1, sizeof(a));    
    int u, v;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    for (int i = 1; i < n; ++i) {
      scanf("%d %d", &u, &v);
      e[u].push_back(m2(v, -1));
      e[v].push_back(m2(u, -1));
    }
    dfs(1, 0);
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      long long tot = 0;
      for (int j = 0; j < e[i].size(); ++j)
        tot += (n - 1 - e[i][j].second) * 1ll * (e[i][j].second);
      //printf("i = %d tot = %lld\n", i, tot);
      tot >>= 1;
      if (tot > ans) ans = tot;
    }
    printf("Case #%d: %lld\n", ++n_case, ans);
  }
}