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

const int N = 100010;
const int SQ = 450;

int a[N], b[N << 1], c[N], cnt[N], tin[N], tout[N];
vector<int> ed[N];
pair<int, int> p[N];

bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
  if (a.first / SQ != b.first / SQ)
    return a.first < b.first;
  return a.second < b.second;
}

void dfs(int u, int& t) {  
  tin[u] = ++t;
  b[tin[u]] = u;
  for (int i = 0; i < ed[u].size(); ++i) {
    dfs(ed[u][i], t);
  }
  tout[u] = ++t;
  p[u] = make_pair(tin[u], tout[u]);
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n, m, k;
  cin >> n >> m >> k;
  for (int i = 2; i <= n; ++i) {
    int p;
    cin >> p;
    ed[p].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  int tm = 0;
  dfs(1, tm);
  sort(p + 1, p + n + 1, cmp);
  cnt[0] = -1e9;
  int f = 1, t = 0, r = 0;
  for (int i = 1; i <= n; ++i) {
    int qf = p[i].first;
    int qt = p[i].second;
    while (t < qt) {      
      ++t;
      int x = a[b[t]];
      r += cnt[x] == 0;
      r -= cnt[x] == k;
      ++cnt[x];
    }
    while (t > qt) {
      int x = a[b[t]];    
      --cnt[x];
      r -= cnt[x] == 0;
      r += cnt[x] == k;
      --t;
    }
    while (f < qf) {
      int x = a[b[f]];
      --cnt[x];
      r -= cnt[x] == 0;
      r += cnt[x] == k;
      ++f;
    }
    while (f > qf) {      
      --f;
      int x = a[b[f]];
      r += cnt[x] == 0;
      r -= cnt[x] == k;
      ++cnt[x];
    }
    int v = b[p[i].first];
    c[v] = r;
//    cerr << "v = " << v << "  r = " << r << "  [" << f << "," << t << "]" << '\n';
//    cerr << "  " << cnt[1] << ' ' << cnt[2] << ' ' << cnt[3] << ' ' << cnt[4] << '\n';
  }
  int q;
  cin >> q;
  while (q--) {
    int u;
    cin >> u;
    cout << c[u] << '\n';
  }
}
