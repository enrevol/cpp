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
 
long long ans[1010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);  
  ans[1] = 1;
  for (int i = 2; i <= 1000; ++i)
    for (int j = 0; j < 60 && j < i; ++j) {
      long long t = (((1ll << j) + ans[i - j - 1]) << 1) - 1;
      if (!ans[i] || ans[i] > t)
        ans[i] = t;
    }
  int n;
  int nc = 0;
  while (~scanf("%d", &n))
    if (n) printf("Case %d: %lld\n", ++nc, ans[n]);
} 