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
 
bool sieve[10101];
 
inline void af(int num, char arr[]) {
  arr[4] = num % 10;
  arr[3] = (num / 10) % 10;
  arr[2] = (num / 100) % 10;
  arr[1] = num / 1000;
}
 
int dp[10101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 2; i * i <= 9999; ++i)
    if (!sieve[i])
      for (int j = i * i; j <= 9999; j += i)
        sieve[j] = true;
  int tt;
  scanf("%d", &tt);
  int x, y;
  while (tt--) {
    scanf("%d %d", &x, &y);
    memset(dp, -1, sizeof(dp));
    std::queue<int> que;
    que.push(x);
    dp[x] = 0;
    while (!que.empty()) {      
      int v = que.front();
      que.pop();
      char arr[5];
      af(v, arr);
      {
        int t = v - arr[4];
        for (int i = 1; i <= 9; i += 2) {
          int z = t + i;
          if (!sieve[z])
            if (dp[z] == -1) {
              dp[z] = dp[v] + 1;
              que.push(z);
            }
        }
      }
      {
        int t = v - arr[3] * 10;
        for (int i = 0; i <= 9; ++i) {
          int z = t + i * 10;
          if (!sieve[z])
            if (dp[z] == -1) {
              dp[z] = dp[v] + 1;
              que.push(z);
            }
        }
      }
      {
        int t = v - arr[2] * 100;
        for (int i = 0; i <= 9; ++i) {
          int z = t + i * 100;
          if (!sieve[z])
            if (dp[z] == -1) {
              dp[z] = dp[v] + 1;
              que.push(z);
            }
        }
      }
      {
        int t = v - arr[1] * 1000;
        for (int i = 1; i <= 9; ++i) {
          int z = t + i * 1000;
          if (!sieve[z])
            if (dp[z] == -1) {
              dp[z] = dp[v] + 1;
              que.push(z);
            }
        }
      }
    }
    printf("%d\n", dp[y]);
  }
} 