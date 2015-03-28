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
 
char s[33][33];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", s[i] + 1);
  int q;
  scanf("%d", &q);
  for (int y; q--; ) {
    scanf("%d", &y);
    int x = 1;
    while (1) {
      if (x == n) break;
      if (s[x + 1][y] == 'X') break;
      if (s[x + 1][y] == '.') {
        ++x;
      } else {
        assert(s[x + 1][y] == 'O');
        if (y > 1 && s[x][y - 1] == '.' && s[x + 1][y - 1] == '.') {
          --y;
          ++x;
        } else
        if (y < m && s[x][y + 1] == '.' && s[x + 1][y + 1] == '.') {
          ++y;
          ++x;
        } else break;
      }
    }
    s[x][y] = 'O';
  }
  for (int i = 1; i <= n; ++i)
    printf("%s\n", s[i] + 1);
}