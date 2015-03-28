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
 
const int N = 10010;
 
const std::string s1 = "qwertyuiop";
const std::string s2 = "asdfghjkl";
const std::string s3 = "zxcvbnm";
 
struct ele {
  std::string s;
  int pri;
  bool operator<(const ele& x) const {
    if (pri != x.pri) return pri < x.pri;
    return s < x.s;
  }
} a[15];
 
std::string s;
std::map<char, int> col, row;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 0; i < int(s1.size()); ++i)
    col[s1[i]] = i, row[s1[i]] = 0;
  for (int i = 0; i < int(s2.size()); ++i)
    col[s2[i]] = i, row[s2[i]] = 1;
  for (int i = 0; i < int(s3.size()); ++i)
    col[s3[i]] = i, row[s3[i]] = 2;
  int tt;
  for (std::cin >> tt; tt--; ) {
    int q;
    std::cin >> s >> q;
    for (int i = 1; i <= q; ++i) {
      std::cin >> a[i].s;
      a[i].pri = 0;
      for (int j = 0; j < int(s.size()); ++j)
        a[i].pri += std::abs(row[s[j]] - row[a[i].s[j]]) +
                    std::abs(col[s[j]] - col[a[i].s[j]]);
    }
    std::sort(a + 1, a + q + 1);
    for (int i = 1; i <= q; ++i)
      std::cout << a[i].s << ' ' << a[i].pri << '\n';
  }
}