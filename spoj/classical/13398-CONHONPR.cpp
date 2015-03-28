#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <set>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
int a[105][105], b[105];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    memset(b, 0, sizeof(b));
    memset(a, 0, sizeof(a));
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        scanf("%d", a[i] + j);
    for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
        if (a[i][j] != -1)
          if (a[i][j] == a[i - 1][j] ||
              a[i][j] == a[i + 1][j] ||
              a[i][j] == a[i][j - 1] ||
              a[i][j] == a[i][j + 1] ||
              a[i][j] == a[i - 1][j - 1] ||
              a[i][j] == a[i - 1][j + 1] ||
              a[i][j] == a[i + 1][j - 1] ||
              a[i][j] == a[i + 1][j + 1])
              b[a[i][j]] = 1;
    int ans = 0;
    for (int i = 1; i <= 100; ++i)
      ans += b[i];
    printf("%d\n", ans);
  }
} 