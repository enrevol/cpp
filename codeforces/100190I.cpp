#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#define pLL pair<LL, LL>
#define pDD pair<double, double>
#define x first
#define y second
typedef long long LL;
using namespace std;
const double eps = 1e-6;
double dist(pDD p1, pDD p2) {
  return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
void lines(pLL p1, pLL p2, LL& A, LL& B, LL& C) {
  A = p2.y - p1.y;
  B = p1.x - p2.x;
  C = A * p1.x + B * p1.y;
  LL g = __gcd(A, __gcd(B, C));
  A /= g;
  B /= g;
  C /= g;
}
int main() {
  //freopen("input.txt", "r", stdin);
  pLL L1, L2, W1, W2;
  int nCase = 0;
  double ans;
  while (cin >> L1.x >> L1.y >> L2.x >> L2.y) {    
    if (L1.x == 0 && L1.y == 0 && L2.x == 0 && L2.y == 0) break;
    cin >> W1.x >> W1.y >> W2.x >> W2.y;
    double dL1L2 = dist(L1, L2);
    double dW1W2 = dist(W1, W2);
    LL A1, B1, C1;
    LL A2, B2, C2;
    lines(L1, L2, A1, B1, C1);
    lines(W1, W2, A2, B2, C2);
    LL det = A1 * B2 - B1 * A2;
    if (det == 0) {
      ans = dL1L2;
    } else {
      LL detX = - C1 * B2 + B1 * C2;
      LL detY = - A1 * C2 + C1 * A2;
      pDD intersect = make_pair(- detX * 1.f / det, - detY * 1.f / det);
      double dIL1 = dist(L1, intersect);
      double dIL2 = dist(L2, intersect);
      double dIW1 = dist(W1, intersect);
      double dIW2 = dist(W2, intersect);      
      if (abs(dIL1 + dL1L2 - dIL2) <= eps ||
          abs(dIL2 + dL1L2 - dIL1) <= eps ||
          abs(dIW1 + dW1W2 - dIW2) <= eps ||
          abs(dIW2 + dW1W2 - dIW1) <= eps) {
        ans = dL1L2;
      } else {
        ans = min(dist(L1, W1) + dist(L2, W1), dist(L1, W2) + dist(L2, W2));
      }
    }
    cout << fixed << "Case " << setprecision(0) << ++nCase << ": " << setprecision(3) << ans / 2 << '\n';
  }
}