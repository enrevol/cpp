#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
char s[101010], ans[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  int sz = 0;
  char c = -1;
  for (int i = n; i >= 1; --i) {
    if (c == -1 || c <= s[i]) {
      c = s[i];
      ans[++sz] = s[i];
    }
  }
  std::reverse(ans + 1, ans + sz + 1);
  printf("%s", ans + 1);
} 