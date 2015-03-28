#include <cstdio>
 
int main() {
  int n;
  scanf("%d", &n);
  while (n--) {
    int a, b;
    scanf("%d", &a);
    if (a & 1) {
      b = a;
    } else {
      b = 0;
      while (a) {
        b |= a & 1;
        a >>= 1;      
        b <<= 1;
      }
      b >>= 1;
    }
    printf("%d\n", b);
  }
} 