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
const int INF = 1e9;

std::vector<int> ed[N], chain[N];
int c[N], vid[N], vps[N], top[N], sub_sz[N], heavy[N], depth[N], ancestor[17][N];

struct node {
  node *left, *right;
  int key, max, min;
  int lazy, sz, pri;
  node();
  void update();
} pool[N * 2];

node* const NIL = pool;
node* next = pool;
node* root[N];

node::node() : left(NIL), right(NIL), key(0), max(-INF), min(INF), lazy(0), sz(1), pri(rand() << 16 ^ rand()) { }

inline void node::update() {
  if (this != NIL) {
    sz = left->sz + right->sz + 1;
    min = std::min(key, std::min(left->min, right->min));
    max = std::max(key, std::max(left->max, right->max));
  }
}

inline void swap(node* x) {
  std::swap(x->left, x->right);
  x->lazy ^= 1;
}

inline void push(node* x) {
  if (x->lazy) {
    swap(x->left);
    swap(x->right);
    x->lazy = 0;
  }
}

void merge(node*& x, node* left, node* right) {
  push(left);
  push(right);
  if (left == NIL) {
    x = right;
  } else if (right == NIL) {
    x = left;
  } else if (left->pri > right->pri) {
    x = left;
    merge(x->right, left->right, right);
  } else {
    x = right;
    merge(x->left, left, right->left);
  }
  x->update();
}

void split(node* x, node*& left, node*& right, const int pos) {  
  if (x == NIL) {
    left = right = NIL;
  } else {
    push(x);
    if (x->left->sz >= pos) {
      right = x;
      split(x->left, left, right->left, pos);
      right->update();
    } else {
      left = x;
      split(x->right, left->right, right, pos - x->left->sz - 1);
      left->update();
    }
  }
}

int query_max(node* x, int f, int t, int qf, int qt) {
  if (f > t) return -INF;
  push(x);
  if (qf <= f && t <= qt) return x->max;
  int m = f + x->left->sz;
  int res = -INF;
  if (qf <= m && m <= qt) res = x->key;
  if (qf < m) res = std::max(res, query_max(x->left, f, m - 1, qf, qt));
  if (qt > m) res = std::max(res, query_max(x->right, m + 1, t, qf, qt));
  return res;
}
  
int query_min(node* x, int f, int t, int qf, int qt) {
  if (f > t) return INF;
  push(x);
  if (qf <= f && t <= qt) return x->min;
  int m = f + x->left->sz;
  int res = INF;
  if (qf <= m && m <= qt) res = x->key;
  if (qf < m) res = std::min(res, query_min(x->left, f, m - 1, qf, qt));
  if (qt > m) res = std::min(res, query_min(x->right, m + 1, t, qf, qt));
  return res;
}

inline int jump(int u, int v, int d) {
  assert(depth[u] >= depth[v] + d);
  for (int i = 16; i >= 0; --i)
    if (depth[u] - (1 << i) >= depth[v] + d)
      u = ancestor[i][u];
  assert(depth[u] == depth[v] + d);
  return u;
}

int lca(int u, int v) {
  if (depth[u] < depth[v]) std::swap(u, v);
  u = jump(u, v, 0);
  if (u == v) return u;
  for (int i = 16; i >= 0; --i)
    if (ancestor[i][u] != ancestor[i][v]) {
      u = ancestor[i][u];
      v = ancestor[i][v];
    }
  return ancestor[0][u];
}

void dfs_size(int u, int p) {
  sub_sz[u] = 1;
  depth[u] = depth[p] + 1;
  ancestor[0][u] = p;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    dfs_size(v, u);
    sub_sz[u] += sub_sz[v];
    if (sub_sz[heavy[u]] < sub_sz[v]) {
      heavy[u] = v;
    }
  }
}

int cnt;

void dfs_tree(int u, int p, int id, int pos) {
  chain[id].push_back(u);
  vid[u] = id;
  vps[u] = pos;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    if (v == heavy[u]) {
      dfs_tree(v, u, id, pos + 1);
    } else {
      ++cnt;
      dfs_tree(v, u, cnt, 1);
    }
  }
}

int query_max(int u, int v) {
  int res = -INF;
  for (;;) {
    int id = vid[u];
    if (id == vid[v]) {
      int val = query_max(root[id], 1, root[id]->sz, vps[v], vps[u]);
      res = std::max(res, val);
      break;
    }
    int val = query_max(root[id], 1, root[id]->sz, 1, vps[u]);
    res = std::max(res, val);
    u = top[u];
  }
  return res;
}

int query_min(int u, int v) {
  int res = INF;
  for (;;) {
    int id = vid[u];    
    if (id == vid[v]) {
      int val = query_min(root[id], 1, root[id]->sz, vps[v], vps[u]);
      res = std::min(res, val);
      break;
    }
    int val = query_min(root[id], 1, root[id]->sz, 1, vps[u]);
    res = std::min(res, val);
    u = top[u];
  }
  return res;
}

void update(int u, int v) {
  if (depth[u] < depth[v]) std::swap(u, v);
  int x = lca(u, v);
  int end_v = x;
  int end_u = jump(u, x, depth[u] - depth[v]);
  node *u1, *u2, *u3, *v1, *v2, *v3;
  while (u != end_u && v != end_v) {
    int top_u = top[u];
    int top_v = top[v];
    int next_u = depth[top_u] > depth[end_u] ? top_u : end_u;
    int next_v = depth[top_v] > depth[end_v] ? top_v : end_v;
    int sz_u = depth[u] - depth[next_u];
    int sz_v = depth[v] - depth[next_v];
    int sz = std::min(sz_u, sz_v);
    // [1..u-sz][u-sz+1..u][u+1..total]
    split(root[vid[u]], u2, u3, vps[u]);
    split(u2, u1, u2, vps[u] - sz);
    // [1..v-sz][v-sz+1..v][v+1..total]
    split(root[vid[v]], v2, v3, vps[v]);
    split(v2, v1, v2, vps[v] - sz);
    // u1 + v2 + u3
    merge(u1, u1, v2);
    merge(root[vid[u]], u1, u3);
    // v1 + u2 + v3
    merge(v1, v1, u2);
    merge(root[vid[v]], v1, v3);
    u = sz_u <= sz_v ? next_u : chain[vid[u]][vps[u] - sz - 1];
    v = sz_v <= sz_u ? next_v : chain[vid[v]][vps[v] - sz - 1];
  }
  assert(u == end_u && v == end_v);
  for (; depth[u] > depth[v];) {
    if (vid[u] == vid[v]) {
      //    u1     u2       u3
      // [1..v-1][v..u][u+1..total]
      split(root[vid[u]], u2, u3, vps[u]);
      split(u2, u1, u2, vps[v] - 1);
      swap(u2);
      // u1 + u2 + u3
      merge(u2, u1, u2);
      merge(root[vid[u]], u2, u3);
      break;
    }
    int k = top[u];
    while (vid[k] != vid[v]) k = top[k];
    int sz_u = vps[u];
    int sz_v = depth[k] - depth[v] + 1;
    int sz = std::min(sz_u, sz_v);
    assert(depth[u] - depth[v] >= sz);
    //     u1        u2         u3
    // [1..u-sz][u-sz+1..u][u+1..total]
    split(root[vid[u]], u2, u3, vps[u]);
    split(u2, u1, u2, vps[u] - sz);
    //     v1       v2         v3
    // [1..v-1][v..v+sz-1][v+sz..total]
    split(root[vid[v]], v2, v3, vps[v] + sz - 1);
    split(v2, v1, v2, vps[v] - 1);
    swap(u2);
    swap(v2);
    // u1 + v2 + u3
    merge(u1, u1, v2);         
    merge(root[vid[u]], u1, u3);
    // v1 + u2 + v3
    merge(v1, v1, u2);
    merge(root[vid[v]], v1, v3);      
    v = jump(u, v, sz);
    u = sz == sz_u ? top[u] : chain[vid[u]][vps[u] - sz - 1];
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  srand(time(NULL));
  NIL->sz = 0;
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) scanf("%d", c + i);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  cnt = 1;
  dfs_size(1, 0);
  dfs_tree(1, 0, cnt, 1);
  for (int j = 1; 1 << j <= n; ++j)
    for (int i = 1; i <= n; ++i)
      ancestor[j][i] = ancestor[j - 1][ancestor[j - 1][i]];
  for (int i = 1; i <= cnt; ++i) {
    root[i] = NIL;
    int u = ancestor[0][chain[i].front()];
    for (int j = 0; j < int(chain[i].size()); ++j) {
      int v = chain[i][j];
      top[v] = u;
      ++next;
      next->key = next->min = next->max = c[v];
      merge(root[i], root[i], next);
    }
  }
  while (m--) {
    int k, u, v;
    scanf("%d %d %d", &k, &u, &v);
    int x = lca(u, v);
    if (k == 1) {
      int res = std::min(query_min(u, x), query_min(v, x));
      printf("%d\n", res);
    } else if (k == 2) {
      int res = std::max(query_max(u, x), query_max(v, x));
      printf("%d\n", res);
    } else {
      update(u, v);
    }
  }
}
