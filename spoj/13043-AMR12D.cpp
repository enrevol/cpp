#include <algorithm>
#include <cstdio>
#include <cstring>
 
char s[1010], t[1010];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    scanf("%s", s + 1);
    int sz = strlen(s + 1);
    strcpy(t + 1, s + 1);
    std::reverse(t + 1, t + sz + 1);
    int f = 1;
    for (int i = 1; i <= sz && f; ++i)
      f = s[i] == t[i];
    if (f) puts("YES");
    else puts("NO");
  }
} 