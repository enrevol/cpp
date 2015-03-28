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
 
typedef std::pair<long long, int> p2;
 
int a[5050505];
std::deque<p2> de;
 
int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output.txt", "w", stdout);
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int n, d;
  scanf("%d %d", &n, &d);
  int p, q, m;  
  scanf("%d %d %d", &p, &q, &m);
  p %= m;
  for (int i = 1; i <= n; ++i) {
    a[i] = a[i - 1] + p;
    if (a[i] >= m) a[i] -= m;
  }  
  long long t = 0;
  for (int i = 1; i <= n; ++i) {
    t += d;
    while (!de.empty() && de.back().first <= t + a[i])
      de.pop_back();
    de.push_back(p2(t + a[i], i));
  }
  long long ans = de.front().first;
  long long k = 0;
  for (int i = 1; i < n; ++i) {
    t += d;
    while (!de.empty() && de.back().first <= t + a[i])
      de.pop_back();
    if (!de.empty() && de.front().second == i)
      de.pop_front();
    de.push_back(p2(t + a[i], i));
    k += d;
    long long v = de.front().first - k;
    if (v < ans) ans = v;
  }
  printf("%lld", ans + q);
}