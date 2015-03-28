#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
 
std::map<int, int> m;
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    int x, n, a;
    scanf("%d %d", &x, &n);
    m.clear();
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a);      
      ans += m[x - a];
      ++m[a];
    }
    printf("%d. %lld\n", ++n_case, ans);
  }
} 