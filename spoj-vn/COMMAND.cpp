#include <algorithm>
#include <bitset>
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

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  std::string s;
  while (std::cin >> s) {
    if (s == "[END]") break;
    assert(s == "[CASE]");
    std::cin >> s;
    int d = 1, x = 0, y = 0;
    while (std::cin >> s) {
      if (s == ">>") break;
//      std::cout << s << '\n';
      for (int i = 0; i < int(s.size()); ++i) {
        if (s[i] == 'L') {
          ++d;
          if (d >= 4) d -= 4;
        } else if (s[i] == 'R') {
          --d;
          if (d < 0) d += 4;
        } else {
          x += dx[d];
          y += dy[d];
        }
      }
    }
    std::cout << ((x == 0 && y == 0) || (d != 1) ? "bounded" : "unbounded") << '\n';
  }
}
