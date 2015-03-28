#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <set>
 
#define m2 std::make_pair
 
typedef std::pair<int, int> p2;
 
const char s[] = "manku";
char ans[111];
 
int main() {
  int tt;
  scanf("%d", &tt);
  while (tt--) {
    long long n;
    scanf("%lld", &n);
    int cnt = 0;
    while (n) {
      --n;
      ans[++cnt] = s[n % 5];
      n /= 5;
    }
    std::reverse(ans + 1, ans + cnt + 1);
    ans[++cnt] = 0;
    puts(ans + 1);
  }
} 