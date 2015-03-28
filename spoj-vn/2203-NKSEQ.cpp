#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
 
typedef std::pair<int, int> p2;
 
std::deque<p2> de;
int a[202020];
int s[202020];
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n;
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i)
    scanf("%d", a + i);
  for (int i = 1; i < n; ++i)
    a[i + n] = a[i];
  for (int i = 1; i < n << 1; ++i)
    s[i] = s[i - 1] + a[i];
  for (int i = 1; i < n; ++i) {
    while (de.size() && de.back().first > s[i])
      de.pop_back();
    de.push_back(p2(s[i], i));
  }
  int ans = 0;
  for (int i = 1; i <= n; ++i) {    
    while (de.size() && de.front().second < i)
      de.pop_front();
    while (de.size() && de.back().first > s[i + n - 1])
      de.pop_back();
    de.push_back(p2(s[i + n - 1], i + n - 1));
    ans += s[i - 1] < de.front().first;
  }
  printf("%d", ans);
} 