#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct cmp {
  bool operator () (const int& a, const int& b) {
    return a > b;
  }
};
 
std::multiset<int, cmp> s[111];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    printf("Case #%d:\n", ++n_case);
    int n, t, v, r;
    scanf("%d", &n);
    for (int i = 0; i <= 100; ++i)
      s[i].clear();
    for (int i = 1; i <= n; ++i) {
      char c[5];
      scanf("%s", c);
      if (c[0] == 'P') {
        scanf("%d %d %d", &t, &v, &r);
        s[r].insert(v - r * t);
      } else {
        scanf("%d", &t);
        int val = -1, rate = -1;
        for (int i = 0; i <= 100; ++i) {
          if (s[i].size()) {
            int tot = *s[i].begin() + i * t;
            if (tot >= val || rate == -1) {
              val = tot;
              rate = i;
            }
          }
        }
        s[rate].erase(s[rate].begin());
        printf("%d %d\n", val, rate);
      }
    }
  }
}