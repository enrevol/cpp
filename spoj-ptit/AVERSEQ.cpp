#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <sstream>
#include <string>
#include <vector>
 
std::pair<long long, int> b[1010101];
std::priority_queue<int> que;
int a[1010101];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  int n, k;
  scanf("%d %d", &n, &k);  
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    a[i] -= k;
  }
  for (int i = 1; i <= n; ++i) {    
    b[i].first = b[i - 1].first + a[i];
    b[i].second = i;
  }
  std::sort(b, b + n + 1);
  int it = n - 1, ans = 0;
  while (it >= 0) {
    que.push(b[it + 1].second);
    int idx = que.top();
    if (idx > b[it].second && idx - b[it].second > ans)
      ans = idx - b[it].second;
    --it;
  }
  printf("%d", ans);
} 