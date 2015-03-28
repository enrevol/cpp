#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

char s[101010];

int main() {
  freopen("clumsy.in", "r", stdin);
  freopen("clumsy.out", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  int x = 0;
  int y = 0;
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    x += s[i] == '(';
    y += s[i] == ')';
    if (x < y) {
      ++x;
      --y;
      ++ans;
    } else if (x > (n >> 1)) {
      --x;
      ++y;
      ++ans;
    }
  }
  printf("%d", ans);
}
