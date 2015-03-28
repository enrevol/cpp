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
 
std::set<p2> s;
std::vector<p2> e[202];
int is_power[202];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    memset(is_power, 0, sizeof(is_power));
    for (int i = 1; i <= n; ++i)
      e[i].clear();
    int t;
    for (int i = 1; i <= k; ++i) {
      scanf("%d", &t);
      is_power[t] = 1;
    }
    int u, v, w;
    for (int i = 1; i <= m; ++i) {
      scanf("%d %d %d", &u, &v, &w);
      e[u].push_back(m2(w, v));
      e[v].push_back(m2(w, u));
    }
    s.clear();
    for (int i = 1; i <= n; ++i)
      if (is_power[i])
        for (int j = 0; j < e[i].size(); ++j)
          s.insert(e[i][j]);
    int ans = 0;
    while (k < n) {
      while (is_power[s.begin()->second])
        s.erase(s.begin());
      ++k;
      p2 t = *s.begin();
      is_power[t.second] = 1;
      ans += t.first;
      for (int i = 0; i < e[t.second].size(); ++i)
        s.insert(e[t.second][i]);
    }    
    printf("Case #%d: %d\n", ++n_case, ans);
  }
}