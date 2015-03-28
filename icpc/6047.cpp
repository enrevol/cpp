#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
std::string s[1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  std::ios::sync_with_stdio(0);  
  int tt, n_case = 0;
  std::cin >> tt;
  while (tt--) {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
      std::cin >> s[i];
    int ans = 0;
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
        if (i != j) {
          int l_sz = s[i].size();
          int r_sz = s[j].size();
          int l = 0;
          int r = l_sz + r_sz - 1;
          int f = 1;
          while (l <= r && f) {
            char l_c = l < l_sz ? s[i][l] : s[j][l - l_sz];
            char r_c = r >= l_sz ? s[j][r - l_sz] : s[i][r];
            if (l_c != r_c) f = 0;
            ++l;
            --r;
          }
          ans += f;
        }
    std::cout << "Case #" << ++n_case << ": " << ans << '\n';
  }
}