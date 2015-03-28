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
 
std::string a, b, s;
int z[2020202];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cin >> a >> b;
  int sa = int(a.size());
  int sb = int(b.size());
  s = b + '0' + a;
  int sz = int(s.size());
  for (int i = 1, l = 0, r = 0; i < sz; ++i) {
    if (r < i) {
      l = r = i;
      while (r < sz && s[r] == s[r - l]) ++r;
      z[i] = r - l;
      --r;
    } else {
      int k = i - l;
      if (z[k] <= r - i) {
        z[i] = z[k];
      } else {
        l = i;
        while (r < sz && s[r] == s[r - l]) ++r;
        z[i] = r - l;
        --r;
      }
    }
    if (z[i] == sb) {
      printf("%d ", i - sb);
    }
  }  
}