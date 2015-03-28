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

const int N = 310;

unsigned char dp[N][N][N][2];

int max(int x, int y) {
  return x > y ? x : y;
}

int solve(int x, int y, int z, int t) {
  unsigned char& r = dp[x][y][z][t];
  if (r != 0xFF) return r;
  r = 0;
  if (t == 0) {
    if (y == 0) {
      if (z > 0) {
        if (x >= 2) r = max(r, solve(x - 2, y + 2, z, 0));
        if (x >= 1) r = max(r, solve(x - 1, y + 1, z, 1));
      } else {
        r = max(r, solve(x - 1, y + 1, z, 0) + 1);
        r = max(r, solve(x - 1, y + 1, z, 1) + 1);
      }
    } else if (y == 1) {
      if (x >= 1) r = max(r, solve(x - 1, y + 1, z, 0));
      r = max(r, solve(x, y, z, 1));
    } else {
      if (y & 1) {
        if (x >= 1) {
          r = max(r, solve(x - 1, y + 1, z, 0));
          r = max(r, solve(x - 1, y + 1, z, 1) + 1);
        }
        if (y >= 3) r = max(r, solve(x, y - 1, z + 1, 0));
        if (x == 0) r = max(r, solve(x, y - 1, z + 1, 1) + 1);
      } else {
        if (x >= 1) {
          r = max(r, solve(x - 1, y + 1, z, 0) + 1);
          r = max(r, solve(x - 1, y + 1, z, 1));
        }
        if (x == 0) r = max(r, solve(x, y - 1, z + 1, 0) + 1);
        if (y >= 2) r = max(r, solve(x, y - 1, z + 1, 1));
      }
    }
  } else {
    if (y == 0) {
      if (z > 0) {
        if (x > 0) r = max(r, solve(x - 1, y + 1, z, 1));
      } else {
        r = max(r, solve(x, y, z, 0));
      }
    } else {
      if (y & 1) {
        if (x >= 1) r = max(r, solve(x - 1, y + 1, z, 1) + 1);
        if (x == 0) r = max(r, solve(x, y - 1, z + 1, 1) + 1);
      } else {
        if (x >= 1) r = max(r, solve(x - 1, y + 1, z, 1));
        if (y >= 2) r = max(r, solve(x, y - 1, z + 1, 1));
      }
    }
  }
//  printf("%d %d %d %d = %d\n", x, y, z, t, r);
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt" "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  memset(dp, -1, sizeof(dp));
  dp[0][0][0][0] = dp[0][0][0][1] = 0;
  int tt;
  scanf("%d", &tt);
  for (int tn = 1; tn <= tt; ++tn) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    printf("Scenario #%d: %d\n", tn, solve(x, y, z, 0));
  }
}