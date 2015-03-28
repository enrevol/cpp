#include <algorithm>
#include <cstdio>
#include <map>
 
const int mod_1 = 1000000006;
const int mod_2 = 1000000007;
 
std::map<long long, int> m;
int fi[20];
 
int f_1(const long long& k) {
  if (k < 20) return fi[k];
  if (m[k]) return m[k];
  long long val_1, val_2, res;
  if (k & 1) {
    val_1 = f_1(k >> 1);
    val_2 = f_1((k >> 1) + 1);
    res = (1ll * val_1 * val_1 + 1ll * val_2 * val_2) % mod_1;
  } else {
    val_1 = f_1((k >> 1) - 1);
    val_2 = f_1(k >> 1);
    res = (val_2 * (2ll * val_1 + val_2)) % mod_1;
  }
  m[k] = res;
  return res;
}
 
int f_2(int base, int exp, int mod) {
  int res = 1;
  while (exp) {
    if (exp & 1) res = (1ll * res * base) % mod;
    exp >>= 1;
    base = (1ll * base * base) % mod;
  }
  return res;
}
 
int main() {
  fi[1] = fi[2] = 1;
  for (int i = 2; i < 20; ++i)
    fi[i] = fi[i - 1] + fi[i - 2];
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    printf("%d\n", f_2(2, f_1(n), mod_2));
  }  
} 