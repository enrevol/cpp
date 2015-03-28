#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define pp pair<double, double>
using namespace std;
struct ss {
  pp p;
  double angle;
};
double dotProduct(pp a, pp b) {
  return a.x * b.x + a.y * b.y;
}
double len(pp a) {
  return sqrt(a.x * a.x + a.y * a.y);
}
pp vect(pp a, pp b) {
  return mp(a.x - b.x, a.y - b.y);
}
int f1(const ss& a, const ss& b) {
  return a.angle > b.angle;
}
double ccw(pp a, pp b, pp c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}
double area(int m, ss p[1005]) {
  if (m < 3) return 0;
  p[0] = p[m];
  double res = 0;
  for (int i = 0; i < m; ++i) res += p[i].p.x * p[i + 1].p.y;
  for (int i = 0; i < m; ++i) res -= p[i].p.y * p[i + 1].p.x;
  return res / 2;
}
double solve(vector<ss> vss, vector<ss>& vs) {
  ss p[1005];
  int n = vss.size();
  for (int i = 1; i <= n; ++i) p[i].p = vss[i - 1].p;
  int pi = 1;
  for (int i = 2; i <= n; ++i)
    if (p[pi].p.y > p[i].p.y ||
       (p[pi].p.y == p[i].p.y &&
        p[pi].p.x > p[i].p.x)) pi = i;
  swap(p[1], p[pi]);
  for (int i = 2; i <= n; ++i) {
    pp vec = vect(p[1].p, p[i].p);
    double dot = dotProduct(vec, mp(1, 0));
    double sz1 = len(vec);
    double sz2 = len(mp(1, 0));
    p[i].angle = acos(dot / sz1 / sz2);
  }
  sort(p + 2, p + n + 1, f1);
  p[0] = p[n];
  int m = 1;
  for (int i = 2; i <= n; ++i) {
    while (ccw(p[m - 1].p, p[m].p, p[i].p) <= 0) {
      if (m > 1) m -= 1;
      else if (i == n) break;
      else i++;
    }
    m++;
    swap(p[m], p[i]);
  }
  vs.clear();
  for (int i = m + 1; i <= n; ++i) vs.pb(p[i]);
  return area(m, p);
}
int main() {
  string s;
  int n;
  while (cin >> s >> n) {
    if (s == "ZZ" && n == 0) break;    
    ss t;
    vector<ss> vss;
    for (int i = 0; i < n; ++i) {
      cin >> t.p.x >> t.p.y;
      vss.pb(t);
    }    
    double res1 = solve(vss, vss);
    double res2 = solve(vss, vss);
    cout << "ProblemID " << s << ": " << fixed << setprecision(4) << res1 - res2 << '\n';
  }
  return 0;
}