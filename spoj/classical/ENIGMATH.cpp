#include <algorithm>
#include <cstdio>
 
int main() {  
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int a, b;
    scanf("%d %d", &a, &b);
    int g = std::__gcd(a, b);
    printf("%d %d\n", b / g, a / g);
  }
} 