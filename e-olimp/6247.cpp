#include <cmath>
#include <iostream>
#define x first
#define y second
#define pp pair<double, double>
#define eps 0.0001
using namespace std;
pp vect(const pp& A, const pp& B) {
  return make_pair(A.x - B.x, A.y - B.y);
}
double len(const pp& A) {
  return sqrt(A.x * A.x + A.y * A.y);
}
double area(const pp& A, const pp& B, const pp& C) {
  double dAB = len(vect(A, B));
  double dBC = len(vect(B, C));
  double dCA = len(vect(C, A));
  double p = (dAB + dBC + dCA) / 2;
  return sqrt(p * (p - dAB) * (p - dBC) * (p - dCA));
}
int main() {
  int N;
  cin >> N;
  pp A, B, C, t;
  double k1, k2, k3;
  while (N--) {
    cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;    
    double sABC = area(A, B, C);
    int ans = 0;
    for (int i = 0; i <= 100; ++i)
      for (int j = 0; j <= 100; ++j) {
        t = make_pair(i, j);
        k1 = area(t, A, B);
        k2 = area(t, B, C);
        k3 = area(t, C, A);
        if (k1 > eps &&
            k2 > eps &&
            k3 > eps &&
            abs(k1 + k2 + k3 - sABC) <= eps) ans++;
      }
    cout << ans << '\n';
  }
}