#include <cstdio>
#include <cstring>
 
const long long mod = 109546051211ll;
const long long m_1 = 587117;
const long long m_2 = 186583;
long long a_1[595959];
long long a_2[595959];
 
long long f(long long base, long long exp, long long m) {
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
  int n;
  scanf("%d", &n);
  if (n >= 587117) {
    puts("0");
  } else {
    a_1[1] = 1;
    a_2[1] = 1;
    for (int i = 2; i <= n; ++i) {
      a_1[i] = (a_1[i - 1] * i) % m_1;
      a_2[i] = (a_2[i - 1] * i) % m_2;
    }
    long long b_1 = 1;
    long long b_2 = 1;
    for (int i = 2; i <= n; ++i) {
      b_1 = (b_1 * a_1[i]) % m_1;
      b_2 = (b_2 * a_2[i]) % m_2;
    }
    long long d = b_2 - b_1;
    while (d < 0) d += m_2;
    long long add = f(m_1, m_2 - 2, m_2);
    long long t = (d * add) % m_2;
    long long p = m_1 * t + b_1;
    printf("%lld\n", p % mod);
  }
} 