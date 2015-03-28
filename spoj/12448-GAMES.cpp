#include <algorithm>
#include <cstdio>
#include <cstring>
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    char s[55];
    memset(s, 0, sizeof(s));
    scanf("%s", s + 1);
    int k = -1;
    for (int i = 1; s[i] && k == -1; ++i)
      if (s[i] == '.') k = i;
    if (k == -1) {
      puts("1");
    } else {
      int t = 1000;
      int val = 0;
      ++k;
      while (s[k]) {
        val += (s[k] - '0') * t;
        ++k;
        t /= 10;
      }
      int g = std::__gcd(val, 10000);
      printf("%d\n", 10000 / g);
    }
  }
} 