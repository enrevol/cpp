#include <algorithm>
#include <cmath>
#include <cstdio>
 
const int m = 1000000007;
 
long long f(long long base, long long exp) {
  long long res = 1;
  while (exp) {
    if (exp & 1) {
      res = (res * base) % m;
      --exp;
    }
    base = (base * base) % m;
    exp >>= 1;
  }
  return res;
}
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    if (n == 1) {
      puts("1");
    } else {
      long long t_2 = n >> 1;
      long long t_3 = 0;
      if (n & 1) {
        --t_2;
        ++t_3;
      }
      long long num = t_2 / 3;
      t_3 += num * 2;
      t_2 -= num * 3;
      printf("%lld\n", (f(2, t_2) * f(3, t_3)) % m);
    }
  }
} 