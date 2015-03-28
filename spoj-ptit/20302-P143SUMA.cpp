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
 
const int N = 1010;
 
struct dragon {
  int power;
  int exp;
  bool operator<(const dragon& x) const {
    return power < x.power;
  }
} a[N];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, exp;
  scanf("%d %d", &exp, &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d", &a[i].power, &a[i].exp);
  std::sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; ++i) {
    if (exp <= a[i].power) {
      puts("NO");
      return 0;
    } else {
      exp += a[i].exp;
    }
  }
  puts("YES");
}