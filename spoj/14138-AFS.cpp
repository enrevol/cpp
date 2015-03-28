#include <cstdio>
#include <iostream>
#include <vector>
typedef long long LL;
using namespace std;
LL f[1000005], a[1000005];
void pre() {
  for (int i = 2; i <= 1000; ++i)
    for (int j = i * i; j <= 1000000; j += i) {
      f[j] += i;
      if (j != i * i) f[j] += j / i;
    }
      
  f[1] = 0;
  for (int i = 2; i <= 1000000; ++i)
    a[i] = a[i - 1] + f[i] + 1;
}
int main() {
  pre();
  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    printf("%lld\n", a[n]);
  }
} 