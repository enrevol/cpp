#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>
 
typedef std::pair<int, int> p2;
 
p2 a[101010];
 
bool f(const p2& lhs, const p2& rhs) {
  if (lhs.second == rhs.second) return lhs.first > rhs.first;
  return lhs.second < rhs.second;
}
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
      scanf("%d %d", &a[i].first, &a[i].second);
    std::sort(a + 1, a + n + 1, f);
    int it = 2, last = a[1].second, ans = 1;
    while (it <= n) {
      if (a[it].first >= last) {
        last = a[it].second;
        ++ans;
      }
      ++it;
    }
    printf("%d\n", ans);
  }
} 