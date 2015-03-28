#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>
#include <set>
#include <vector>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
long long a[10101], b[10101], c[10101], d[10101], e[10101], s[10101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt, n_case = 0;
  scanf("%d", &tt);
  while (tt--) {
    printf("Case #%d: ", ++n_case);
    long long m;
    scanf("%lld %lld %lld %lld %lld %lld", a, b, c, d, e, &m);
    s[0] = a[0] + b[0] + c[0] + d[0] + e[0];
    if (s[0] >= m) {
      puts("0");
    } else {
      int k = 1;
      int f = -1;    
      while (1 && f == -1) {
        a[k] = a[k - 1] + b[k - 1];
        b[k] = b[k - 1] + c[k - 1];
        c[k] = c[k - 1] + d[k - 1];
        d[k] = d[k - 1] + e[k - 1];
        e[k] = e[k - 1] + a[k - 1];
        s[k] = a[k] + b[k] + c[k] + d[k] + e[k];
        if (s[k] >= m) {
          f = k;
        } else if (s[k] <= s[k - 1]) {
          break;
        }
        ++k;
      }
      printf("%d\n", f);
    }
  }
}