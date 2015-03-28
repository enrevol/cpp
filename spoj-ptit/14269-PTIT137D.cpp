#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
char s[22][77];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%s", s[i] + 1);
    int lo = 1, hi = 60;
    std::string ans;
    while (lo <= hi) {
      int mi = (lo + hi) >> 1;
      //printf("mi = %d\n", mi);
      char buffer[77];
      int ff = 0;
      std::set<std::string> st;
      for (int i = 1; i + mi - 1 <= 60; ++i) {
        memset(buffer, 0, sizeof(buffer));
        strncpy(buffer + 1, s[1] + i, mi);
        //printf("i = %2d buffer = %s\n", i, buffer + 1);
        int f = 1;
        for (int j = 2; j <= n && f; ++j)
          if (strstr(s[j] + 1, buffer + 1) == NULL)
            f = 0;
        ff |= f;
        if (f) {
          std::string str(buffer + 1);
          st.insert(str);
        }
      }
      if (ff) {
        ans = *(st.begin());
        lo = mi + 1;
      } else {
        hi = mi - 1;
      }
    }
    if (ans.size() < 3) {
      puts("no significant commonalities");
    } else {
      //printf("%d ", strlen(ans + 1));
      std::cout << ans << '\n';
    }
  }
} 