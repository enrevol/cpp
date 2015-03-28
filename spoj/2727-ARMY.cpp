#include <cstdio>
#include <cstring>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int ng, nm;
    scanf("%d %d", &ng, &nm);
    int best_1, best_2, a;
    scanf("%d", &best_1);
    for (int i = 1; i < ng; ++i) {
      scanf("%d", &a);
      if (a > best_1) best_1 = a;
    }
    scanf("%d", &best_2);
    for (int i = 1; i < nm; ++i) {
      scanf("%d", &a);
      if (a > best_2) best_2 = a;
    }
    if (best_1 >= best_2) puts("Godzilla");
    else puts("MechaGodzilla");
  }
} 