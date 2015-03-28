#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
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
 
typedef long double ld;
typedef long long ll;
 
const ld eps = 1e-13;
 
inline ld abs(const ld& a) { return a >= 0 ? a : -a; }
inline bool eq(const ld& a, const ld& b) { return abs(a - b) <= eps * abs(a); }
inline bool le(const ld& a, const ld& b) { return !eq(a, b) && a < b; }
inline bool gr(const ld& a, const ld& b) { return !eq(a, b) && a > b; }
 
ll gcd(ll a, ll b) {
  while (b) {
    a %= b;
    std::swap(a, b);
  }
  return a;
}
 
struct pts {
  ld x, y;
  pts() { }  
  pts(const ld& x, const ld& y) : x(x), y(y) { }
  bool operator< (const pts& a) const {
    if (eq(x, a.x)) return le(y, a.y);
    return le(x, a.x);
  }
  bool operator== (const pts& a) const {
    return !(*this < a) && !(a < *this);
  }
} p[2525];
 
struct line {
  pts u, v;
  ll a, b, c;
  ll xl, xr;
  ll yl, yr;
  line() { }
  line(const pts& u, const pts& v) : u(u), v(v) {
    xl = std::min(u.x, v.x), xr = std::max(u.x, v.x);
    yl = std::min(u.y, v.y), yr = std::max(u.y, v.y);
    a = ll(v.y) - ll(u.y);
    b = ll(u.x) - ll(v.x);
    ll g = gcd(a, b);
    a /= g;
    b /= g;
    c = a * ll(u.x) + b * ll(u.y);
  }
  bool intersect(const line& l, pts& res) const {
    ll d = a * l.b - b * l.a;
    if (d == 0) return false;    
    ld px = ld(c * l.b - b * l.c) / d;
    ld py = ld(a * l.c - c * l.a) / d;
    if (!on(pts(px, py))) return false;
    if (!l.on(pts(px, py))) return false;
    res.x = px;
    res.y = py;
    return true;
  }
  bool on(const pts& p) const {
    if (le(p.x, xl) || gr(p.x, xr)) return false;
    if (le(p.y, yl) || gr(p.y, yr)) return false;
    return eq(p.x * a + p.y * b, c);
  }
} e[55];
 
typedef std::pair<bool, int> p2;
 
std::vector<p2> pv[2525];
std::vector<int> ev[55];
 
int arr[2525];
 
ld ox, oy;
 
inline int part(const ld& x, const ld& y) {
  if (gr(x, 0) && !le(y, 0)) return 1;
  if (!gr(x, 0) && gr(y, 0)) return 2;
  if (le(x, 0) && !gr(y, 0)) return 3;
  return 4;
}
 
bool ef(int a, int b) { return p[a] < p[b]; }
 
bool pf(const p2& a, const p2& b) {
  int ai = a.second;
  int bi = b.second;
  ld ax = p[ai].x - ox, ay = p[ai].y - oy;
  ld bx = p[bi].x - ox, by = p[bi].y - oy;
  int ap = part(ax, ay);
  int bp = part(bx, by);
  if (ap == bp) return le(ay * bx, ax * by);
  return ap < bp;
}
 
ll cnt;
 
void dfs(int u, int t, int k) {
  if (u == arr[1]) {
    if (k & 1) {
      ++cnt;
    } else {
      bool f = true;
      int l = 2;
      int r = k;
      while (l < r && f) f = arr[l++] == arr[r--];
      if (!f) ++cnt;
    }
  } else {
    arr[++k] = u;
    int x = -1;
    for (size_t i = 0; i < pv[u].size() && x == -1; ++i)
      if (pv[u][i].second == t) x = i;
    int y = x + 1 < int(pv[u].size()) ? x + 1 : 0;
    pv[u][y].first = false;
    dfs(pv[u][y].second, u, k);
  }
}
 
std::set<pts> st;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  ll tt;
  std::cin >> tt;
  //scanf("%d", &tt);
  while (tt--) {
    ll n, m, k;
    std::cin >> n >> m >> k;
    //scanf("%d %d %d", &n, &m, &k);    
    ll ans = 1;
    while (k--) {
      ll r;
      std::cin >> r;
      //scanf("%d", &r);
      for (int i = 1; i <= r; ++i)
        std::cin >> p[i].x >> p[i].y;
        //scanf("%lf %lf", &p[i].x, &p[i].y);
      r = std::unique(p + 1, p + r + 1) - p - 1;
      int en = r - 1;
      for (int i = 1; i <= en; ++i)
        e[i] = line(p[i], p[i + 1]);
      std::sort(p + 1, p + r + 1);
      r = std::unique(p + 1, p + r + 1) - p - 1;
      st.clear();
      int pn = r;
      for (int i = 1; i <= pn; ++i)
        st.insert(p[i]);
      for (int i = 1; i <= en; ++i) {
        ev[i].clear();
        for (int j = 1; j < i; ++j)
          if (e[i].intersect(e[j], p[pn + 1]))
            if (!st.count(p[pn + 1])) {
              st.insert(p[pn + 1]);
              ++pn;
            }
      }
      for (int i = 1; i <= en; ++i)
        for (int j = 1; j <= pn; ++j)
          if (e[i].on(p[j])) ev[i].push_back(j);
      for (int i = 1; i <= pn; ++i)
        pv[i].clear();
      for (int i = 1; i <= en; ++i) {
        std::sort(ev[i].begin(), ev[i].end(), ef);
        ev[i].resize(std::unique(ev[i].begin(), ev[i].end()) - ev[i].begin());
        for (size_t j = 0; j + 1 < ev[i].size(); ++j) {
          pv[ev[i][j]].push_back(p2(true, ev[i][j + 1]));
          pv[ev[i][j + 1]].push_back(p2(true, ev[i][j]));
        }
      }
      for (int i = 1; i <= pn; ++i) {
        ox = p[i].x;
        oy = p[i].y;
        std::sort(pv[i].begin(), pv[i].end());
        pv[i].resize(std::unique(pv[i].begin(), pv[i].end()) - pv[i].begin());
        std::sort(pv[i].begin(), pv[i].end(), pf);
      }
      cnt = 0;
      for (int i = 1; i <= pn; ++i)
        for (size_t j = 0; j < pv[i].size(); ++j)
          if (pv[i][j].first) {
            arr[1] = i;
            pv[i][j].first = false;
            dfs(pv[i][j].second, i, 1);
          }
      if (cnt > 0) --cnt;
      ans += cnt;
    }    
    std::cout << ans << '\n';
    //printf("%d\n", ans);
  }
} 