#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    int ans[11];
    memset(ans, 0, sizeof(ans));
    for (int i = 1; i <= n; ++i) {
      int t = i;
      while (t) {
        ++ans[t % 10];
        t /= 10;
      }
    }
    printf("%d", ans[0]);
    for (int i = 1; i <= 9; ++i)
      printf(" %d" , ans[i]);
    putchar('\n');
  }
}