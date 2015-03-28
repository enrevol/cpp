SPOJ submission 10856264 (C++ 4.3.2) plaintext list. Status: AC, problem RIDERHP, contest SPOJVN. By enrevol (What Does The Fox Say?), 2014-01-13 00:02:13.
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
#define m2 std::make_pair
#define m4(a, b, c, d) m2(m2(a, b), m2(c, d))
 
typedef std::pair<double, double> p2;
typedef std::pair<p2, p2> p4;
 
const double eps = 1e-8;
 
double abs(const double& a) {
  return a >= 0 ? a : -a;
}
 
double eq(const double& a, const double& b) {
  return abs(a - b) <= eps;
}
 
std::vector<p2> v;
std::vector<p4> points;
 
bool ff(const p4& lhs, const p4& rhs) {
  if (eq(lhs.first.first, rhs.first.first)) return 0;
  return lhs.first.first < rhs.first.first;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int m, n, t;
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    scanf("%d", &t);
    if (v.size() == 0 || v.back().first < t)
      v.push_back(m2(t, i));
  }
  points.push_back(m4(0, 1 << 30, 0, 0));
  points.push_back(m4(0, 0, 0, 0));
  for (int i = 0; i < v.size(); ++i) {
    int l = 1, r = points.size() - 1, pos = -1;
    while (l <= r) {
      int m = (l + r) >> 1;
      p4 p = points[m];
      double y = (v[i].first - p.first.first) / v[i].second;
      if (eq(y, p.first.second) || y > p.first.second) {    
        pos = m;
        r = m - 1;
      } else {
        l = m + 1;
      }
    }
    assert(pos != -1);
    if (pos >= 1) {
      double x = 0;
      double y = v[i].first / v[i].second;
      p2 p_t =  points[pos].second;
      if (pos > 1) {        
        x = (p_t.second * v[i].first - v[i].second * p_t.first) / (p_t.second - v[i].second);
        y = (p_t.first - x) / p_t.second;
      }
      p4 add_1 = m4(x, y, p_t.first, p_t.second);
      p4 add_2 = m4(v[i].first, 0, v[i].first, v[i].second);
      points.resize(pos);
      points.push_back(add_1);
      points.push_back(add_2);
    }
  }
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    int pos = std::upper_bound(points.begin(), points.end(), m4(t, 0, 0, 0), ff) - points.begin();
    p2 p_t = points[pos].second;
    double ans = (p_t.first - t) / p_t.second;
    printf("%.6lf\n", 1 / ans);
  }
} 