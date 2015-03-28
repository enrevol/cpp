#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
void solve(int& ans, int n, int k) {
  if (n <= k || ((n - k) & 1)) {
    ++ans;
  } else {
    int val = (n - k) >> 1;
    solve(ans, val, k);
    solve(ans, n - val, k);
  }
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  int ans = 0;
  solve(ans, n, k);
  printf("%d", ans);
}