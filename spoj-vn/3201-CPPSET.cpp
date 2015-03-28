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
 
std::set<int> s;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  for (int k, v; std::cin >> k; ) {
    if (k == 0) break;
    if (k <= 2) {
      std::cin >> v;
      if (k == 1) s.insert(v);
      else s.erase(v);
    } else {
      int sz = s.size();
      if (sz == 0) {
        std::cout << "empty";
      } else {
        if (k == 3) std::cout << *s.begin();
        else
        if (k == 4) std::cout << *s.rbegin();
        else {
          std::set<int>::iterator it;
          std::cin >> v;
          if (k <= 6) {
            if (k == 5) it = s.upper_bound(v);
            else it = s.lower_bound(v);
            if (it == s.end()) std::cout << "no";
            else std::cout << *it;
          } else {
            if (k == 7) it = s.lower_bound(v);
            else it = s.upper_bound(v);
            if (it == s.begin()) std::cout << "no";
            else std::cout << *--it;
          }
        }
      }
      std::cout << '\n';
    }    
  }
}