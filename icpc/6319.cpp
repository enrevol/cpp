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
 
std::string s, t, r;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  std::ios::sync_with_stdio(0);
  int tt;
  std::cin >> tt;
  while (tt--) {
    std::cin >> s;
    int x, y;
    while (1) {
      std::cin >> t;
      if (t[0] == 'E') break;
      if (t[0] == 'I') {
        std::cin >> r >> x;
        s.insert(x, r);
      } else {
        std::cin >> x >> y;
        std::cout << s.substr(x, y - x + 1) << '\n';
      }
    }
  }
}