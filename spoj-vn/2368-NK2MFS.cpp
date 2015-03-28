#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
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
 
struct ele {
  int a, b;
  int i;
  ele(int a, int b, int i) : a(a), b(b), i(i) { }
};
 
int a[10101];
int b[10101];
 
bool ff1(const ele& a, const ele& b) {
  return a.a < b.a;
}
 
bool ff2(const ele& a, const ele& b) {
  return a.b > b.b;
}
 
std::vector<ele> v1;
std::vector<ele> v2;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  for (int i = 1; i <= n; ++i)
    scanf("%d", b + i);
  for (int i = 1; i <= n; ++i)
    if (a[i] < b[i]) {
      v1.push_back(ele(a[i], b[i], i));
    } else {
      v2.push_back(ele(a[i], b[i], i));
    }
  std::sort(v1.begin(), v1.end(), ff1);
  std::sort(v2.begin(), v2.end(), ff2);
  for (size_t i = 0; i < v2.size(); ++i)
    v1.push_back(v2[i]);
  long long xa = 0;
  long long xb = 0;
  for (int i = 0; i < n; ++i) {
    xa += v1[i].a;
    xb = std::max(xb, xa) + v1[i].b;
  }
  printf("%lld\n", std::max(xb, xb));
  for (int i = 0; i < n; ++i)
    printf("%d ", v1[i].i);
}