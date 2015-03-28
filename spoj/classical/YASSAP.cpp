#include <algorithm>
#include <bitset>
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
 
const int N = 55;
const int MAX = 1010;

long long dp[N * MAX];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    memset(dp, 0, sizeof(dp));
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
      int a;
      scanf("%d", &a);
      for (int j = sum; j >= 1; --j) {
        dp[j + a] |= dp[j] << 1;
      }
      sum += a;
      dp[a] |= 1 << 1;
    }
    int best = 0;
    int x = 0;
    for (int i = sum; i >= 1; --i) {
      int cnt = __builtin_popcountll(dp[i]);
      if (cnt >= best) {
        best = cnt;
        x = i;
      }
    }
    printf("%d %d\n", best, x);
  }
}