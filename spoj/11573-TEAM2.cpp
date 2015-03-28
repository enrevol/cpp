#include <algorithm>
#include <cstdio>
 
int a[4];
 
int main() {
  int n_case = 0;
  while (scanf("%d %d %d %d", a + 1, a + 2, a + 3, a + 4) == 4) {  
    int ans = 0;
    for (int i = 1; i <= 4; ++i)
      for (int j = 1; j <= 4; ++j)
        if (i != j) ans = std::max(ans, a[i] + a[j]);
    printf("Case %d: %d\n", ++n_case, ans);
  }
} 