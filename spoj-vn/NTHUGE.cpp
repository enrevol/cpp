#include <algorithm>
#include <bitset>
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

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  int n;
  long long l, r;
  std::cin >> n >> l >> r;
  const int N = 32;
  long long w[N], v[N];
  for (int i = 0; i < n; ++i)
    std::cin >> w[i] >> v[i];
  int lh = n >> 1;
  int rh = n - lh;
  static std::pair<long long, long long> larr[1 << (N >> 1)], rarr[1 << (N >> 1)];
  for (int mask = 0; mask < 1 << lh; ++mask) {
    long long tw = 0;
    long long tv = 0;
    for (int i = 0; i < lh; ++i)
      if ((mask >> i) & 1) {
        tw += w[i];
        tv += v[i];
      }
    larr[mask] = std::make_pair(tw, tv);
  }
  for (int mask = 0; mask < 1 << rh; ++mask) {
    long long tw = 0;
    long long tv = 0;
    for (int i = 0; i < rh; ++i)
      if ((mask >> i) & 1) {
        tw += w[i + lh];
        tv += v[i + lh];
      }
    rarr[mask] = std::make_pair(tw, tv);
  }
  std::sort(larr, larr + (1 << lh));
  std::sort(rarr, rarr + (1 << rh));
  long long ans = 0;
  static std::deque<int> deq;
  int left = 1 << rh, right = left - 1;
  for (int i = 0; i < 1 << lh; ++i) {
    while (left - 1 >= 0 && rarr[left - 1].first + larr[i].first >= l) {
      --left;
      while (!deq.empty() && rarr[deq.back()].second < rarr[left].second)
        deq.pop_back();
      deq.push_back(left);
    }
    while (rarr[right].first + larr[i].first > r) {      
      --right;
      while (!deq.empty() && deq.front() > right)
        deq.pop_front();
    }
    if (!deq.empty()) {
      long long val = larr[i].second + rarr[deq.front()].second;
      if (val > ans) ans = val;
    }    
  }
  std::cout << ans;
}
