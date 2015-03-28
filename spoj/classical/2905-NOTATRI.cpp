#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
int a[2020];
 
int main() {
  int n;
  while (scanf("%d", &n) == 1) {
    if (n == 0) break;
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
      int left = i + 1;
      int right = i + 2;
      while (right <= n) {
        if (a[i] + a[left] >= a[right]) {
          ++right;
        } else {
          ans += n - right + 1;
          ++left;
        }
      }
    }
    printf("%d\n", ans);
  }
} 