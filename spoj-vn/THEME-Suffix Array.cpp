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

const int N = 5010;

int n, gap;
int a[N], b[N], sa[N], lcp[N], rank[N], tmp[N], bucket[N];


bool cmp(int i, int j) {
  if (rank[i] != rank[j]) return rank[i] < rank[j];
  i += gap;
  j += gap;
  if (i < n && j < n) return rank[i] < rank[j];
  return i > j;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cin >> n;
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  for (int i = 1; i < n; ++i) b[i] = a[i + 1] - a[i] + 100;
  for (int i = 1; i < n; ++i) {
    sa[i] = i;
    rank[i] = b[i];
  }
  int rn = 200;
  for (gap = 1; ; gap <<= 1) {    
    int p = 0;
    for (int i = n - 1; i + gap >= n; --i) tmp[++p] = i;
    std::fill(bucket + 1, bucket + rn + 1, 0);
    for (int i = 1; i + gap < n; ++i) ++bucket[rank[i + gap]];
    for (int i = 2; i <= rn; ++i) bucket[i] += bucket[i - 1];
    for (int i = 1; i + gap < n; ++i) tmp[p + bucket[rank[i + gap]]--] = i;
    std::fill(bucket + 1, bucket + rn + 1, 0);
    for (int i = 1; i < n; ++i) ++bucket[rank[i]];
    for (int i = 2; i <= rn; ++i) bucket[i] += bucket[i - 1];
    for (int i = n - 1; i >= 1; --i) sa[bucket[rank[tmp[i]]]--] = tmp[i];
    tmp[1] = 1;
    for (int i = 2; i < n; ++i) tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for (int i = 1; i < n; ++i) rank[sa[i]] = tmp[i];
    if (tmp[n - 1] == n - 1) break;
    rn = tmp[n - 1];
  }
  for (int i = 1, k = 0; i < n; ++i) {
    if (rank[i] == n - 1) continue;
    for (int j = sa[rank[i] + 1]; b[i + k] == b[j + k]; ) ++k;
    lcp[rank[i]] = k;
    if (k) --k;
  }
  int ans = 0;
  for (int low = 4, high = n - 1; low <= high; ) {
    int mid = (low + high) >> 1;
    std::deque<int> min_lcp, max_pos, min_pos;
    int flag = 0, right = 0;
    for (int i = 1; i < n && flag == 0; ++i) {
      if (right < i) right = i;
      while (right + 1 < n && lcp[right] >= mid) {
        while (!min_lcp.empty() && lcp[min_lcp.back()] >= lcp[right])
          min_lcp.pop_back();
        min_lcp.push_back(right);
        ++right;
        while (!max_pos.empty() && sa[max_pos.back()] <= sa[right])
          max_pos.pop_back();
        max_pos.push_back(right);
        while (!min_pos.empty() && sa[min_pos.back()] >= sa[right])
          min_pos.pop_back();
        min_pos.push_back(right);
      }      
      if (!min_lcp.empty() && lcp[min_lcp.front()] >= mid) {
        int v_max = sa[max_pos.front()];
        int v_min = sa[min_pos.front()];
        flag |= sa[i] - v_min - 1 >= mid;
        flag |= v_max - sa[i] - 1 >= mid;
      }
      if (!min_pos.empty() && min_pos.front() < i + 1) min_pos.pop_front();
      if (!max_pos.empty() && max_pos.front() < i + 1) max_pos.pop_front();
      if (!min_lcp.empty() && min_lcp.front() < i + 1) min_lcp.pop_front();      
    }
    if (flag) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  ++ans;
  if (ans < 5) ans = 0;
  std::cout << ans;
}
