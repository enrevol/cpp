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

#include <ext/hash_set>
 
#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }
 
using namespace std;
 
const int N = 110;
 
string s, t;
int cnt, avail = 1, dp[N][N], child[500000][26];
vector<pair<int, int> > pos[N], next[N][N];
 
int count(int u) {
  int r = 0;
  for (int i = 0; i < 26; ++i) {
    if (child[u][i] > 0) {
      r += count(child[u][i]);
    }
  }
  if (r == 0) r = 1;
  return r;
}
 
char str[N];
 
void solve(int len, int u) {
  int f = 0;
  for (int i = 0; i < 26; ++i) {
    if (child[u][i] > 0) {
      str[len] = i + 'a';
      solve(len + 1, child[u][i]);
      f = 1;
    }
  }
  if (f == 0) {
    puts(str + 1);
  }
}
 
int counter;
 
__gnu_cxx::hash_set<int> vis[N][N];
 
void insert(int x, int y, int last) {
//  cerr << len << ' ' << x << ' ' << y << ' ' << last << '\n';  
  if (vis[x][y].count(last)) return;
  vis[x][y].insert(last);
//  cerr << ++counter << '\n';
  int c = s[x - 1] - 'a';
  if (child[last][c] == 0) {
    child[last][c] = ++avail;
  }
//  if (len == 1) return;
  for (int i = 0; i < next[x][y].size(); ++i) {
    int xx = next[x][y][i].first;
    int yy = next[x][y][i].second;
    insert(xx, yy, child[last][c]);
  }
}
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  cin >> s >> t;
  int sn = s.size();
  int tn = t.size();
  for (int i = 1; i <= sn; ++i)
    for (int j = 1; j <= tn; ++j) {
      if (s[i - 1] == t[j - 1]) {
        int len = dp[i - 1][j - 1] + 1;
        dp[i][j] = len;
        pos[len].push_back(make_pair(i, j));
      } else {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }    
  int ans = 0;
  int len = dp[sn][tn];
  if (len > 0) {
    for (int i = 1; i <= len; ++i) {
      sort(pos[i].begin(), pos[i].end());
      cerr << "i = " << i << " pos = " << pos[i].size() << '\n';
    }
    int total = 0;
    for (int l = len; l > 1; --l)
      for (int i = 0; i < pos[l].size(); ++i) {
        int x = pos[l][i].first;
        int y = pos[l][i].second;
        if (l < len && next[x][y].empty()) continue;
        total += next[x][y].size();
        for (int j = 0; j < pos[l - 1].size(); ++j) {
          int xx = pos[l - 1][j].first;
          int yy = pos[l - 1][j].second;
          if (xx >= x) break;
          if (xx < x && yy < y) {
            next[xx][yy].push_back(make_pair(x, y));
          }
        }
      }
    cerr << "total = " << total << '\n';
    for (int i = 0; i < pos[1].size(); ++i) {
      int x = pos[1][i].first;
      int y = pos[1][i].second;
      if (len > 1 && next[x][y].empty()) continue;
      insert(x, y, 1);
    }
    ans = count(1);
  }
  cerr << "len = " << len << '\n';
  cerr << "cnt = " << ans << '\n';
  cerr << "avail = " << avail << '\n';
  cout << ans << '\n';
  if (ans > 0) solve(1, 1);
} 
