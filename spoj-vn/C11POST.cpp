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

typedef std::pair<unsigned char, unsigned char> p2;

const int N = 110;
const int INF = 1e9;

const int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
const int dy[] = { 1, 1, 0, -1, -1, -1, 0, 1 };

int n, m, px, py, need;

char s[N][N];
int a[N][N], v[N * N];

bool bfs(int low, int high) {
  static p2 q[N * N];
  static bool vis[N][N];
  int sz = 0, have = 0;
  q[++sz] = p2(px, py);
  vis[px][py] = 1;
  for (int qi = 1; qi <= sz; ++qi) {    
    int x = q[qi].first;
    int y = q[qi].second;
    for (int d = 0; d < 8; ++d) {
      int nx = x + dx[d];
      int ny = y + dy[d];      
      if (1 <= nx && nx <= n && 1 <= ny && ny <= m)
        if (!vis[nx][ny] && low <= a[nx][ny] && a[nx][ny] <= high) {
          have += s[nx][ny] == 'K';
          if (have == need) {
            memset(vis, 0, sizeof(vis));
            return 1;
          }
          vis[nx][ny] = 1;
          q[++sz] = p2(nx, ny);
        }
    }
  }
  memset(vis, 0, sizeof(vis));
  return have == need;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s[i] + 1);
    for (int j = 1; j <= m; ++j)
      if (s[i][j] == 'P') {
        px = i;
        py = j;
      } else if (s[i][j] == 'K') {
        ++need;
      }
  }
  int v_max = 0, v_min = INF;
  int vn = 0;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      scanf("%d", a[i] + j);
      v[++vn] = a[i][j];
      if (s[i][j] == 'K') {
        if (a[i][j] > v_max) v_max = a[i][j];
        if (a[i][j] < v_min) v_min = a[i][j];
      }
    }
  std::sort(v + 1, v + vn + 1);
  vn = std::unique(v + 1, v + vn + 1) - v - 1;
  fprintf(stderr, "px = %d py = %d\n", px, py);
  int p_val = a[px][py];
  int p_pos = std::lower_bound(v + 1, v + vn + 1, p_val) - v;
  int ans = -1;
  int low = std::max(v_max, p_val) - std:: min(v_min, p_val);
  int high = v[vn] - v[1];
  while (low <= high) {
    int mid = (low + high) >> 1;
    int flag = 0;
    int left_val = p_val - mid;
    int left_pos = std::lower_bound(v + 1, v + vn + 1, left_val) - v;
    int right_val = p_val + mid;
    int right_pos = std::upper_bound(v + 1, v + vn + 1, right_val) - v - 1;
    int right = left_pos;
    int last = right - 1;
    for (int i = left_pos; i <= p_pos && flag == 0; ++i) {
      int val = v[i] + mid;
      while (right + 1 <= right_pos && v[right + 1] <= val) ++right;
      if (last < right && v[i] <= v_min && v_max <= v[right]) {
        flag = bfs(v[i], v[right]);
      }
      last = right;
    }
    if (flag) {
      ans = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  printf("%d", ans);
}
