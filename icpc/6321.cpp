#include <algorithm>
#include <cassert>
#include <cmath>
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
  scanf("%d", &tt);
  while (tt--) {
    int n, k;
    scanf("%d %d", &n, &k);
    int ans = 0;
    int t;
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &t);
      ans += t / k;
    }
    printf("%d\n", ans);    
  }
}