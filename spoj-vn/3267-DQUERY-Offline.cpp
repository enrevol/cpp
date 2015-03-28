#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::vector<int> event[30303];
int a[30303], ans[202020], fw[30303], last_pos[1010101], n, left[202020];
 
void update(int idx, const int& val) {
  while (idx >= 1) {
    fw[idx] += val;
    idx -= idx & -idx;
  }  
}
 
int query(int idx) {
  int res = 0;
  while (idx <= n) {
    res += fw[idx];
    idx += idx & -idx;
  }
  return res;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  int q;
  scanf("%d", &q);
  int t;
  for (int i = 1; i <= q; ++i) {
    scanf("%d %d", left + i, &t);
    event[t].push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    if (last_pos[a[i]])
      update(last_pos[a[i]], -1);
    last_pos[a[i]] = i;
    update(i, 1);
    for (int j = 0; j < event[i].size(); ++j)
      ans[event[i][j]] = query(left[event[i][j]]);
  }
  for (int i = 1; i <= q; ++i)
    printf("%d\n", ans[i]);
} 