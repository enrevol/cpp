#include <algorithm>
#include <bitset>
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
const int MAX = 1000000;
const double INF = 1e15;
const double EPS = 1e-2;
 
inline bool equal(double x, double y) {
  return fabs(x - y) <= EPS;
}
 
inline bool less_than(double x, double y) {
  return x < y && !equal(x, y);
}
 
struct edge {
  int to, dist;
  edge(int to, int dist) : to(to), dist(dist) { }
};
 
long long vf, vt;
double ans;
 
bool mark[N];
int sub_sz[N];
std::vector<edge> ed[N];
 
struct node {
  node *left, *right;
  long long key, f, t;
  int pri;
  double val, max;
  node();
  inline void update();
} pool[N];
 
node* const NIL = pool;
node* next;
 
node::node() : left(NIL), right(NIL),
  key(0), f(INF), t(0), pri(rand() << 16 ^ rand()), val(-INF), max(-INF) { }
 
inline void node::update() {
  max = std::max(val, std::max(left->max, right->max));
  f = std::min(key, left->f);
  t = std::max(key, right->t);
}
 
inline node* left_rotate(node* x) {
  node* y = x->right;
  x->right = y->left;
  y->left = x;
  x->update();
  y->update();
  return y;
}
 
inline node* right_rotate(node* x) {
  node* y = x->left;
  x->left = y->right;
  y->right = x;
  x->update();
  y->update();
  return y;
}
 
node* insert(node* x, const long long key, const double val) {
  if (x == NIL) {
    x = ++next;
    x->left = x->right = NIL;
    x->key = x->f = x->t = key;
    x->val = x->max = val;
  } else {
    if (key == x->key) {
      if (val > x->val) {
        x->val = val;
      }
    } else if (key < x->key) {
      x->left = insert(x->left, key, val);
      if (x->left->pri > x->pri) x = right_rotate(x);
    } else {
      x->right = insert(x->right, key, val);
      if (x->right->pri > x->pri) x = left_rotate(x);    
    }
    x->update();
  }
  return x;
}
 
int query(node* x, const long long qf, const long long qt, const double w) {
  if (qt < x->f || x->t < qf || less_than(x->max, -w)) return 0;
  if (qf <= x->f && x->t <= qt) return !less_than(x->max, -w);
  int r = 0;
  if (qf <= x->key && x->key <= qt) r |= !less_than(x->val, -w);
  if (qf < x->key) r |= query(x->left, qf, qt, w);
  if (qt > x->key) r |= query(x->right, qf, qt, w);
  return r;
}
 
int dfs_size(int u, int p) {
  sub_sz[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    if (mark[v]) {
      std::swap(ed[u][i], ed[u].back());
      ed[u].pop_back();
      --i;
    } else {
      sub_sz[u] += dfs_size(v, u);
    }
  }
  return sub_sz[u];
}
 
int dfs_center(int u, int p, int anc_sz) {
  int total = anc_sz + sub_sz[u];
  if (anc_sz << 1 > total) return 0;
  int flag = 1;
  for (int i = 0; i < int(ed[u].size()) && flag; ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    flag = sub_sz[v] << 1 <= total;
  }
  if (flag) return u;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    int x = dfs_center(v, u, total - sub_sz[v]);
    if (x) return x;
  }
  return 0;
}
 
struct vertex {
  int depth;
  long long dist;
  vertex(int depth, long long dist) : depth(depth), dist(dist) { }
  bool operator<(const vertex& v) const {
    return dist < v.dist;
  }
};
 
void dfs_dist(std::vector<vertex>& vect, int u, int p, int depth, long long dist) {
  if (dist > vt) return;
  vect.push_back(vertex(depth, dist));
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p) continue;
    dfs_dist(vect, v, u, depth + 1, dist + ed[u][i].dist);
  }
}
 
std::vector<vertex> vert[N];

bool cmp(int i, int j) {
  return vert[i].size() < vert[j].size();
}

void solve(int root) {
  dfs_size(root, 0);
  int ct = dfs_center(root, 0, 0);  
  double c_min = MAX, c_max = 0;
  int sz = int(ed[ct].size());
  for (int i = 0; i < sz; ++i) {
    int v = ed[ct][i].to;
    vert[i].clear();
    dfs_dist(vert[i], v, ct, 1, ed[ct][i].dist);
    for (int j = 0; j < int(vert[i].size()); ++j) {
      double val = 1.0 * vert[i][j].dist / vert[i][j].depth;
      c_min = std::min(c_min, val);
      c_max = std::max(c_max, val);
    }
    std::sort(vert[i].begin(), vert[i].end());
  }
  double low = std::max(c_min, ans);
  double high = std::min(c_max, 1.0 * MAX);
  static int pos[N];
  for (int i = 0; i < sz; ++i) {
    pos[i] = i;
  }
  std::sort(pos, pos + sz, cmp);
  for (int loop = equal(low, high); less_than(low, high) || loop; loop = 0) {
    double mid = (low + high) * 0.5;
    node* root = pool;
    next = pool;
    int flag = 0;
    root = insert(root, 0, 0);
    for (int k = 0; k < sz && flag == 0; ++k) {
      int i = pos[k];
      for (int j = 0; j < int(vert[i].size()) && flag == 0; ++j) {
        long long dist = vert[i][j].dist;
        double w_dist = dist - vert[i][j].depth * mid;
        flag = query(root, vf - dist, vt - dist, w_dist);
      }
      if (flag == 0 && k < sz - 1) {
        for (int j = 0; j < int(vert[i].size()); ++j) {
          long long dist = vert[i][j].dist;
          double w_dist = dist - vert[i][j].depth * mid;
          root = insert(root, dist, w_dist);
        }
      }
    }
    if (flag == 1) {
      ans = mid;
      low = mid;
    } else {
      high = mid;
    }
  }
  mark[ct] = 1;
  for (int i = 0; i < sz; ++i) {
    int v = ed[ct][i].to;
    solve(v);
  }
}
 
inline int read() {
  register char c = 0;
  while (c < 33) c = getchar();
  int a = 0;
  while (c > 33) {
    a = (a << 3) + (a << 1) + c - '0';
    c = getchar();
  }
  return a;
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  int tt = read();
  while (tt--) {
    int n = read();
    for (int i = 1; i <= n; ++i) {
      ed[i].clear();
    }
    for (int i = 1; i < n; ++i) {
      int u = read();
      int v = read();
      int c = read();
      ed[u].push_back(edge(v, c));
      ed[v].push_back(edge(u, c));
    }
    scanf("%lld %lld", &vf, &vt);
    memset(mark + 1, 0, n);
    ans = 1;
    solve(1);
    printf("%.10lf\n", ans);
  }
}

