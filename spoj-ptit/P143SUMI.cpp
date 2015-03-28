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
 
const int N = 300010;
 
struct ele {
  int weight;
  int value;
  bool operator<(const ele& x) const {
    return weight < x.weight;
  }
} a[N], tmp[N];
 
int b[N];
std::priority_queue<int> q;
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 1; i <= n; ++i) scanf("%d %d", &a[i].weight, &a[i].value);
  for (int i = 1; i <= k; ++i) scanf("%d", b + i);
  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + k + 1);
  long long ans = 0;
  for (int i = 1, j = 1; i <= k; ++i) {
    while (j <= n && a[j].weight <= b[i]) {
      q.push(a[j].value);
      ++j;
    }
    if (q.size()) {
      ans += q.top();
      q.pop();
    }
  }
  printf("%lld", ans);
}