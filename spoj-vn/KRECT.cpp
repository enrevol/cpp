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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }
 
using namespace std;
 
const int N = 110;
 
char s[N][N];
int b[N][N][26];

inline int calc(int x1, int y1, int x2, int y2, int z) {
  return b[x2][y2][z] + b[x1 - 1][y1 - 1][z] - b[x2][y1 - 1][z] - b[x1 - 1][y2][z];
}

inline int count(int x1, int y1, int x2, int y2) {  
  int r = 0;
  for (int i = 0; i < 26; ++i) {
    r += calc(x1, y1, x2, y2, i) > 0;
  }
  return r;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m, k;
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; ++j)
      for (int z = 0; z < 26; ++z) {
        b[i][j][z] = b[i - 1][j][z] + b[i][j - 1][z] - b[i - 1][j - 1][z] + (s[i][j] == 'A' + z);
      }
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      int lower = n + 1, upper = n + 1;
      for (int jj = j; jj <= m; ++jj) {
        while (lower - 1 >= i && count(i, j, lower - 1, jj) >= k) --lower;
        while (upper - 1 >= i && count(i, j, upper - 1, jj) > k) --upper;
        if (upper == i) break;
//        if (lower < upper) {
          ans += upper - lower;
//        }
//        cerr << "i = " << i << "  j = " << j << "  jj = " << jj << "  lower = " << lower << "  upper = " << upper << "  ans = " << ans << '\n';
      }
    }
  }
  printf("%d", ans);
}
