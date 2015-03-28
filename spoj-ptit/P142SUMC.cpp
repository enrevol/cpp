#include <algorithm>
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
 
/*
 * 1,2,3,4 : row
 * 5,6,7,8 : col
 * 9,10    : 2
 * 11,12   : 3
 * 13,14   : 4
 * 15,16   : 5
 * 17,18   : 6
 * 19,20   : 7
 * 21,22   : 8
 * 23,24   : 9
 * Total: (2 ^ 24) states
 */
 
const int dx[] = { 0, -1, 0, 1 };
const int dy[] = { 1, 0, -1, 0 };
const int dr[] = { 2, 3, 0, 1 }; // reverse direction
 
unsigned char dp[1 << 24];
char s[17][17];
int q[1 << 24]; // queue
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  int fx = -1, fy = -1;
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
    for (int j = 0; j < m; ++j)
      if (s[i][j] == '1')
        fx = i, fy = j;
  }
  assert(fx >= 0 && fy >= 0);
  int fstate = fx | (fy << 4);
  int ssz = 1; // snake size
  for (int f = 1, v = 2; f; ++v) {
    f = 0;
    for (int i = 0; i < 4 && !f; ++i) {
      int xx = fx + dx[i];
      int yy = fy + dy[i];
      if (0 <= xx && xx < n)
        if (0 <= yy && yy < m)
          if (s[xx][yy] == v + '0') {
            f = 1;
            fstate |= i << ((v << 1) + 4);
            fx = xx;
            fy = yy;
            ssz = v;
            //fprintf(stderr, "%d -> %d %d\n", ssz, fx, fy);
          }
    }
  }
  //fprintf(stderr, "ssz = %d\n", ssz);
  int sz = 0;
  q[sz++] = fstate;
  dp[fstate] = 1;
  for (int i = 0; i < sz; ++i) {
    int state = q[i];
    int x = state & 15;
    int y = (state >> 4) & 15;
    //fprintf(stderr, "state = %d x = %d y = %d\n", state, x, y);
    bool mat[17][17] = { 0 };
    for (int j = 2, xx = x, yy = y, tmp = state >> 8; j < ssz; ++j, tmp >>= 2) {      
      int d = tmp & 3;
      //fprintf(stderr, "xx = %d yy = %d d = %d\n", xx, yy, d);
      xx += dx[d];
      yy += dy[d];
      //fprintf(stderr, "-> xx = %d yy = %d\n", xx, yy);
      mat[xx][yy] = 1;
    }
    unsigned char step = dp[state];        
    for (int j = 0; j < 4; ++j) {
      int xx = x + dx[j];
      int yy = y + dy[j];
      if (0 <= xx && xx < n)
        if (0 <= yy && yy < m)
          if (!mat[xx][yy] && s[xx][yy] != '#') {
            if (s[xx][yy] == '@') {
              printf("%u", step);
              return 0;
            }
            int nstate = (dr[j] << 8) | xx | (yy << 4) | ((state >> 8) << 10);
            nstate &= (1 << 24) - 1;
            if (dp[nstate] == 0) {
              dp[nstate] = step + 1;
              q[sz++] = nstate;
            }            
          }
    }
  }
  puts("-1");
}