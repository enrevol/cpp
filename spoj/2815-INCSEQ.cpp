#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
const int mod = 5e6;
 
int fw[55][101010];
 
void update(int t, int i, int v) {
  ++i;
  while (i <= 100001) {
    fw[t][i] += v;
    if (fw[t][i] >= mod) fw[t][i] -= mod;
    i += i & -i;
  }
}
 
int query(int t, int i) {
  int res = 0;
  ++i;
  while (i) {
    res += fw[t][i];
    if (res >= mod) res -= mod;
    i -= i & -i;
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k, t;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &t);
    update(1, t, 1);
    for (int j = 1; j < k; ++j) {
      int cnt = query(j, t - 1);
      update(j + 1, t, cnt);
    }
  }
  printf("%d", query(k, 100000));
} 