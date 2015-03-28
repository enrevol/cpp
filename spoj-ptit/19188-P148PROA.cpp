#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  while (~scanf("%d", &n)) {
    if (n) {
      int ans = 1;
      while (n > 1) {
        if (n & 1) {
          n = n * 3 + 1;
        } else {
          n >>= 1;
        }
        ++ans;
      }
      printf("%d\n", ans);
    }
  }
} 