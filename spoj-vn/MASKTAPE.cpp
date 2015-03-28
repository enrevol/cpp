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
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };

struct rect {
  int x1, y1, x2, y2;
} r[N];

bool id[N << 2][N << 2];
int q[N * N * 4], vx[N << 1], vy[N << 1];
short nx, ny, sum[N << 2], sub[N << 2][N << 2];

void bfs(int fx, int fy) {
  id[fx][fy] = 0;
  int tail = 0;
  q[tail++] = (fx << 16) | fy;
  for (int head = 0; head < tail; ++head) {    
    int x = q[head] >> 16;
    int y = q[head] & 65535;
    for (int d = 0; d < 4; ++d) {
      int xx = x + dx[d];
      int yy = y + dy[d];
      if (1 <= xx && xx < nx)
        if (1 <= yy && yy < ny)
          if (id[xx][yy]) {
            id[xx][yy] = 0;
            q[tail++] = (xx << 16) | yy;
          }
    }
  }
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int w, h, n;
  cin >> w >> h >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> r[i].x1 >> r[i].y1 >> r[i].x2 >> r[i].y2;
    vx[++nx] = r[i].x1;
    vx[++nx] = r[i].x2;
    vy[++ny] = r[i].y1;
    vy[++ny] = r[i].y2;
  }
  vx[++nx] = 0;
  vx[++nx] = w;
  vy[++ny] = 0;
  vy[++ny] = h;
  sort(vx + 1, vx + nx + 1);
  sort(vy + 1, vy + ny + 1);
  cerr << nx << ' ' << ny << '\n';
  nx = unique(vx + 1, vx + nx + 1) - vx - 1;
  ny = unique(vy + 1, vy + ny + 1) - vy - 1;
  for (int i = 1; i <= n; ++i) {    
    int x1 = lower_bound(vx + 1, vx + nx + 1, r[i].x1) - vx;
    int x2 = lower_bound(vx + 1, vx + nx + 1, r[i].x2) - vx;
    int y1 = lower_bound(vy + 1, vy + ny + 1, r[i].y1) - vy;
    int y2 = lower_bound(vy + 1, vy + ny + 1, r[i].y2) - vy;
    ++sub[x1][y1];
    --sub[x1][y2];
    --sub[x2][y1];
    ++sub[x2][y2];
  }
  for (int x = 1; x < nx; ++x)
    for (int y = 1; y < ny; ++y) {
      sub[x][y] += sub[x][y - 1];
      sum[y] += sub[x][y];
      id[x][y] = sum[y] == 0;
    }
  int ans = 0;
  for (int x = 1; x < nx; ++x)
    for (int y = 1; y < ny; ++y)
      if (id[x][y]) {
        ++ans;
        bfs(x, y);
      }
  cout << ans;
}
