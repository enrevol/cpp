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
 
typedef std::pair<int, int> p2;
 
std::vector<p2> v;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int x, y;
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &x, &y);
    v.push_back(p2(x, 1));
    v.push_back(p2(y + 1, -1));
  }
  std::sort(v.begin(), v.end());
  int ans = 0;
  int tot = 0;
  for (std::vector<p2>::iterator i = v.begin(); i != v.end(); ++i) {
    tot += i->second;
    ans = std::max(ans, tot);
  }
  printf("%d", ans);
}