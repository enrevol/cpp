#include <algorithm>
#include <cmath>
#include <iostream>
typedef long long LL;
using namespace std;
int main() {
  LL n, ans = 0;
  cin >> n;
  LL x = 1;
  while (x * x * x <= n) x++;
  x--;
  n -= x * x * x;
  ans += x * (x + 1) * (x + 1) * 3;
  LL s[3] = {x, x, x};
  while (n) {
    sort(s, s + 3);
    LL ms = s[1] * s[2];
    LL k = min(n, ms);
    LL sq = sqrt(k);
    LL r = k - sq * sq;
    n -= k;
    ans += (sq + 1) * (sq + 1) + sq * (sq + 1) * 2;
    if (r) {
      LL r2 = 0;
      if (r > sq) {        
        r2 = r - sq;
        r = sq;
      }
      ans += r + (r + 1) * 2;
      if (r2) ans += r2 + (r2 + 1) * 2;
    }
    s[0]++;
  }
  cout << ans << '\n';
}