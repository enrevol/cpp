#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
typedef long long LL;
using namespace std;
int pw(int power) {  
  if (power == 0) return 1;
  else return pw(power - 1) * 10;
}
int main() {
  char str[55];
  while (scanf("%s", str) != EOF) {
    int n1, n2, n3;
    char s1[22], s2[22], s3[22];
    memset(s1, 0, sizeof(s1));
    memset(s2, 0, sizeof(s2));
    memset(s3, 0, sizeof(s3));
    sscanf(str, "%[^.]%[^(](%[^)]", s1, s2, s3);
    n1 = atoi(s1);
    if (strlen(s2) > 1) n2 = atoi(s2 + 1);
    else n2 = 0;
    n3 = atoi(s3);
    int p2 = pw(strlen(s2) - 1);
    int p3 = pw(strlen(s3)) - 1;
    int g1 = __gcd(n3, p3);
    n3 /= g1;
    p3 /= g1;
    p3 *= pw(strlen(s2) - 1);
    LL ts = n2 * 1LL * p3 + n3 * 1LL * p2;
    LL ms = p2 * 1LL * p3;
    LL g2 = __gcd(ts, ms);
    ts /= g2;
    ms /= g2;
    ts += ms * n1;
    printf("%s%s(%s) = %I64d / %I64d\n", s1, s2, s3, ts, ms);
  }
}