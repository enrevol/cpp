#include <algorithm>
#include <cmath>
#include <cstdio>
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int r_1, r_2, r_3;
    scanf("%d %d %d", &r_1, &r_2, &r_3);
    double k_1 = double(1) / r_1;
    double k_2 = double(1) / r_2;
    double k_3 = double(1) / r_3;
    double val_1 = k_1 + k_2 + k_3;
    double val_2 = 2 * std::sqrt(k_1 * k_2 + k_2 * k_3 + k_3 * k_1);
    double k_4_1 = val_1 + val_2;
    double k_4_2 = val_1 - val_2;
    double k_4 = std::max(std::abs(k_4_1), std::abs(k_4_2));
    printf("%.17lf\n", 1 / k_4);
  }
} 