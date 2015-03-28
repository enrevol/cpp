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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }

using namespace std;

const int N = 1010;

bool blossom[N];
int n, pred[N], dsu[N], match[N], q[N];
vector<int> ed[N];

int lca(int u, int v) {
  static bool mark[N];
  memset(mark, 0, sizeof(mark));
  for (;;) {
    u = dsu[u];
    mark[u] = 1;
    if (match[u] == -1) break;
    u = pred[match[u]];
  }
  for (;;) {
    v = dsu[v];
    if (mark[v]) return v;
    v = pred[match[v]];
  }
  return -1;
}

void mark(int u, int b, int child) {
  while (dsu[u] != b) {
    blossom[dsu[u]] = blossom[dsu[match[u]]] = 1;
    pred[u] = child;
    child = match[u];
    u = pred[child];
  }
}

int find(int root) {
  static bool used[N];
  memset(used, 0, sizeof(used));
  memset(pred, -1, sizeof(pred));
  for (int i = 0; i < n; ++i) dsu[i] = i;
  int tail = 0;
  q[tail++] = root;
  used[root] = 1;
  for (int head = 0; head < tail; ++head) {
    int u = q[head];
    for (int i = 0; i < ed[u].size(); ++i) {
      int v = ed[u][i];
      if (dsu[u] == dsu[v] || match[v] == u) continue;
      if (v == root || (match[v] != -1 && pred[match[v]] != -1)) {
        int x = lca(u, v);
        memset(blossom, 0, sizeof(blossom));
        mark(u, x, v);
        mark(v, x, u);
        for (int j = 0; j < n; ++j)
          if (blossom[dsu[j]]) {
            dsu[j] = x;
            if (!used[j]) {
              used[j] = 1;
              q[tail++] = j;
            }
          }
      } else if (pred[v] == -1) {
        pred[v] = u;
        if (match[v] == -1)
          return v;
        v = match[v];
        used[v] = 1;
        q[tail++] = v;
      }
    }
  }
  return -1;
}

int edmonds() {
  memset(match, -1, sizeof(match));
  for (int i = 0; i < n; ++i)
    if (match[i] == -1) {
      int u = find(i);
      while (u != -1) {
        int v = pred[u];
        int x = match[v];
        match[u] = v;
        match[v] = u;
        u = x;
      }
    }
  int r = 0;
  for (int i = 0; i < n; ++i)
    if (match[i] != -1)
      ++r;
  return r >> 1;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int m;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  int r = edmonds();
  cout << n - r;
}
