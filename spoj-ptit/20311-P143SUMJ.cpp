#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int N = 100010;
const long double EPS = 1e-10;
 
struct ld {
  long double val;
  ld() : val(0) { }
  ld(long double val) : val(val) { }
  bool operator==(const ld& x) const { return fabs(val - x.val) <= EPS * fabs(val); }
  bool operator!=(const ld& x) const { return !(*this == x); }
  bool operator<(const ld& x) const { return val < x.val && *this != x; }
  bool operator>(const ld& x) const { return val > x.val && *this != x; }
  bool operator<=(const ld& x) const { return val < x.val || *this == x; }
  bool operator>=(const ld& x) const { return val > x.val || *this == x; }
  ld operator-(const ld& x) const { return ld(val - x.val); }
  ld operator+(const ld& x) const { return ld(val + x.val); }
  ld operator*(const ld& x) const { return ld(val * x.val); }
  ld operator/(const ld& x) const { return ld(val / x.val); }
};
 
struct point {
  ld x, y;
  int id;
  // 0 left
  // 1 right
  int type;
  point() { }
  point(ld x, ld y, int id, int type) : x(x), y(y), id(id), type(type) { }
  bool operator<(const point& a) const {
    return x < a.x;
  }
} p[N << 1];
 
struct line {
  point left, right;
  line() { }
  line(const point& left, const point& right) : left(left), right(right) { }
  inline point get(ld x, int id) const {
    if (x == left.x) return point(left.x, left.y, id, 0);
    if (x == right.x) return point(right.x, right.y, id, 0);
    ld dx = right.x - left.x;
    ld dy = right.y - left.y;
    ld y = left.y + (x - left.x) * dy / dx;
    assert((x - left.x) / (y - left.y) == (x - right.x) / (y - right.y));    
    return point(x, y, id, 0);
  }
} s[N];
 
// ba * bc
inline ld ccw(const point& a, const point& b, const point& c) {
  return (a.x - b.x) * (c.y - b.y) - (a.y - b.y) * (c.x - b.x);
}
 
inline bool on(const point& a, const point& b, const point& c) {
  return std::min(a.x, c.x) <= b.x && b.x <= std::max(a.x, c.x) &&
         std::min(a.y, c.y) <= b.y && b.y <= std::max(a.y, c.y);
}
 
inline int orient(const point& p, const point& q, const point& r) {
  ld val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
  if (val == 0) return 0;
  return val > 0 ? 1 : 2;
}
 
inline bool intersect(const line& a, const line& b) {
  int o1 = orient(a.left, a.right, b.left);
  int o2 = orient(a.left, a.right, b.right);
  int o3 = orient(b.left, b.right, a.left);
  int o4 = orient(b.left, b.right, a.right);
  if (o1 != o2 && o3 != o4) return 1;
  if (o1 == 0 && on(a.left, b.left, a.right)) return 1;
  if (o2 == 0 && on(a.left, b.right, a.right)) return 1;
  if (o3 == 0 && on(b.left, a.left, b.right)) return 1;
  if (o4 == 0 && on(b.left, a.right, b.right)) return 1;
  return 0;
}
 
bool b[N], c[N];
 
struct ele {  
  point left;
  point right;
  int id;
  ele(const point& left, const point& right, int id) : left(left), right(right), id(id) { }
  bool operator<(const ele& x) const {    
    if (id == x.id) return 0;
    if (c[id]) { // already in set
      point p = s[id].get(x.left.x, 0);
      return p.y > x.left.y;
    } else {
      point p = s[x.id].get(left.x, 0);
      return left.y > p.y;
    }
  }
};
 
std::set<ele> set;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    int x1, y1, x2, y2;
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
    p[i] = point(x1, y1, i, 0);
    p[i + n] = point(x2, y2, i, 1);
    if (p[i + n] < p[i]) std::swap(p[i], p[i + n]);
    p[i].type = 0;
    p[i + n].type = 1;
    s[i] = line(p[i], p[i + n]);
  }
  int pn = n << 1;
  std::sort(p + 1, p + pn + 1);
  int ans = n + 1;
  for (int i = 1; i <= pn; ++i) {
    //fprintf(stderr, "i = %d\n", i);
    int id = p[i].id;
    if (b[id] == 1 && c[id] == 0) continue;
    if (p[i].type == 0) {
      int add = 1;
      std::set<ele>::iterator it;
      while (add && ((it = set.upper_bound(ele(s[id].left, p[0], 0))) != set.begin()) && intersect(s[(--it)->id], s[id])) {
        int pred = it->id;
        if (id < pred) {
          set.erase(ele(s[pred].get(s[id].left.x, pred), p[0], pred));
          c[pred] = 0;
          if (pred < ans) {
            std::fill(b + pred, b + ans, 1);
            ans = pred;
          }
        } else add = 0;
      }
      while (add && ((it = set.upper_bound(ele(s[id].left, p[0], 0))) != set.end()) && intersect(s[it->id], s[id])) {
        int succ = it->id;
        if (id < succ) {
          set.erase(ele(s[succ].get(s[id].left.x, succ), p[0], succ));
          c[succ] = 0;
          if (succ < ans) {
            std::fill(b + succ, b + ans, 1);
            ans = succ;
          }
        } else add = 0;
      }
      if (add) {
        if (s[id].left.x != s[id].right.x) {
          set.insert(ele(s[id].left, s[id].right, id));
          c[id] = 1;
        }
      } else if (id < ans) {
        std::fill(b + id, b + ans, 1);
        ans = id;
      }
    } else if (c[id]) {
      set.erase(ele(s[id].right, p[0], id));
      c[id] = 0;
    }
  }
  printf("%d", ans == n + 1 ? -1 : ans);
}