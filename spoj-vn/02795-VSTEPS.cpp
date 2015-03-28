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
 
bool a[101010];
int dp[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k, t;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= k; ++i) {
    scanf("%d", &t);
    a[t] = 1;
  }
  dp[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!a[i]) {
      dp[i] = (dp[i - 1] + dp[i - 2]) % 14062008;
    }
  }
  printf("%d", dp[n]);
} 