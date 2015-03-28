#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
const int mod = 10000007;
int g[105][105];
 
int main() {
  int n, r;
  scanf("%d %d", &n, &r);
  if (n < r) {
    puts("-1");
  } else if (r == 1) {
    puts("1");
  } else {
    for (int i = 1; i <= 100; ++i) {
      g[1][i] = i;
      g[i][i] = 1;
    }
    for (int i = 2; i <= 100; ++i)
      for (int j = 2; j <= 100; ++j)
        g[i][j] = (g[i - 1][j - 1] + g[i][j - 1]) % mod;
    printf("%d", g[r - 1][n - 1]);
  }
} 