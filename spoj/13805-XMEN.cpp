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
 
int a[101010], pos[101010], arr[101010];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      pos[a[i]] = i;
    }
    for (int i = 1; i <= n; ++i) {
      scanf("%d", a + i);
      a[i] = pos[a[i]];
    }
    int sz = 0;
    for (int i = 1; i <= n; ++i) {
      int it = std::upper_bound(arr + 1, arr + sz + 1, a[i]) - arr;
      if (it == sz + 1) {
        arr[++sz] = a[i];
      } else {
        arr[it] = a[i];
      }
    }
    printf("%d\n", sz);
  }
}
 