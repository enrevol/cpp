#include <cmath>
#include <iostream>
#define x first
#define y second
#define pp pair<double, double>
using namespace std;
pp p1, p2;
double r1, r2;
double dist(const pp& a, const pp& b) {
 return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
double vsize2(const pp& a) {
 return a.x * a.x + a.y * a.y;
}
int main() {
 cin >> p1.x >> p1.y >> r1 >> p2.x >> p2.y >> r2;
 pp vectP = make_pair(p1.x - p2.x, p1.y - p2.y);
 double d = sqrt(vsize2(vectP));
 int ans;
 if (d == 0 && r1 == r2) {
   ans = -1;
 } else if (d == r1 + r2 || d + r1 == r2 || d + r2 == r1) {
   ans = 1;
 } else if (d > r1 + r2 || d + r1 < r2 || d + r2 < r1) {
   ans = 0;
 } else {
   ans = 2;
 }
 cout << ans << '\n';
}