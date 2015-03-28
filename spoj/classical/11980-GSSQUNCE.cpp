#include <algorithm>
#include <cstdio>
 
int a[50505];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);    
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    std::sort(a + 1, a + n + 1);
    int f = 1;
    for (int i = 3; i <= n && f; ++i)
      if (a[i] == a[i - 1] && a[i] == a[i - 2])
        f = 0;
    if (f && n >= 2) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
} 