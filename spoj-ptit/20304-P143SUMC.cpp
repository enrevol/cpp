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
 
const int N = 100010;
 
int a[N], sum[N];
char s[N];
 
int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", a + i);
    sum[i] = sum[i - 1] + a[i];
  }
  scanf("%s", s + 1);
  int ans = 0;
  int val = 0;
  for (int i = n; i; --i) {
    if (s[i] == '1') {
      ans = std::max(ans, sum[i - 1] + val);
      val += a[i];
    }
  }  
  printf("%d", std::max(ans, val));
}