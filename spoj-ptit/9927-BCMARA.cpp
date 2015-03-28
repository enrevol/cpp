#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
 
struct ss {
  int x, y, z;
} a[5050];
 
bool ff(const ss& lhs, const ss& rhs) {
  if (lhs.x == rhs.x) {
    if (lhs.y == rhs.y) return lhs.z < rhs.z;
    return lhs.y < rhs.y;
  }
  return lhs.x < rhs.x;
}
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d %d %d", &a[i].x, &a[i].y, &a[i].z);
  std::sort(a + 1, a + n + 1, ff);
  for (int i = 1; i <= n; ++i)
    printf("%d %d %d\n", a[i].x, a[i].y, a[i].z);
} 