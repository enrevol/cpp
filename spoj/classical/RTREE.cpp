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

std::vector<int> ed[N];

int dp[N], ans[N];

void dfs(int u, int p) {
  int a = 0, b = -1;
  for (int i = 0; i < int(ed[u].size()); ++i) {
    int v = ed[u][i];
    if (v == p) continue;
    dfs(v, u);
    int x = dp[v] + 1;
    if (x > dp[u]) dp[u] = x;
    if (ans[v] > ans[u]) ans[u] = ans[v];
    int arr[3] = { a, b, x };
    std::sort(arr, arr + 3, std::greater<int>());
    a = arr[0];
    b = arr[1];
  }
  if (b >= 0) {
    int x = a + b;
    if (x > ans[u]) ans[u] = x;
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d %d", &u, &v);
    ed[u].push_back(v);
    ed[v].push_back(u);
  }
  int root;
  scanf("%d", &root);
  dfs(root, 0);
  int q;
  scanf("%d", &q);
  while (q--) {
    int s;
    scanf("%d", &s);
    printf("%d\n", ans[s]);
  }
}