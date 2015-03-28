#include <algorithm>
#include <cstdio>
#include <cstring>
 
const long long mod = 1000000007;
long long a[303];
 
long long f(long long base) {
  long long res = 1;
  int exp = mod - 2;
  while (exp) {
    if (exp & 1) {
      res = (res * base) % mod;
      --exp;
    }
    base = (base * base) % mod;
    exp >>= 1;
  }
  return res;
}
 
int main() {
  a[0] = 1;
  for (int i = 1; i <= 300; ++i)
    a[i] = (a[i - 1] * i) % mod;
  int n, w, t, r;
  scanf("%d %d %d %d", &n, &w, &t, &r);
  long long val_1 = (((a[n] * f(a[w])) % mod) * f(a[n - w])) % mod;
  long long val_2 = (((a[n - w] * f(a[t])) % mod) * f(a[n - w - t])) % mod;
  printf("%lld", (val_1 * val_2) % mod);
} 