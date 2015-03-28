#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
p2 a[101010]; 
 
int main() {
  //freopen("input.txt", "r", stdin);
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      scanf("%d", &a[i].first);
      a[i].second = i;
    }
    std::sort(a + 1, a + n + 1);
    long long ans = 0;
    int pos_max = a[n].second, pos_min = a[n].second;
    for (int i = n - 1; i >= 1; --i) {
      int val = std::max(abs(a[i].second - pos_max), abs(a[i].second - pos_min));      
      ans = std::max(ans, a[i].first * 1ll * val);
      if (a[i].second > pos_max) pos_max = a[i].second;
      if (a[i].second < pos_min) pos_min = a[i].second;
    }
    printf("%lld\n", ans);
  }
} 