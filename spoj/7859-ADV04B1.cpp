#include <cstdio>
#include <iostream>
#define M 1000003
#define N 1000000
typedef long long LL;
using namespace std;
LL ans[N + 5];
LL pw(int base, int exp) {
  if (exp == 0) return 1;
  LL t = pw(base, exp >> 1);
  t = (t * t) % M;
  if (exp & 1) t = (t * base) % M;
  return t;
}
void pre() {
  ans[0] = 1;
  ans[1] = 3;
  LL t1, t2;
  for (int i = 2; i <= N; ++i) {
    t1 = 3 * (2 * i - 1) * ans[i - 1] - (i - 1) * ans[i - 2];    
    t2 = pw(i, M - 2);
    ans[i] = (t1 * t2) % M;
    if (ans[i] < 0) ans[i] += M;
  }
}
int main() {
  pre();
  int t, n;
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    printf("%I64d\n", ans[n - 1]);
  }
}