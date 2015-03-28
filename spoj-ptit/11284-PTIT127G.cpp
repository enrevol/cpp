#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
struct ff {
  bool operator() (const std::string& lhs, const std::string& rhs) {
    size_t l_sz = lhs.size();
    size_t r_sz = rhs.size();
    if (l_sz < r_sz) return 1;
    if (l_sz > r_sz) return 0;
    for (size_t i = 0; i < l_sz; ++i) {
      if (lhs[i] < rhs[i]) return 1;
      if (lhs[i] > rhs[i]) return 0;
    }
    return 0;
  }
};
 
std::multiset<std::string, ff> ms;
std::string str;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n;
  std::cin >> n;
  while (n--) {
    std::cin >> str;
    str += 'a';
    size_t sz = str.size();
    size_t it = 0;
    std::string buffer;
    while (it < sz) {
      if (isdigit(str[it])) {
        if (buffer.size() && buffer[0] == '0') {
          buffer[buffer.size() - 1] = str[it];
        } else {
          buffer += str[it];
        }
      } else {
        if (buffer.size()) {
          ms.insert(buffer);
          buffer.clear();
        }
      }
      ++it;
    }    
  }
  for (__typeof(ms.begin()) i = ms.begin(); i != ms.end(); ++i)
      std::cout << *i << '\n';
} 