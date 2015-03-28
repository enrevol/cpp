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

const int N = 50010;

typedef std::pair<int, int> p2;

char s[N];
int gap, n;
int sa[N], lcp[N], rank[N], tmp[N];
std::deque<p2> q;

bool cmp(int i, int j) {
  if (rank[i] != rank[j]) return rank[i] < rank[j];
  i += gap;
  j += gap;
  if (i <= n && j <= n) return rank[i] < rank[j];
  return i > j;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  int k;
  scanf("%d %d", &n, &k);
  scanf("%s", s + 1);
  if (k == 1) { printf("%d", n); return 0; }
  for (int i = 1; i <= n; ++i) {
    sa[i] = i;
    rank[i] = s[i];
  }
  tmp[1] = 1;
  for (gap = 1; ; gap <<= 1) {
    std::sort(sa + 1, sa + n + 1, cmp);
    for (int i = 2; i <= n; ++i)
      tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for (int i = 1; i <= n; ++i)
      rank[sa[i]] = tmp[i];
    if (tmp[n] == n) break;
  }
  for (int i = 1, k = 1; i <= n; ++i) {
    if (rank[i] == n) continue;
    for (int j = sa[rank[i] + 1]; s[i + k] == s[j + k]; )
      ++k;
    lcp[rank[i]] = k;
    if (k) --k;
  }
  int ans = 0;
  for (int i = 1; i <= k - 1; ++i) {
    while (!q.empty() && q.back().second > lcp[i])
      q.pop_back();
    q.push_back(p2(i, lcp[i]));
  }
  for (int i = 1; i + k - 2 < n; ++i) {
    while (!q.empty() && q.front().first < i)
      q.pop_front();
    while (!q.empty() && q.back().second > lcp[i + k - 2])
      q.pop_back();
    q.push_back(p2(i + k - 2, lcp[i + k - 2]));
    ans = std::max(ans, q.front().second);
  }
  printf("%d", ans);
}
