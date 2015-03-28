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
 
bool a[1010][1010];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  for (int i = 1; i <= n; ++i) {
    std::string s;
    do {
      std::getline(std::cin, s, '\n');
    } while (s.size() < n);
    std::stringstream ss(s);
    for (int j = 1; j <= n; ++j)
      ss >> a[i][j];
  }
  int e[2][1010];
  for (int i = 1; i <= n; ++i) {
    int s[2] = { 0, 0 };
    for (int j = i + 1; j <= n; ++j) {
      int v = a[i][j];
      e[v][s[v]++] = j;
    }
    for (int i1 = 0, i0 = 0; i1 < s[1]; ++i1) {
      while (i0 < s[0] && e[0][i0] < e[1][i1]) ++i0;
      if (i0 >= s[0]) break;
      int x0 = e[0][i0];
      int x1 = e[1][i1];
      for (int p = i0; p < s[0]; ++p)
        if (a[x1][x0]) {
          std::cout << i << ' ' << x1 << ' ' << x0;
          return 0;
        }
    }
  }
  std::cout << "-1 -1 -1";
}