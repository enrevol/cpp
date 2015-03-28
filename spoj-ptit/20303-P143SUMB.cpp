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
 
const int N = 1010;
 
int a[N];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, m;
  scanf("%d %d", &n, &m);
  for (int i = 1; i <= m; ++i) scanf("%d", a + i);
  std::sort(a + 1, a + m + 1);
  int max = 0, min = 0;
  for (int i = 1, x = n; i <= m && x; ++i) {
    int k = std::min(x, a[i]);
    x -= k;
    min += (a[i] + (a[i] - k + 1)) * k / 2;
  }
  std::priority_queue<int> q;
  for (int i = 1; i <= m; ++i)  q.push(a[i]);
  while (n) {
    int k = q.top();
    q.pop();
    max += k;
    --k;
    if (k > 0) q.push(k);
    --n;
  }
  printf("%d %d", max, min);
}