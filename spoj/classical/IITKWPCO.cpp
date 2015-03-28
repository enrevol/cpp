#include <algorithm>
#include <cstdio>
#include <cstring>
 
int a[111], b[111];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);    
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    memset(b, 0, sizeof(b));
    std::sort(a + 1, a + n + 1);
    int left = 1, right = 1;
    int ans = 0;
    while (right <= n) {
      if (a[left] * 2 < a[right]) {
        ++left;
      } else if (a[left] * 2 > a[right]) {
        ++right;
      } else if (b[left]) {
        ++left;
      } else if (b[right]) {
        ++right;
      } else {
        ++ans;
        ++b[left];
        ++b[right];        
        ++left;
        ++right;        
      }
    }
    printf("%d\n", ans);
  }
} 