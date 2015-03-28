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

typedef std::pair<long long, long long> p2;

std::vector<int> a[101010];
std::vector<p2> dp[101010];

int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, m, t;
  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    std::cin >> t;
    a[(i % m) + 1].push_back(t);
  }
  long long ans = 0;
  for (int i = 1; i <= m; ++i) {
    int sz = a[i].size();
    if (sz) {
      dp[i].push_back(std::make_pair(0, 0));
      for (int j = 1; j < sz; ++j) {
        dp[i].push_back(std::make_pair(dp[i][j - 1].second + a[i][j - 1] + a[i][j], std::max(dp[i][j - 1].first, dp[i][j - 1].second)));
      }
      ans += std::max(dp[i][sz - 1].first, dp[i][sz - 1].second);
    }
  }
  std::cout << ans << '\n';
}