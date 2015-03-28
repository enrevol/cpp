#include <cmath>
#include <iostream>
typedef long long LL;
using namespace std;
int main() {
 LL n;
 cin >> n;
 LL sq = sqrt(n);
 LL ans = sq * (sq + 1) * 2;
 LL r = 0;
 n -= sq * sq;
 if (n > sq) {
   r = n - sq;
   n = sq;
 }
 if (n) ans += 1 + n * 2;
 if (r) ans += 1 + r * 2;
 cout << ans << "\n";
}