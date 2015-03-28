#include <cstdio>
#include <cstring>
 
char s[101010], b[101010];
int a[101010], f[101010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d", a + i);
    for (int i = 1; i < n; ++i) {
      if (a[i] > a[i + 1]) b[i] = 'L';
      else if (a[i] == a[i + 1]) b[i] = 'E';
      else b[i] = 'G';
    }
    b[n] = 0;
    scanf("%s", s + 1);
    char *p = strstr(b + 1, s + 1);
    if (p == NULL) {
      puts("NO");      
    } else {
      puts("YES");
    }
  }
} 