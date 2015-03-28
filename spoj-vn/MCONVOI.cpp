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

const int MOD = 1e9 + 7;
const int N = 300010;

typedef std::pair<int, int> p2;

p2 p[N];
int v[N], best[N], ways[N];

std::vector<int> step[N], sum[N];

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d %d", &p[i].first, &p[i].second);
    v[i] = p[i].second;
  }
  std::sort(v + 1, v + n + 1);
  int vn = std::unique(v + 1, v + n + 1) - v - 1;
  for (int i = 1; i <= n; ++i) {
    p[i].second = std::lower_bound(v + 1, v + vn + 1, p[i].second) - v;
  }
  std::sort(p + 1, p + n + 1);
  int ans = 0;
  step[0].push_back(0);
  sum[0].push_back(0);
  sum[0].push_back(1);
  ways[0] = 1;
  for (int i = 1; i <= n; ) {
    int j = i;
    while (j + 1 <= n && p[j + 1].first == p[i].first)
      ++j;
//    printf("[%d..%d]\n", i, j);
    for (int k = j; k >= i; --k) {
//      printf("k = %d ", k);
      int x = p[k].second;
      int pos = 0;
      for (int low = 1, high = ans; low <= high; ) {
        int mid = (low + high) >> 1;
        int id = step[mid].back();
        if (p[id].second < x) {
          pos = mid;
          low = mid + 1;
        } else {
          high = mid - 1;
        }
      }
//      printf("pos = %d ", pos);
      best[k] = pos + 1;
      int sz = step[pos].size();
//      printf("sz = %d ", sz);
      int index = -1;
      for (int low = 0, high = sz - 1; low <= high; ) {
        int mid = (low + high) >> 1;
        int id = step[pos][mid];
        if (p[id].second < x) {
          index = mid;
          high = mid - 1;
        } else {
          low = mid + 1;
        }
      }
      ways[k] = (sum[pos][sz] - sum[pos][index]) % MOD;
//      printf("index = %d way = %d\n", index, ways[k]);
    }
    for (int k = j; k >= i; --k) {
      int v = best[k];
      step[v].push_back(k);
      if (v > ans) {
        ans = v;
        sum[v].push_back(0);
      }      
      sum[v].push_back((sum[v].back() + ways[k]) % MOD);
    }
    i = j + 1;
  }
//  for (int i = 1; i <= ans; ++i) {
//    printf("i = %d : ", i);
//    for (int j = 0; j < int(step[i].size()); ++j)
//      printf("%d ", step[i][j]);
//    putchar('\n');
//  }      
  printf("%d\n", ans);
  printf("%d\n", (sum[ans].back() + MOD) % MOD);
}
