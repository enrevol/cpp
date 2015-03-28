#include <algorithm>
#include <cstdio>
#include <cstring>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int w, b;
    scanf("%d %d", &w, &b);
    if (b & 1) {
      puts("1.000000");
    } else {
      puts("0.000000");
    }
  }
} 