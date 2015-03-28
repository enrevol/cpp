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

const int N = 1000010;

char s[N];
int dp[N][3];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  scanf("%s", s + 1);
  int a = 0, b = 0;
  for (int i = 1; i <= n; ++i) {
    if (s[i] == 'A') {
      dp[i][0] = std::min(dp[i - 1][0], dp[b][1] + 1);
      dp[i][1] = std::min(dp[i - 1][1], dp[a][0] + 1) + 1;
      dp[i][1] = std::min(dp[i][1], dp[i][0] + 1);
      a = i;
    } else {
      dp[i][1] = std::min(dp[i - 1][1], dp[a][0] + 1);
      dp[i][0] = std::min(dp[i - 1][0], dp[b][1] + 1) + 1;
      dp[i][0] = std::min(dp[i][0], dp[i][1] + 1);
      b = i;
    }
  }
  printf("%d", dp[n][0]);
}