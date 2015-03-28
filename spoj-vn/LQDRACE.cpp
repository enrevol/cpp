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

const int N = 200010;
const int MAX = 1000010;

struct edge {
  int to, dist;
  edge(int to, int dist) : to(to), dist(dist) { }
};

struct ele {
  int ed, dist;
  ele(int ed, int dist) : ed(ed), dist(dist) { }
};

std::vector<edge> ed[N];
bool mark[N];
int sub_sz[N];

void dfs_size(int u, int p) {
  sub_sz[u] = 1;
  for (int i = 0; i < int(ed[u].size()); ++i) {    
    int v = ed[u][i].to;
    if (v == p || mark[v]) continue;
    dfs_size(v, u);
    sub_sz[u] += sub_sz[v];
  }
}

int dfs_center(int u, int p, int anc_sz) {
  int total = anc_sz + sub_sz[u];
  if (anc_sz << 1 > total + 1) return 0;
  int flag = 1;
  for (int i = 0; i < int(ed[u].size()) && flag; ++i) {
    int v = ed[u][i].to;
    if (v == p || mark[v]) continue;
    flag = sub_sz[v] << 1 <= total + 1;
  }
  if (flag) return u;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p || mark[v]) continue;
    int x = dfs_center(v, u, total - sub_sz[v]);
    if (x > 0) return x;
  }
  return 0;
}

void dfs_dist(int u, int p, int depth, int dist, std::vector<ele>& vect, const int k) {
  if (dist > k) return;
  vect.push_back(ele(depth, dist));
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i].to;
    if (v == p || mark[v]) continue;
    dfs_dist(v, u, depth + 1, dist + ed[u][i].dist, vect, k);
  }
}

int solve(int root, const int k) {
  dfs_size(root, 0);
  int ct = dfs_center(root, 0, 0);
  assert(ct > 0);
  static std::vector<ele> vect[N];
  static int memo[MAX];
  int res = N;
  for (int i = 0; i < int(ed[ct].size()); ++i) {
    int v = ed[ct][i].to;
    if (mark[v]) continue;
    vect[i].clear();
    dfs_dist(v, ct, 1, ed[ct][i].dist, vect[i], k);
    for (int j = 0; j < int(vect[i].size()); ++j) {
      int z = k - vect[i][j].dist;
      assert(z >= 0);
      if (z == 0 || memo[z] > 0) {
        int total = vect[i][j].ed + memo[z];
        if (total < res) {
          res = total;
        }
      }
    }
    for (int j = 0; j < int(vect[i].size()); ++j) {
      int x = vect[i][j].dist;
      int y = vect[i][j].ed;
      if (memo[x] == 0 || memo[x] > y) {
        memo[x] = y;
      }
    }
  }
  for (int i = 0; i < int(ed[ct].size()); ++i) {
    for (int j = 0; j < int(vect[i].size()); ++j) {
      int x = vect[i][j].dist;
      memo[x] = 0;
    }
    vect[i].clear();
  }
  mark[ct] = 1;
  for (int i = 0; i < int(ed[ct].size()); ++i) {
    int v = ed[ct][i].to;
    if (mark[v]) continue;
    int x = solve(v, k);
    if (x < res) {
      res = x;
    }
  }
  return res;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i < n; ++i) {
    int u, v, c;
    scanf("%d %d %d", &u, &v, &c);
    ++u, ++v;
    ed[u].push_back(edge(v, c));
    ed[v].push_back(edge(u, c));
  }
  int ans = solve(1, k);
  if (ans == N) ans = -1;
  printf("%d", ans);
}
