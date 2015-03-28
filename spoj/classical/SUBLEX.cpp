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
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#define DEBUG(z, x) { cerr << setw(z) << "" << (#x) << " = " << (x) << '\n'; }

using namespace std;

const int N = 100010;

char s[N];
int n, gap, sa[N], lcp[N], pos[N], tmp[N], bucket[N];
long long sum[N];

inline bool cmp(int i, int j) {
  if (pos[i] != pos[j]) return pos[i] < pos[j];
  i += gap;
  j += gap;
  if (i <= n && j <= n) return pos[i] < pos[j];
  return i > j;
}

int main() {
  //assert(freopen("input.txt", "r", stdin));
  //assert(freopen("output.txt", "w", stdout));
  //std::ios::sync_with_stdio(0);
  //std::cin.tie(0);
  scanf("%s", s + 1);
  n = strlen(s + 1);
  for (int i = 1; i <= n; ++i) {
    sa[i] = i;
    pos[i] = s[i];
  }
  int rn = 255;
  for (gap = 1; ; gap <<= 1) {
    int p = 0;
    for (int i = n; i + gap > n; --i) tmp[++p] = i;
    fill(bucket + 1, bucket + rn + 1, 0);
    for (int i = 1; i + gap <= n; ++i) ++bucket[pos[i + gap]];
    for (int i = 2; i <= rn; ++i) bucket[i] += bucket[i - 1];
    for (int i = 1; i + gap <= n; ++i) tmp[p + bucket[pos[i + gap]]--] = i;
    fill(bucket + 1, bucket + rn + 1, 0);
    for (int i = 1; i <= n; ++i) ++bucket[pos[i]];
    for (int i = 2; i <= rn; ++i) bucket[i] += bucket[i - 1];
    for (int i = n; i >= 1; --i) sa[bucket[pos[tmp[i]]]--] = tmp[i];
    tmp[1] = 1;
    for (int i = 2; i <= n; ++i) tmp[i] = tmp[i - 1] + cmp(sa[i - 1], sa[i]);
    for (int i = 1; i <= n; ++i) pos[sa[i]] = tmp[i];
    if (tmp[n] == n) break;
    rn = tmp[n];
  }
  for (int i = 1, k = 0; i <= n; ++i) {
    if (pos[i] == n) continue;
    for (int j = sa[pos[i] + 1]; s[i + k] == s[j + k]; ) ++k;
    lcp[pos[i]] = k;
    if (k) --k;
  }
  for (int i = 1; i <= n; ++i) {
    sum[i] = sum[i - 1] + (n - sa[i] + 1) - lcp[i - 1];
//    cerr << "i = " << i << " sum = " << sum[i] << '\n';
  }
  int q;
  scanf("%d", &q);
  while (q--) {
    long long k;
    scanf("%lld", &k);
    for (int i = 1; i <= n; ++i) {
      if (sum[i - 1] < k && k <= sum[i]) {
        int p = k - sum[i - 1] + lcp[i - 1];
        for (int j = sa[i]; j <= sa[i] + p - 1; ++j)
          putchar(s[j]);
        puts("");
        break;
      }
    }
  }
}