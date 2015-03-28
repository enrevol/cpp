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

const unsigned long long INF = 1ULL << 60;

int lucky(int x) {
  static char s[20];
  sprintf(s, "%d", x);
  for (int i = 0; s[i]; ++i)
    if (s[i] != '4' && s[i] != '7')
      return 0;
  return 1;
}

int sz;
int number[10];
unsigned long long dp[10][500][500];

bool vis[10][500][500];

unsigned long long calc(int id, int c4, int c7) {
  int c = c4 + c7;
  assert(number[id] >= c);
  unsigned long long& r = dp[id][c4][c7];
  if (vis[id][c4][c7]) return r;
  vis[id][c4][c7] = 1;
  if (c == number[id]) return r = lucky(c4) || lucky(c7);
  int add = std::min(number[id] - c, 2);
  r = 0;  
  r += calc(id, c4 + add, c7);
  r += calc(id, c4, c7 + add);
  if (r > INF) r = INF;
  return r;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  for (int i = 1; i <= 444; ++i)
    if (lucky(i)) {
      ++sz;
      number[sz] = i;
      calc(sz, 0, 0);
      fprintf(stderr, "%d %llu\n", i, dp[sz][0][0]);
    }
  fprintf(stderr, "sz = %d\n", sz);
  int tt;
  scanf("%d", &tt);  
  for (int tn = 1; tt--; ++tn) {
    unsigned long long k;
    scanf("%llu", &k);
    char ans[555];
    for (int i = 1; i <= sz; ++i) {
      if (k > dp[i][0][0]) {
        k -= dp[i][0][0];
      } else {
        int c4 = 0, c7 = 0;
        int x = number[i];
        for (int j = 1; c4 + c7 < x; ++j) {
          int add = std::min(x - c4 - c7, 2);
          unsigned long long val = dp[i][c4 + add][c7];
          if (k <= val) {
            c4 += add;
            ans[j] = ans[x - j + 1] = '4';
          } else {
            k -= val;
            c7 += add;
            ans[j] = ans[x - j + 1] = '7';
          }
        }
        assert(k == 1);
        ans[x + 1] = 0;
//        for (int j = 1; j <= x; ++j)
//          assert(ans[j] == ans[x - j + 1]);
        break;
      }
    }
    printf("Query #%d: %s\n", tn, ans + 1);
  }
  putchar('\n');
}