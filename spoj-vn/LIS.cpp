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

const int N = 30010;
const long long INF = 1e10;

long long dp[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  int ans = 0;
  dp[0] = -INF;
  for (int i = 0; i < n; ++i) {
    int a;
    scanf("%d", &a);
    int p = std::lower_bound(dp, dp + ans + 1, a) - dp;
    if (p > ans) {
      ans = p;
      dp[p] = a;
    } else if (dp[p] > a) {
      dp[p] = a;
    }
  }
  printf("%d", ans);
}
