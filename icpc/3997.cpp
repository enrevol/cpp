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
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  std::cin >> tt;
  while (tt--) {
    int n;
    std::string s;
    std::cin >> n >> s;
    size_t sz = s.size();
    long long k = 0;
    for (size_t i = 0; i < sz; ++i) {
      k = (k << 3) + (k << 1) + s[i] - '0';
      k %= n;
    }
    std::cout << k << '\n';
  }
}