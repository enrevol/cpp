#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;
const double eps = 1e-12;
const double PI = 3.14159265358979323;
int n, a[1005];
double b[1005];
double solve(double left, double right) {
  if (right - left < eps) return 0;
  double mid = (left + right) / 2;
  double tot = 0;
  for (int i = 0; i < n; ++i) {
    tot += asin(b[i] / mid);
    if (tot > PI) break;
  }
  if (abs(tot - PI) / PI < eps) return mid;
  else if (tot > PI) return solve(mid, right);
  else return solve(left, mid);
}
int main() {
#ifdef ONLINE_JUDGE
  freopen("zeriba.in", "r", stdin);
#endif  
  int T, nCase = 0;
  cin >> T;  
  while (T--) {
    cin >> n;
    int sum = 0, imax = 0;
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      sum += a[i];
      b[i] = a[i] * .5f;
      if (b[i] > b[imax]) imax = i;
    }
    cout << "Case " << setprecision(0) << ++nCase << ": ";
    int f = 1;    
    for (int i = 0; i < n && f; ++i)
      if (a[i] * 2 >= sum) f = 0;
    if (f) {
      double ans = solve(b[imax], 1 << 18);
      if (!ans) ans = b[imax];
      cout << fixed << setprecision(4) << ans << '\n';
    } else {
      cout << "can't form a convex polygon\n";
    }
  }
}