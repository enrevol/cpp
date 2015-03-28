#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
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
 
const unsigned base = 29;
 
char s[1010101];
unsigned p[1010101];
unsigned h[1010101]; 
 
inline unsigned get(int f, int t) {
  return h[t] - h[f - 1] * p[t - f + 1];
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  int n = strlen(s + 1);
  p[0] = 1;
  for (int i = 1; i <= n; ++i) {
    p[i] = p[i - 1] * base;
    h[i] = h[i - 1] * base + (s[i] - 'a');
  }
  for (int i = n - 2; i >= 1; --i) {
    if (get(1, i) != get(n - i + 1, n)) continue;
    unsigned v = get(1, i);
    for (int j = 2; j + i <= n; ++j)
      if (v == get(j, j + i - 1)) {
        assert(memcmp(s + 1, s + n - i + 1, i) == 0);
        assert(memcmp(s + 1, s + j, i) == 0);
        s[i + 1] = 0;
        puts(s + 1);
        return 0;
      }
  }
  puts("Just a legend");
}